#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong argument!\n";
        return 1;
    }
    BitcoinExchange btc(argv[1]);
}