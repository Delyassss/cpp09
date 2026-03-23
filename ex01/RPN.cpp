#include "RPN.hpp"
RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(RPN const &src)
{
    *this = src;
}

RPN &RPN::operator=(RPN const &rhs)
{
    if (this != &rhs)
    {
        this->mycontsiner = rhs.mycontsiner;
        this->myoperators = rhs.myoperators;
    }
    return (*this);
}

Oper &RPN::getOperators()
{
    return (myoperators);
}

stackk &RPN::getContainer()
{
    return (mycontsiner);
}

void removeOperators(std::string line, std::string &res, std::string &operators)
{

    for (size_t i = 0; i < line.length(); i++)
    {
        if (line[i] != '+' && line[i] != '-' && line[i] != '*' && line[i] != '/')
            res += line[i];
        else
            operators += line[i];
    }
}

bool notOperator(char c)
{
    if (c != '+' && c != '-' && c != '*' && c != '/')
        return (true);
    return (false);
}

int Itemcheck(std::string item)
{
    if (item.empty() || item.size() > 1)
        return (std::cerr << "Error" << std::endl, 0);
    if (notOperator(item[0]) && !std::isdigit(item[0]))
        return (std::cerr << "Error" << std::endl, 0);

    return (1);
}

int execute(stackk &mystack, std::string oper)
{
    long Right = mystack.top();
        mystack.pop();
    
    if (mystack.empty()) // in case if we dont have pair for the math 
        return (std::cerr << "Error" << std::endl, 0);

    long Left = mystack.top();
        mystack.pop();

        if (oper == "+")
            mystack.push(Left + Right);
        if (oper == "-")
            mystack.push(Left - Right);
        if (oper == "*")
            mystack.push(Left * Right);
        if (oper == "/")
            mystack.push(Left / Right);

    return (mystack.top());
}

void RPN::parsing(std::string line)
{
    long nb;
    stackk   mystack = getContainer();
    std::string trimOper;
    std::string Oper;
    
    if (line.empty())
        return ;
    
    removeOperators(line, trimOper, Oper);

    std::stringstream ss(line.c_str());
    std::string item;

    while (std::getline(ss, item, ' '))
    {
        
        if (item.empty())
            continue;

        if (!Itemcheck(item))
            return ;

        if (!notOperator(item[0]))
            execute(mystack, item);
        else
        {
            nb = std::atol(item.c_str());
            mystack.push(nb);
        }        
        item.clear();
    }
    if (Oper.empty() || mystack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return ;
    }
    std::cout << mystack.top() << std::endl;
}