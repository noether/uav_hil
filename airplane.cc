#include "adb.hh"
#include "airplane.hh"
#include "Eigen/Core"
#include "parse_xml.hh"
#include "stringify.hh"

#include <string>

Airplane::Airplane(int label, std::string adbxmlname,
        std::string initialconditions) :
    Vehicle(label),
    _adb(adbxmlname)
{
    tinyxml2::XMLDocument initdoc;

    if(initdoc.LoadFile(initialconditions.c_str()))
    {
        throw std::runtime_error("I can not find the initial condition file");
    }
    initdoc.LoadFile(initialconditions.c_str());

    const tinyxml2::XMLElement *pqr =
        initdoc.FirstChildElement("PQR");
    if(!pqr)
    {
        std::string error_msg("I can not find the initial condition PQR");
        throw std::runtime_error(error_msg);
    }
    const tinyxml2::XMLElement *rpy =
        initdoc.FirstChildElement("rpy");
    if(!rpy)
    {
        std::string error_msg("I can not find the initial condition roll, pitch, yaw");
        throw std::runtime_error(error_msg);
    }
    const tinyxml2::XMLElement *latlonalt =
        initdoc.FirstChildElement("latlonalt");
    if(!latlonalt)
    {
        std::string error_msg("I can not find the initial condition for lat lon alt");
        throw std::runtime_error(error_msg);
    }
    const tinyxml2::XMLElement *velENU =
        initdoc.FirstChildElement("VelENU");
    if(!velENU)
    {
        std::string error_msg("I can not find the initial condition for VelENU");
        throw std::runtime_error(error_msg);
    }

    _statevector.PQR = parse_element_to_matrix(pqr);
}

Airplane::~Airplane()
{
}

Eigen::Vector3d Airplane::getPQR()
{
    return _statevector.PQR;
}

Eigen::Vector4d Airplane::getQ()
{
    return _statevector.q;
}

Eigen::Vector3d Airplane::getPosECI()
{
    return _statevector.PosECI;
}

Eigen::Vector3d Airplane::getVelECEF()
{
    return _statevector.PosECEF;
}

