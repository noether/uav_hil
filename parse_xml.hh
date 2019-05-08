#ifndef DESTRINGIFY_XML_HH
#define DESTRINGIFY_XML_HH 1

#include "destringify.hh"
#include <tinyxml2.h>
#include <Eigen/Core>
#include <list>
#include <string>

Eigen::ArrayXXd parse_subelements_to_array(const tinyxml2::XMLElement * e,
        std::list<std::string> * p);

Eigen::MatrixXd parse_element_to_matrix(const tinyxml2::XMLElement * e);

template <typename T_> inline
T_ parse_element_to_scalar(const tinyxml2::XMLElement * e)
{
    T_ number(destringify<T_>(e->GetText()));

    return number;
}

template <typename T_>
inline const tinyxml2::XMLElement* getSafeFirstChildElement(T_ *n){
    if(n->NoChildren()){
        std::string name(n->Value());
        throw std::runtime_error(name + " XML is empty");
    }
    return n->FirstChildElement();
}

#endif
