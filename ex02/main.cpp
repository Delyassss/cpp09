#include "PmergeMe.hpp"


int main(int argc, char **argv)
{

    if (argc < 2)
           return (std::cerr << "Error\n", 1);
    PmergeMe pmergeme(argv, argc);
}