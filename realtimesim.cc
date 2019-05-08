#include <time.h>
#include <unistd.h>
#include <iostream>

#include "simulation.hh"
#include "realtimesim.hh"

#ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
#endif

RealTimeSim::RealTimeSim(Simulation * sim) :
    _sim(sim)
{
}

RealTimeSim::~RealTimeSim()
{
}

namespace
{
    int our_clock_realtime(struct timespec * ts)
    {
#ifdef __MACH__
        clock_serv_t cclock;
        host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);

        mach_timespec_t mts;
        kern_return_t kret(clock_get_time(cclock, &mts));

        mach_port_deallocate(mach_task_self(), cclock);

        ts->tv_sec = mts.tv_sec;
        ts->tv_nsec = mts.tv_nsec;

        return kret == KERN_SUCCESS ? 0 : -1;
#else
        return clock_gettime(CLOCK_REALTIME, ts);
#endif
    }
}

void RealTimeSim::start()
{
    timespec ts;
    timespec tsleep;
    tsleep.tv_sec = 0;

    int last_step_time = -1;

    _sim->init();
    double endtime = _sim->get_endtime();

    long dt_ns = (long)(_sim->dt()*1e9);

    while(! _sim->isFinished())
    {
        our_clock_realtime(&ts);
        last_step_time = ts.tv_nsec;

        _sim->step();

        our_clock_realtime(&ts);
        tsleep.tv_nsec = dt_ns - (ts.tv_nsec - last_step_time);

        if(tsleep.tv_nsec < 0)
        {
            std::cout << tsleep.tv_nsec << " " <<
                ts.tv_nsec << " " <<
                last_step_time << " " << 
                _sim->get_time() <<
                std::endl;
        }else
            nanosleep(&tsleep, NULL);

        if(_sim->get_time() >= endtime)
            _sim->finish();
    }
}


