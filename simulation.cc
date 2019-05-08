#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <deque>

#include "simulation.hh"
#include "sixdof.hh"

Simulation::Simulation(Sim_Cfg sim_cfg, std::deque<Sixdof> * sixdofvehicles) :
	_dt(sim_cfg.dt), 
    _time(sim_cfg.inittime), 
    _endtime(sim_cfg.endtime),
    _sixdofvehicles(sixdofvehicles),
	_finished(false)
{
}

Simulation::~Simulation()
{
	_log.close();
}

void Simulation::init()
{
	time_t rawtime;
	time(&rawtime);

	//XXX Check if there are problems creating the dir
	mkdir("./logs", S_IRWXU);
	char filename[31];
	strftime(filename, 31, "./logs/log_%Y%m%d_%H%M%S.txt", gmtime(&rawtime));

	_log.open(filename);

}

void Simulation::step()
{
    std::deque<Sixdof>::iterator it = _sixdofvehicles->begin();
	while (it != _sixdofvehicles->end())
    {
        it->step();
        it++;
    }
	_time += _dt;
	_log << _time << std::endl;
}

void Simulation::finish()
{
	_finished = true;
}
	
bool Simulation::isFinished() const
{
	return _finished;
}

double Simulation::get_time() const
{
	return _time;
}

double Simulation::get_endtime() const
{
	return _endtime;
}

double Simulation::dt() const
{
	return _dt;
}
