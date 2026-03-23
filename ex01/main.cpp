#include "RPN.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong argument!\n";
        return 1;
    }
    RPN rpn;
    rpn.parsing(argv[1]);
    return (0);
}