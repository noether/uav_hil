#include "rc_airplane.hh"
#include "adb.hh"
#include <string>

Rc_Airplane::Rc_Airplane (int label, std::string adbxmlname,
        std::string initialconditions) :
            Airplane(label, adbxmlname, initialconditions)
{
    std::map<std::string, Coef> mapCoefs(_adb.getCoefmap());
    std::map<std::string, Coef>::iterator itCoef;

    for(itCoef = mapCoefs.begin(); itCoef != mapCoefs.end(); itCoef++)
    {
        Coef coef((*itCoef).second);
        std::map<std::string, SubCoef> mapSubCoefs(coef.getSubCoefmap());

        std::map<std::string, SubCoef>::iterator itSubCoef;

        for(itSubCoef = mapSubCoefs.begin(); itSubCoef != mapSubCoefs.end();
                itSubCoef++)
        {
            SubCoef subcoef((*itSubCoef).second);
            Eigen::Spline<double, 2>::ControlPointVectorType points
                (subcoef.getTable());

            Eigen::Spline<double, 2> spline =
                Eigen::SplineFitting<Eigen::Spline<double, 2>>
                ::Interpolate(points, 3);

            _subCoefSpline.insert(std::make_pair((*itSubCoef).first,
                        spline));
        }
    }
}

Rc_Airplane::~Rc_Airplane()
{
}

Eigen::Vector3d Rc_Airplane::getForces()
{
    Eigen::Vector3d force;

    std::map<std::string, Coef> mapCoefs(_adb.getCoefmap());
    std::map<std::string, Coef>::iterator itCoef;

    for(itCoef = mapCoefs.begin(); itCoef != mapCoefs.end(); itCoef++)
    {
        _applicationRule((*itCoef).second);
    }

    std::map<std::string, Eigen::Spline<double, 2>>::
        iterator cx;
    cx = _subCoefSpline.find("CX0");

    force << 0, 0, 0;
    return force;
}

Eigen::Vector3d Rc_Airplane::getMoments()
{
    Eigen::Vector3d moment;
    moment << 0, 0, 0;
    return moment;
}

double Rc_Airplane::_applicationRule(Coef coef)
{
    std::map<std::string, SubCoef> mapSubCoefs(coef.getSubCoefmap());
    std::map<std::string, SubCoef>::iterator itSubCoef;

    for(itSubCoef = mapSubCoefs.begin(); itSubCoef != mapSubCoefs.end(); 
            itSubCoef++)
    {
        std::string param  = (*itSubCoef).first;
        param.erase(0, 2);

        std::cout << param;
    }

     std::cout << std::endl;

     return 2;
}
