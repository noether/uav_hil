#include <math.h>
#include <iostream>
#include <deque>

#include "rc_airplane.hh"
#include "init_simulation.hh"
#include "sixdof.hh"
#include "simulation.hh"
#include "realtimesim.hh"
#include "batchsim.hh"

int main(int argc, char* argv[])
{
    std::string cfg;

    if(argc != 2)
    {
        std::cout << "Usage: uavsim configFile" << std::endl;
        return 0;
    }else
    {
        cfg = argv[1];
    }

    Init_Simulation init_simulation(cfg);
	Simulation sim(init_simulation.sim_cfg, &init_simulation.sixdof_vehicles);
    
    if(init_simulation.sim_cfg.realtime || init_simulation.sim_cfg.hil)
    {
        RealTimeSim rts(&sim);
        rts.start();
    }else
    {
        BatchSim bs(&sim);
        bs.start();
    }

	std::cout << "Simulation done " << std::endl;
	return 0;
}
