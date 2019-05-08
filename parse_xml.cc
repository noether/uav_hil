#include <iostream>
#include <tinyxml2.h>
#include <list>
#include <string>
#include "destringify_eigen.hh"
#include "destringify.hh"
#include "parse_xml.hh"

Eigen::ArrayXXd
parse_subelements_to_array(const tinyxml2::XMLElement * e, 
        std::list<std::string> * p)
{
    const tinyxml2::XMLElement *_subelement
        = getSafeFirstChildElement(e);
    std::string _array_subelements = "[";

    while(1){
        _array_subelements += _subelement->GetText();
        p->push_back(_subelement->Name());

        if(_subelement->ShallowEqual(e->LastChild()))
            break;
        else{
            _subelement =
                _subelement->NextSiblingElement();
            _array_subelements += ";";
        }
    }

    _array_subelements += "]";

    return destringify_eigen::parse_array(_array_subelements);
}

Eigen::MatrixXd
parse_element_to_matrix(const tinyxml2::XMLElement * e)
{
    return destringify_eigen::parse_matrix(e->GetText());
}
