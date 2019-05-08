#ifndef ADB_HH
#define ADB_HH 1

#include <Eigen/Core>
#include <map>
#include <list>
#include <tinyxml2.h>
#include <iostream>
#include <stdexcept>

/*! \brief Stores the aerodynamic subcoeficcients in tables.
 */
class SubCoef
{
    private:
        std::list<std::string> _listparameters;
        Eigen::ArrayXXd _table;

    public:
        SubCoef(std::list<std::string>, Eigen::ArrayXXd);
        ~SubCoef();
        std::list<std::string> getListParameters();
        Eigen::ArrayXXd getTable();
};

/*! \brief Gathers all the subcoefficients of one 
 *         aerodynamic coefficient.
 */
class Coef
{
    private:
        std::map<std::string, SubCoef> _mapSubCoefs;

    public:
        Coef();
        ~Coef();
        void setSubCoef(std::string, SubCoef);
        std::map<std::string, SubCoef> getSubCoefmap();
};

/*! \brief Maps all the aerodynamic coefficients of
 *         one Airplane.
 */
class Adb_Plane
{
    private:
        std::map<std::string, Coef> _mapCoefs;
        void _readAdbxml(std::string adbxmlname);

    public:
        Adb_Plane(std::string adbxmlname);
        ~Adb_Plane();
        std::map<std::string, Coef> getCoefmap();
};

#endif
