#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "string.h"
#include "iostream"
#include "map"
#include "fstream"
#include "vector"
#include "sstream"

struct inputfile
{
    void    *date;
    void    *value;
};

typedef std::map<std::string, float> data_M;
typedef std::map<std::string, float> input_M;

class BitcoinExchange
{
    private :
        data_M _data;
        input_M _input;
        BitcoinExchange();

    public :
    BitcoinExchange(std::string filename);
    ~BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &src);
    BitcoinExchange &operator=(BitcoinExchange const &rhs);
    data_M &getdata();
    input_M &getinput();
    void readData(std::map<std::string, float> &mydata, std::string filename, char delim);






};


#endif