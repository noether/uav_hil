/*! \brief Performs a batch of simulations as fast as possible.
 */

#ifndef BATCHSIM_HH
#define BATCHSIM_HH 1

#include "simulation.hh"

class BatchSim
{
	private:
		Simulation * _sim;

	public:
		BatchSim(Simulation *);
		~BatchSim();

		void start();
};
#endif
