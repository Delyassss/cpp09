#include "BitcoinExchange.hpp"
bool isNumber(std::string line, int forDate)
{
    for (size_t i = 0; i < line.length(); i++)
    {
        if (!std::isdigit(line[i]))
            return (std::cout << "Error: not a valid number." << std::endl, false);
    }
    if (std::atof(line.c_str()) < 0)
        return (std::cout << "Error: not a positive number." << std::endl, false);
    if (!forDate && std::atof(line.c_str()) > 1000)
    {
        return (std::cout << "Error: too large a number." << std::endl,false);
    }
    return (true);
}

bool isleap (int year)
{
    bool leap = false;
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        leap = true;
    return leap;
}
bool checkDay(long day, long month, long year)
{
    bool isLeap = isleap(year);
    int fevrier = isleap ? 29 : 28;
    int  dayinmonth[12] = {31, fevrier, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > dayinmonth[month - 1])
        return (std::cout << "Error: not a valid day." << std::endl, false);
    return (true);
}

bool validDate(std::vector<std::string> strs)
{
    long year = atol(strs[0].c_str());
    long month = atol(strs[1].c_str());
    long day = atol(strs[2].c_str());
    if (year < 2009 || year > 2022)
        return (std::cout << "Error: not a valid date." << std::endl, false);
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return (std::cout << "Error: not a valid date." << std::endl, false);
    return  (checkDay(day, month, year));
}
bool isTime(std::string line)
{
    std::vector <std::string> strs;
    std::stringstream ss(line);
    std::string item;
    
    if (line.size() != 10)
        return (std::cout << "Error: invalid date format" << std::endl, false);

    while (std::getline(ss, item , '-'))
    {
        if (item.empty() || !isNumber(item, true))
            return (std::cout << "Error: invalid date format" << std::endl, false);
        strs.push_back(item);
    }
    if (strs.size() != 3)
        return (std::cout << "Error: invalid date format" << std::endl, false);
    validDate(strs);
    return (true);
}

bool checkFormatandInsert(std::string line, char split, int insert , data_M &data)// 1 for insert
{
    std::vector <std::string> strs;
    size_t pos = 0;
    while ((pos = line.find(split, pos)) != std::string::npos)
    {
        strs.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
        if (strs.size() > 2)
        {
            return (std::cout  << "Error: too many arguments" << std::endl, false);
        }

    if (isTime(strs[0]) && isNumber(strs[1], insert))
    {
        std::pair<std::string, float> p(strs[0], std::atof(strs[1].c_str()));
        if (insert == 1)
            data.insert(p);
        return (true);
    }
}
void BitcoinExchange::readData(std::map<std::string, float> &mydata, std::string filename, char delim, int insert)// 1 for inserting to the map
{
    if (filename.empty())
        (throw std::runtime_error("Empty filename"));

    std::ifstream d_input(filename);
    if (!d_input.is_open())
        (throw std::runtime_error("Error opening file"));

    std::string line;
    if (delim == ',')
    {
        std::getline(d_input, line);
        if (line != "date,exchange_rate")
             throw (std::runtime_error("Error: invalid database format."));
    }
    else if (delim == '|')
    {
        std::getline(d_input, line);
        if (line != "date|value")
            std::cerr << "Error: missing (date | value) header !" << std::endl;
    }
    while (!line.empty())
    {
        if (!checkFormatandInsert(line, delim, insert, mydata) && insert)
            throw (std::runtime_error("Error: invalid database format."));
            std::getline(d_input, line);
    }
    return ;
}
BitcoinExchange::BitcoinExchange(std::string filename)
{
    readData(_data, "data.csv", ',', 1);
    readData(_input, filename, '|' , 0);




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