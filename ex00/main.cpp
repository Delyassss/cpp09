#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Missing argument!\n";
        return ;
    }
    BitcoinExchange(argv[1]);
}