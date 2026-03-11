#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include "string.h"
#include "iostream"
#include "map"
#include "fstream"
#include "vector"
#include "sstream"
#include <cstdlib>
#include <string>

struct inputfile
{
    void    *date;
    void    *value;
};

typedef std::map<std::string, double> data_M;
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
    data_M      &getdata();
    input_M     &getinput();
    void        readData(std::map<std::string, double> &mydata, std::string filename, char delim, int insert);
    bool        calcul(std::string date , std::string value, data_M &data);
    bool        checkFormatandInsert(std::string line, char split, int insert , data_M &data);
    





};


#endif