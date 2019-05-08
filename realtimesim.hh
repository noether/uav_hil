/*! \brief Performs the Simulation in real time.
 */

#ifndef REALTIMESIM_HH
#define REALTIMESIM_HH 1

#include "simulation.hh"

class RealTimeSim
{
	private:
		Simulation * _sim;

	public:
		RealTimeSim(Simulation *);
		~RealTimeSim();

		void start();
};
#endif
