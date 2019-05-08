/*! \brief Interpolates all the Aerodynamic Data Base
 * employing 2D Splines. This means that all the coefficients
 * can only depend on one variable.
 */

#ifndef RC_AIRPLANE_HH
#define RC_AIRPLANE_HH 1

#include <unsupported/Eigen/Splines>
#include <string>
#include <map>
#include "airplane.hh"
#include "Eigen/Core"
#include "adb.hh"


class Rc_Airplane: public Airplane
{
    private:
        std::map<std::string, Eigen::Spline<double, 2>>
            _subCoefSpline;

        double _applicationRule(Coef coef);

    public:
        Rc_Airplane (int label, std::string adbxmlname, 
                std::string initialconditions);
        ~Rc_Airplane();

        Eigen::Vector3d getForces();
        Eigen::Vector3d getMoments();
};
#endif
