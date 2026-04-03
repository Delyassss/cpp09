#include "PmergeMe.hpp"

bool digits(std::string str)
{
    int i = 0;
    if (str.empty())
        return std::cerr << "Error\n", false;
    if (str[0] == '-')
        return std::cerr << "Error\n", false;
    if (str[0] == '+')
        i++;

    for (; str[i]; i++)
    {
        if (!isdigit(str[i]) )
            return false;
    }
    return true;
}

bool PmergeMe::parse_args(char **argv)
{
    std::vector<std::pair<int, int> > &v = this->getPairs();
    std::pair<int, int> p;
    if (!argv || !argv[1])
        return (std::cerr << "Error\n", false);
    
    for (int i = 1; argv[i]; i++)
    {
        if (!digits(argv[i]))
            return (std::cerr << "Error\n", false);
        if (i % 2 == 0)
        {
            p.first = std::max(atoi(argv[i - 1]), atoi(argv[i]));
            p.second = std::min(atoi(argv[i - 1]), atoi(argv[i]));
            v.push_back(p);
        }
        if (!argv[i + 1] && !(i % 2 == 0))
            this->setRemainingV(atoi(argv[i]));
    }
    return true;
}

thePairs &PmergeMe::getPairs()
{
    return this->v;
}

thePairs PmergeMe::sortPairs(thePairs &v)
{
    if (v.size() < 2)
        return v;

    size_t mid = v.size() / 2;

    thePairs::iterator it = v.begin();
    thePairs::iterator itmid = it + mid;

    thePairs left(it, itmid);
    thePairs right(itmid, v.end());

    left = sortPairs(left);
    right = sortPairs(right);

    if (left.[0].first > right[0].first.first)
        std::swap(left, right);
    
    thePairs &res = this->getResult();
    res.push_back(left[0]);
    res.push_back(right[0]);
    
}

thePairs &PmergeMe::getResult()
{
    return this->result;
}

PmergeMe::PmergeMe(char **argv)
{
    this->remainingV = 0;
    if (!this->parse_args(argv))
        return ;
    
    
}

PmergeMe::~PmergeMe()
{
    

}

unsigned long PmergeMe::getRemainingV()
{
    return this->remainingV;
}

void PmergeMe::setRemainingV(unsigned long value)
{
    this->remainingV = value;
}
