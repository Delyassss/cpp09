#ifndef RPN_HPP
#define RPN_HPP

#include "stack"
#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include <cstdlib>
#include <string>


typedef std::stack<long> stackk;
typedef std::stack<std::string> Oper;


class RPN
{
    stackk   mycontsiner;
    long    res;
    Oper    myoperators;

    public :
    RPN();
    ~RPN();
    RPN(RPN const &src);
    RPN &operator=(RPN const &rhs);
    void parsing(std::string line);
    stackk &getContainer();
    Oper &getOperators();
};


#endif

