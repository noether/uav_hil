#ifndef INIT_SIMULATION_HH
#define INIT_SIMULATION_HH 1

#include <string>
#include <deque>

#include "sixdof.hh"

struct Sim_Cfg
{
    double dt, inittime, endtime;
    bool realtime, hil;
};

/*! \brief Sets up Simulation from the configuration XML file
 */
class Init_Simulation
{
    private:
        std::string _conf_file;

    public:
        Init_Simulation(std::string conf_file);
        ~Init_Simulation();
        Sim_Cfg sim_cfg;
        std::deque<Sixdof> sixdof_vehicles;
};


#endif
