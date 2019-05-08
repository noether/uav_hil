#ifndef AIRPLANE_HH
#define AIRPLANE_HH 1

#include "vehicle.hh"
#include "Eigen/Core"
#include "adb.hh"
#include <map>
#include <string>

/*! \brief The representation of the Airplane.
 */
typedef struct
{
    Eigen::Vector4d q;
    Eigen::Vector3d PosECI;
    Eigen::Vector3d PosECEF;
    Eigen::Vector3d PosLLH;
    Eigen::Vector3d Attitude;
    Eigen::Vector3d AerodynamicAngles;
    Eigen::Vector3d PQR;
    Eigen::Vector3d VelECEF;
    Eigen::Vector3d VelENU;
    Eigen::Vector3d VelRelWind;
    std::map<std::string, double> Actuators;
}StatevectorAirplane;

/*! \brief Virtual class which contains
 *  the state vector and a XML file with ADB data for one Airplane.
 */
class Airplane: public Vehicle
{
    protected:
        Adb_Plane   _adb;
        StatevectorAirplane _statevector;

    public:
        Airplane(int label,
                std::string adbxmlname, std::string initialconditions);
        ~Airplane();
        
        Eigen::Vector3d getPQR();
        Eigen::Vector4d getQ();
        Eigen::Vector3d getPosECI();
        Eigen::Vector3d getVelECEF();

        virtual Eigen::Vector3d getForces() = 0;
        virtual Eigen::Vector3d getMoments() = 0;
};

#endif
