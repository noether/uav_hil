#include "parse_xml.hh"
#include "adb.hh"

#include <string>
#include <tinyxml2.h>

SubCoef::SubCoef(std::list<std::string> l, Eigen::ArrayXXd t) :
    _listparameters(l),
    _table(t)
{
}

SubCoef::~SubCoef()
{
}

std::list<std::string> SubCoef::getListParameters()
{
    return _listparameters;
}

Eigen::ArrayXXd SubCoef::getTable()
{
    return _table;
}

Coef::Coef()
{
}

Coef::~Coef()
{
}

void Coef::setSubCoef(std::string s, SubCoef sc)
{
     this->_mapSubCoefs.insert(std::pair<std::string, SubCoef>(s, sc));
}

std::map<std::string, SubCoef> Coef::getSubCoefmap()
{
    return _mapSubCoefs;
}

Adb_Plane::Adb_Plane(std::string adbxmlname)
{
    _readAdbxml(adbxmlname);
    std::map<std::string, Coef>::iterator itcoef;
}

Adb_Plane::~Adb_Plane()
{
}

std::map<std::string, Coef> Adb_Plane::getCoefmap()
{
    return _mapCoefs;
}

void Adb_Plane::_readAdbxml(std::string adbxmlname)
{
    tinyxml2::XMLDocument adbdoc;
    adbxmlname.append(".xml");
    adbdoc.LoadFile(adbxmlname.c_str());
    const tinyxml2::XMLElement *adb = 
        adbdoc.FirstChildElement("AerodynamicDataBase");

    if(!adb)
        throw std::runtime_error("I can not find the AerodynamicDataBase");

    if(const tinyxml2::XMLElement *adb_coef
            = adb->FirstChildElement()){
        while(1){
            Coef c;
            _mapCoefs.insert(std::pair<std::string, Coef>
                    (adb_coef->Name(), c));

            if(adb_coef->ShallowEqual(adb->LastChild()))
                break;
            else
                adb_coef = adb_coef->NextSiblingElement();
        }
    }else
    {
        throw std::runtime_error("AerodynamicDataBase is empty");
    }

    std::map<std::string, Coef>::iterator it;

    for(it = _mapCoefs.begin(); it != _mapCoefs.end(); it++){

        if (const tinyxml2::XMLElement *adb_coef
                = adb->FirstChildElement((*it).first.c_str())){
                if (const tinyxml2::XMLElement *adb_subcoef
                    = adb_coef->FirstChildElement())
                {
                while(1){
                    std::list<std::string> parName;
                    Eigen::ArrayXXd table;

                    table = parse_subelements_to_array(adb_subcoef, &parName);
                    std::map<std::string, Coef>::iterator itcoef =
                        _mapCoefs.find((*it).first);

                    SubCoef sc(parName, table);
                    (*itcoef).second.setSubCoef(adb_subcoef->Name(), sc);

                    if(adb_subcoef->ShallowEqual(adb_coef->LastChild()))
                        break;
                    else
                        adb_subcoef = adb_subcoef->NextSiblingElement();
                }
                }else
                {
                    throw std::runtime_error((*it).first + " is empty");
                }
        }else
        {
            throw std::runtime_error((*it).first +
                    " coeff is missing from the ADB xml file");
        }
    }
}
