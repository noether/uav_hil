#include <memory>

#include "sixdof.hh"
#include "vehicle.hh"

Sixdof::Sixdof(Sixdof && o) :
    _vehicle(std::move(o._vehicle))
{
}

Sixdof::Sixdof(std::unique_ptr<Vehicle> && vehicle) :
    _vehicle(std::move(vehicle))
{
}

Sixdof::~Sixdof()
{
}

void Sixdof::step()
{
    _vehicle->getForces();
}
