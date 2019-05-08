/*! \brief Abstract class for passing Moments and Forces to the
 *         Simulation.
 */

#ifndef VEHICLE_HH
#define VEHICLE_HH 1

#include "Eigen/Core"

class Vehicle
{
	protected:
        int _label;

        Eigen::Matrix3d _inertiaTensor;
		double _mass;
        Eigen::Vector3d _centreOfGravity;

	public:
		Vehicle();
        Vehicle(int label);
		~Vehicle();
		virtual Eigen::Vector3d getForces() = 0;
		virtual Eigen::Vector3d getMoments() = 0;
        virtual Eigen::Vector3d getPQR() = 0;
        virtual Eigen::Vector4d getQ() = 0;
        virtual Eigen::Vector3d getPosECI() = 0;
        virtual Eigen::Vector3d getVelECEF() = 0;
};


#endif
