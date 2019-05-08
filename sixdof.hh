/*! \brief Ask for the Moments and Forces applied in 
 * one Vehicle and applies 6DoF dynamics.
 */

#ifndef SIXDOF_HH
#define SIXDOF_HH 1

#include <memory>
#include "vehicle.hh"

class Sixdof
{
	private:
        std::unique_ptr<Vehicle> _vehicle;

	public:
        Sixdof(Sixdof &&);
		Sixdof(std::unique_ptr<Vehicle> &&);
		~Sixdof();

		void step();
};

#endif
