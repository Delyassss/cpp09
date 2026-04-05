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
    
    thePairs &res = this->getResult();

    int i = 0;
    int j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i].first > right[j].first)
        {
            res.push_back(right[j]);
            j++;
        }
        else
        {
            res.push_back(left[i]);
            i++;
        }
    }

    while (i < left.size())
    {
        res.push_back(left[i]);
        i++;
    }
    while (j < right.size())
    {
        res.push_back(right[j]);
        j++;
    }
    return res;
    
} 

thePairs &PmergeMe::getResult()
{
    return this->result;
}

bool PmergeMe::LosersAndWinners(Loser &loser, Winner &winners)
{
    thePairs &res = this->getResult();

    thePairs::iterator it = res.begin();

    
    // Low value & High Value 
    while (it != res.end())
    {
        winners.push_back(it->first);
        losers.push_back(it->second);
        it++;
    }
    
    // we take those high numbers (second) and find the lowest value and 
    High::iterator h_it = winners.begin();
    Low::iterator l_it = losers.begin();

    while (l_it != losers.end())
    {
        Winner::iterator pos = std::lower_bound(h_it , winners.end(), *l_it);
        winners.insert(pos, *l_it);
        l_it++;
    }
    // now the Remaining value
    Winner::iterator pos = std::lower_bound(h_it , winners.end(), getRemainingV());
    winners.insert(pos, getRemainingV()); 

    return true;
}

losers &PmergeMe::getlosers()
{

    return this->losers;
}

winners &PmergeMe::getwinners()
{
    return this->winners;
}

PmergeMe::PmergeMe(char **argv)
{
    this->remainingV = 0;
    if (!this->parse_args(argv))
        return ;
    this->sortPairs(this->getPairs());

    
    
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
