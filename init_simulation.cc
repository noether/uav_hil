#include <tinyxml2.h>
#include <string>
#include <deque>
#include <memory>
#include <sstream>

#include "init_simulation.hh"
#include "parse_xml.hh"
#include "rc_airplane.hh"
#include "sixdof.hh"

Init_Simulation::Init_Simulation(std::string conf_file):
    _conf_file(conf_file)
{
    tinyxml2::XMLDocument adbdoc;
    adbdoc.LoadFile(conf_file.c_str());

    const tinyxml2::XMLElement *parameters = 
        adbdoc.FirstChildElement("SimulationParameters");
    if(!parameters)
        throw std::runtime_error("I can not find the SimulationParameters");

    const tinyxml2::XMLElement *e_dt =
        parameters->FirstChildElement("dt");
    if(!e_dt)
        throw std::runtime_error("I can not find the SimulationParameter dt");

    const tinyxml2::XMLElement *e_inittime =
        parameters->FirstChildElement("init_time");
    if(!e_inittime)
        throw std::runtime_error
            ("I can not find the SimulationParameter init_time");

    const tinyxml2::XMLElement *e_endtime =
        parameters->FirstChildElement("end_time");
    if(!e_endtime)
        throw std::runtime_error
            ("I can not find the SimulationParameter end_time");

    const tinyxml2::XMLElement *e_realtime =
        parameters->FirstChildElement("realtime");
    if(!e_realtime)
        throw std::runtime_error
            ("I can not find the SimulationParameter realtime");

    const tinyxml2::XMLElement *e_hil =
        parameters->FirstChildElement("hil");
    if(!e_hil)
        throw std::runtime_error("I can not find the SimulationParameter hil");

    sim_cfg.dt = parse_element_to_scalar<double>(e_dt);
    sim_cfg.inittime = parse_element_to_scalar<double>(e_inittime);
    sim_cfg.endtime = parse_element_to_scalar<double>(e_endtime);
    sim_cfg.realtime = parse_element_to_scalar<int>(e_realtime);
    sim_cfg.hil =  parse_element_to_scalar<int>(e_hil);

    const tinyxml2::XMLElement *e_vehicles =
        adbdoc.FirstChildElement("Vehicles");
    if(!e_vehicles)
        throw std::runtime_error("I can not find the Vehicles");

    const tinyxml2::XMLElement *e_vehicle = e_vehicles->FirstChildElement();

    std::string rc("RCAirplane");

    while(1){

        if(rc.compare(e_vehicle->Value()) == 0)
        {
            const tinyxml2::XMLElement *e_number =
                e_vehicle->FirstChildElement("number");
            const tinyxml2::XMLElement *e_adb =
                e_vehicle->FirstChildElement("adb");
            const tinyxml2::XMLElement *e_i =
                e_vehicle->FirstChildElement("initial_conditions");

            int number = parse_element_to_scalar<int>(e_number);
            for(int i = 1; i <= number; i++)
            {
                std::string cfg_adb("./database/");
                std::string cfg_initial("./config/");
                std::string numveh = static_cast<std::ostringstream*>
                    (&(std::ostringstream() << i))->str();

                cfg_adb.append(e_adb->GetText());
                cfg_initial.append(e_i->GetText());
                if(number != 1)
                {
                    cfg_initial.append("_");
                    cfg_initial.append(numveh);
                }
                cfg_initial.append(".xml");

                try{
                    Sixdof sixdof_rcplane(std::unique_ptr<Vehicle>(
                                new Rc_Airplane(i, cfg_adb, cfg_initial)));
                    sixdof_vehicles.push_back(std::move(sixdof_rcplane));
                }catch(std::runtime_error& e)
                {
                    std::cerr << e.what() << " for RC Plane " << i << std::endl;
                    throw std::runtime_error("RC Plane wrong cofigured");
                }
            }

        }

        if(e_vehicle->ShallowEqual(e_vehicles->LastChild()))
            break;
        e_vehicle = e_vehicle->NextSiblingElement();
    }

    if(sixdof_vehicles.empty())
        throw std::runtime_error("There are not vehicles for the simulation");

}

Init_Simulation::~Init_Simulation()
{
}

