/*! \brief Sweeps all the Vehicles, applies
 *  the numerical integration, defines the network of Vehicles for
 *  allowing communication and saves a log.
 */

#ifndef SIMULATION_HH
#define SIMULATION_HH 1

#include <fstream>
#include <deque>
#include "sixdof.hh"
#include "init_simulation.hh"

class Simulation
{
	private:
		double _dt, _time, _endtime;
        std::deque<Sixdof> * _sixdofvehicles;
		bool _finished;
		std::ofstream _log;

	public:
		Simulation(Sim_Cfg, std::deque<Sixdof> *);
		~Simulation();

		void init();
		void step();
		void finish();
		bool isFinished() const;
		double get_time() const;
        double get_endtime() const;
		double dt() const;
};

#endif
