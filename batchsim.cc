#include <time.h>
#include <unistd.h>
#include <iostream>

#include "simulation.hh"
#include "batchsim.hh"

BatchSim::BatchSim(Simulation * sim) :
    _sim(sim)
{
}

BatchSim::~BatchSim()
{
}

void BatchSim::start()
{
    _sim->init();
    double endtime = _sim->get_endtime();

    while(! _sim->isFinished())
    {
        _sim->step();

        if(_sim->get_time() >= endtime)
            _sim->finish();
    }
}

