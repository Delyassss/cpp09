#include "BitcoinExchange.hpp"

std::string &trimWithSpaces(std::string &str)
{
    str.erase(0, str.find_first_not_of(" \t\r"));
    str.erase(str.find_last_not_of(" \t\r") + 1);
    return (str);
}
bool isNumber(std::string line, int forDate)
{
    size_t i = 0;
    
    // std::cout << "Line {" << line << "}" << std::endl;

    if (line.empty())
        return false;

     if (line[i] == '-' || line[i] == '+')
        i++;

    for (; i < line.length(); i++)
    {
        if ((!std::isdigit(line[i]) && line[i] != '.'))
            return (std::cout << "Error: not a valid number." << std::endl, false);
    }

    if (std::atof(line.c_str()) < 0)
        return (std::cout << "Error: not a positive number." << std::endl, false);
    if (!forDate && std::atof(line.c_str()) > 1000.0)
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
    int fevrier = isLeap ? 29 : 28;
    int  dayinmonth[12] = {31, fevrier, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > dayinmonth[month - 1])
        return (std::cout << "Error: not a valid day." << std::endl, false);
    return (true);
}

bool validDate(std::vector<std::string> strs)
{
    long year = std::atol(strs[0].c_str());
    long month = std::atol(strs[1].c_str());
    long day = std::atol(strs[2].c_str());
    if (year < 2009 || year > 2022)
        return (std::cout << "Error: not a valid date." << std::endl, false);
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return (std::cout << "Error: not a valid date." << std::endl, false);
    return  (checkDay(day, month, year));
}

bool isTime(std::string line)
{
    std::vector <std::string> strs;
    std::string item;
    
    if (line.size() != 10)
    return (std::cout << "Error: invalid date format" << std::endl, false);
    std::stringstream ss(line);

    while (std::getline(ss, item , '-'))
    {
        if (item.empty() || !isNumber(item, 1))
            return (std::cout << "Error: invalid date format" << std::endl, false);
        strs.push_back(item);
    }
    if (strs.size() != 3)
        return (std::cout << "Error: invalid date format" << std::endl, false);
    validDate(strs);
    return (true);
}

bool BitcoinExchange::checkFormatandInsert(std::string line, char delim, int insert , data_M &data)// 1 for insert
{
    std::vector <std::string> strs;
    std::string extracted;
    size_t pos = 0;
    while ((pos = line.find(delim, pos)) != std::string::npos)
    {
        extracted = line.substr(0, pos);
        // std::cout << "extracted {" << extracted << "}" << std::endl;

        strs.push_back(extracted);
        line.erase(0, pos + 1);
        pos = 0;
    }
    if (line.size() > 0)
    {
        extracted = line.substr(0 , pos -3);
        // std::cout << "extracted {" << extracted << "}" << std::endl;
        strs.push_back(extracted);
    }

    if (strs.size() != 2)
    {
        return (std::cout  << "Error: Invalid arguments" << std::endl, false);
    }
    std::string date = strs[0];
    date = trimWithSpaces(date);
    std::string value = strs[1];
    value = trimWithSpaces(value);


    // std::cout << "value {" << value << "}" << std::endl;
    // std::cout << "date {" << date << "}" << std::endl;

    if (isTime(date) && isNumber(value, insert))
    {
        std::pair<std::string, double> p(date, std::atof(value.c_str()));
        if (insert == 1)
            data.insert(p);
        else
            return (calcul(date,value, data));
            
        return (true);
    }
    return (false);
}

void BitcoinExchange::readData(std::map<std::string, double> &mydata, std::string filename, char delim, int insert)// 1 for inserting to the map
{
    if (filename.empty())
        (throw std::runtime_error("Empty filename"));

    std::ifstream d_input(filename.c_str());
    if (!d_input.is_open())
        (throw std::runtime_error("Error opening file"));

    std::string line;
    if (delim == ',')
    {
        std::getline(d_input, line);
        if (line != "date,exchange_rate" && line.find("date,exchange_rate") == std::string::npos)
            {
                d_input.close();
                throw (std::runtime_error("Error: invalid database format."));
            }
    }
    else if (delim == '|')
    {
        std::getline(d_input, line);
        if (line != "date | value" && line.find("date | value") == std::string::npos)
            std::cerr << "Error: missing (date | value) header !" << std::endl;
    }
    while (std::getline(d_input, line))
    {
        if (d_input.eof())
            break;           
        if (checkFormatandInsert(line, delim, insert, mydata) == false)
        {
           if (delim == ',')
           {
                d_input.close();
                throw (std::runtime_error("Error: invalid database format."));
           }
        }
    }
    d_input.clear();
    d_input.close();
    return ;
}

BitcoinExchange::BitcoinExchange(std::string filename)
{
    readData(getdata(), "data.csv", ',', 1);
    readData(getdata(), filename, '|' , 0);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
    if (this != &rhs)
    {
        this->_data = rhs._data;
        this->_input = rhs._input;
    }
    return (*this);
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

void printRes(double INP_value, double DB_value, std::string date)
{
    double Res = INP_value * DB_value;
    std::cout << date << " => " << Res << std::endl;
}

bool BitcoinExchange::calcul(std::string date, std::string svalue, data_M &data)
{
    char *endptr;

    double value = std::strtod(svalue.c_str(), &endptr);
    if (endptr == svalue.c_str())
        return (std::cout << "Error: not a valid number." << std::endl, false);
    if (value < 0)
        return (std::cout << "Error: not a valid number." << std::endl, false);
    if (value > 1000)
        return (std::cout << "Error: too large a number." << std::endl, false);
    if (data.empty())
        return (std::cout << "Error: database is empty" << std::endl, false);

    data_M::iterator it = data.lower_bound(date);
    
        if ( it != data.end() && it->first == date)
        {
            printRes(value, it->second, it->first);
            return (true);
        }
         else
        {
            if (it != data.begin())
                 it--;
            else
                return (std::cout << "Error: Bad Input !", false);
             printRes(value, it->second, it->first);
             return (true);
         }     
    return (false);

}