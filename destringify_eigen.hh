#ifndef DESTRINGIFY_EIGEN_HH
#define DESTRINGIFY_EIGEN_HH 1

#include "destringify.hh"
#include <Eigen/Core>

namespace destringify_eigen
{
    std::pair<int, int> parse_matrix_size(const std::string &);
    Eigen::MatrixXd parse_matrix(const std::string & s);
    Eigen::ArrayXXd parse_array(const std::string & s);
}

template<>
inline Eigen::MatrixXd destringify(const std::string & s)
{
    return destringify_eigen::parse_matrix(s);
}

template<>
inline Eigen::ArrayXXd destringify(const std::string & s)
{
    return destringify_eigen::parse_array(s);
}
#endif
