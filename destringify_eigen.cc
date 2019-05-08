#include <iostream>
#include "destringify_eigen.hh"
#include "simple_parser.hh"

using namespace destringify_eigen;

std::pair<int, int>
destringify_eigen::parse_matrix_size(const std::string & s)
{
    int rows(std::count(s.begin(), s.end(), ';') + 1);

    SimpleParser p(s);

    p.consume(*simple_parser::any_of(" \t\n"));
    p.consume(simple_parser::exact("["));

    int cols(0);
    while (true)
    {
        p.consume(*simple_parser::any_of(" \t\n"));
        if (p.lookahead(simple_parser::exact(";")))
            break;
        std::string s;
        if (! p.consume(+simple_parser::any_of("0123456789.e+-") >> s))
            break;
        cols++;
    }

    return std::make_pair(rows, cols);
}

Eigen::MatrixXd
destringify_eigen::parse_matrix(const std::string & s)
{
    std::string numbers("0123456789");
    auto size(parse_matrix_size(s));
    auto rows(size.first);
    auto cols(size.second);
    Eigen::MatrixXd ret(Eigen::MatrixXd::Zero(rows, cols));

    SimpleParser p(s);

    p.consume(*simple_parser::any_of(" \t\n"));
    p.consume(simple_parser::exact("["));

    for (int i(0), i_end(rows) ; i < i_end ; ++i)
    {
        for (int j(0), j_end(cols) ; j < j_end ; ++j)
        {
            p.consume(*simple_parser::any_of(" \t\n"));
            std::string s;
            if (! p.consume(+simple_parser::any_of(numbers + ".e+-") >> s))
                throw std::invalid_argument("Expected to find a number, got '"
                        + p.rest() + "'.");
            ret(i, j) = destringify<double>(s);
        }
        p.consume(*simple_parser::any_of(" \t\n"));
        if (i < i_end - 1 && ! p.consume(simple_parser::exact(";")))
            throw std::invalid_argument(
                    "Expected ';', got '" + p.rest() + "'.");
    }
    p.consume(*simple_parser::any_of(" \t\n"));
    if (! p.consume(simple_parser::exact("]")))
        throw std::invalid_argument( "Expected ']', got '" + p.rest() + "'.");
    p.consume(*simple_parser::any_of(" \t\n"));

    if (! p.eof())
        throw std::invalid_argument("Found stray '" + p.rest() + "'.");

    return ret;
}

Eigen::ArrayXXd
destringify_eigen::parse_array(const std:: string & s)
{
    std:: string numbers("0123456789");
    auto size(parse_matrix_size(s));
    auto rows(size.first);
    auto cols(size.second);
    Eigen::ArrayXXd ret(Eigen::ArrayXXd::Zero(rows, cols));

    SimpleParser p(s);

    p.consume(*simple_parser::any_of(" \t\n"));
    p.consume(simple_parser::exact("["));

    for (int i(0), i_end(rows) ; i < i_end ; ++i)
    {
        for (int j(0), j_end(cols) ; j < j_end ; ++j)
        {
            p.consume(*simple_parser::any_of(" \t\n"));
            std::string s;
            if (! p.consume(+simple_parser::any_of(numbers + ".e+-") >> s))
                throw std::invalid_argument("Expected to find a number, got '"
                        + p.rest() + "'.");
            ret(i, j) = destringify<double>(s);
        }
        p.consume(*simple_parser::any_of(" \t\n"));
        if (i < i_end - 1 && ! p.consume(simple_parser::exact(";")))
            throw std::invalid_argument(
                    "Expected ';', got '" + p.rest() + "'.");
    }
    p.consume(*simple_parser::any_of(" \t\n"));
    if (! p.consume(simple_parser::exact("]")))
        throw std::invalid_argument( "Expected ']', got '" + p.rest() + "'.");
    p.consume(*simple_parser::any_of(" \t\n"));

    if (! p.eof())
        throw std::invalid_argument("Found stray '" + p.rest() + "'.");

    return ret;
}

