#include "BitcoinExchange.hpp"
bool isNumber(std::string line)
{
    for (size_t i = 0; i < line.length(); i++)
    {
        if (!std::isdigit(line[i]))
            return (false);
    }
    if (std::atof(line.c_str()) < 0 || std::atof(line.c_str()) > 1000)
        return (false);
    return (true);
}

bool isTime(std::string line)
{
    std::vector <std::string> strs;
    std::stringstream ss(line);
    std::string item;
    int i = 0;
    while (std::getline(ss, item , '-'))
    {
        if (item.empty() || !isNumber(item))
            return (false);
        strs.push_back(item);
        if (strs.size() > 2)
        {
            return (false);
        }
        i++;

    }
}

bool checkFormatandInsert(std::string line, char split, int insert , data_M &data)// 1 for insert
{
    std::vector <std::string> strs;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item , split))
    {
        if (item.empty())
            return (false);
        strs.push_back(item);
        if (strs.size() > 2)
        {
            return (false);
        }
    }
    if (isTime(strs[0]) && isNumber(strs[1]))
    {
        std::pair<std::string, float> p(strs[0], std::atof(strs[1].c_str()));
        if (insert == 1)
            data.insert(p);
        return (true);
    }
}
void BitcoinExchange::readData(std::map<std::string, float> &mydata, std::string filename, char delim)
{
    if (filename.empty())
        (throw std::runtime_error("Empty filename"));

    std::ifstream d_input(filename);
    if (!d_input.is_open())
        (throw std::runtime_error("Error opening file"));
    std::string line;
    std::getline(d_input, line);
    if (line != ("date,exchange_rate"))
        throw (std::runtime_error("Error: invalid database format."));
    data_M &data = getdata();
    while (std::getline(d_input, line))
    {
        if (!checkFormatandInsert(line, delim, 1, data))
            throw (std::runtime_error("Error: invalid database format."));
        
    }
    return ;
}
BitcoinExchange::BitcoinExchange(std::string filename)
{
    readData(_data, "data.csv", ',');
    readData(_input, filename, '|');




}

data_M &BitcoinExchange::getdata()
{
    return (_data);
}

input_M &BitcoinExchange::getinput()
{
    return (_input);
}

BitcoinExchange::~BitcoinExchange()
{

}