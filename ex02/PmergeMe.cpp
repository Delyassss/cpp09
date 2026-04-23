#include "PmergeMe.hpp"
double time_me(struct timeval start, struct timeval end);

PmergeMe::PmergeMe(char **argv, int argc)
{
    this->remainingV = 0;
    this->Remainingflag = false;

    if (!this->parse_args(argv, argc))
        throw std::runtime_error("") ;
}


void PmergeMe::Output(Winner &winners, char **argv, int argc)
{
     if (winners.empty())
     {
        std::cerr << "Error\n";
        return ;
     }
    std::cout << "Before :";
    for (int i = 1; i < argc; i++)
    {
        std::cout << " " << argv[i];
        if (i == argc - 1)
            std::cout << " " << std::endl;
    }
    std::cout << "After :";
    for (size_t i = 0; i < winners.size(); i++)
    {
        std::cout << " " << winners[i];
        if (i == winners.size() - 1)
            std::cout << " " << std::endl;
    }
}



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

bool PmergeMe::parse_args(char **argv, int argc)
{
    thePairs &v = this->getPairs();
    vecPairs &vecpairs = this->getvecPairs();
    std::pair<int, int> p;

    if (!argv || !argv[1])
        return (std::cerr << "Error\n", false);
    
    for (int i = 1; i < argc ; i++)
    {
        if (!digits(argv[i]))// not a digit 
            return (std::cerr << "Error\n", false);
        
        if (i % 2 == 0) // pairing 
        {
            p.first = std::max(std::atol(argv[i - 1]), std::atol(argv[i])); // so the first is the higher value 
            p.second = std::min(std::atol(argv[i - 1]), std::atol(argv[i]));
            v.push_back(p);
            vecpairs.push_back(p);

        }

        if (i + 1 >= argc && !(i % 2 == 0)) // if we have an odd container
        {
            set_remaining_value(true);
            this->setRemainingV(std::atol(argv[i]));
            return true;
        }
    }    
    return true;
}

thePairs &PmergeMe::getPairs()
{
    return this->v;
}

double time_me(struct timeval start, struct timeval end)
{
    double sec = end.tv_sec - start.tv_sec;
    double micro = end.tv_usec - start.tv_usec;
    double res = micro + (sec * 1000000.0);  
    return (res); 
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
    
    thePairs res ;
    size_t i = 0;
    size_t j = 0;

    while (i < left.size() && j < right.size()) // here we take the the lower pair and push it to res like if i > j ==> j++ and i stay the same to compare with the next j pair ...
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

    while (i < left.size()) // leftover basically the last pair has a higher value so we just push it back
    {
        res.push_back(left[i]);
        i++;
    }
    while (j < right.size()) 
    {
        res.push_back(right[j]);
        j++;
    }
    v = res;
    return v;
    
} 



std::deque<unsigned long> &PmergeMe::generate_Jacobsthal(std::deque<unsigned long> &Jacobsthal)
{
    size_t size = this->getlosers().size();

     if (size == 0)
        return Jacobsthal;

    Jacobsthal.push_back(0);
    if (size == 1)
        return Jacobsthal;
    Jacobsthal.push_back(1);


    for (size_t i = 2; i < size; i++)
    {
        Jacobsthal.push_back(Jacobsthal[i - 1] + (2 * Jacobsthal[i - 2]));
    }

    return Jacobsthal;
}

//for deque
bool PmergeMe::LosersAndWinners(Loser &losers, Winner &winners)
{
    thePairs &res = this->getPairs();
    if (res.empty())
        return false;

    thePairs::iterator it = res.begin();

    // create 2 seperated deque why deque cuz it better at insert he has a smart shift & no need to reallocate again if the memmory is full he can just ask the os for another memmort block and insert the new value 
    while (it != res.end())
    {
        winners.push_back(it->first); // so the first is the higher value in its own Pair but winners[i] < winners[i + 1] (winners are sorted)
        losers.push_back(it->second); // not sorted but we know they belong to an specific winner so winners[i] > loser[i] so we later we know the the index of loser ijd just before winner[i]
        it++;
    }

    std::deque<unsigned long > Jacob;
    this->generate_Jacobsthal(Jacob);  // its a sequence similar to fibonacci we use it to get the range of index we need to insert back in the winners

    int track  = 0;
    size_t end;
    size_t start ;
    Winner::iterator pos;

    for (size_t i = 0; i < Jacob.size(); i++)
    {
        start = Jacob[i];

        if (i == losers.size() - 1)
            end = losers.size();
        else
            end = Jacob[i + 1];

        if (end > losers.size())
            end = losers.size();
            
        while (end > start)
        {
            pos = std::lower_bound(winners.begin() , winner.begin() + (end + track), losers[end -1]);
            winners.insert(pos, losers[end - 1]);
            track++;  
            end--;
        }
    }
    get_range() = winners.size();
    // now the Remaining value
    if (has_remaining_value())
    { 
        get_range()++;
        pos = std::lower_bound(winners.begin() , winners.end(), getRemainingV());
        winners.insert(pos, getRemainingV());
    }
    return true;
}

Loser &PmergeMe::getlosers()
{

    return this->loser;
}

Winner &PmergeMe::getwinners()
{
    return this->winner;
}

bool &PmergeMe::has_remaining_value()
{
    return this->Remainingflag;
}

void PmergeMe::set_remaining_value(bool flag)
{
    this->Remainingflag = flag;
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



long &PmergeMe::get_range()
{
    return this->range;
}


void PmergeMe::mergeInsert(thePairs &pairs, char **argv, int argc)
{
    struct timeval start1 , end1;
    gettimeofday(&start1, NULL);

    sortPairs(pairs);
    
    if (!LosersAndWinners(getlosers(), getwinners()))
    {
        std::cerr << "Error\n";
        return ;
    }
    gettimeofday(&end1, NULL);

    Output(getwinners() , argv , argc);
    std::cout << "Time to process a range of " << get_range() << " elements with std::deque : " << time_me(start1, end1) << " us" << std::endl;
}





/*                                        vector                                        */

void PmergeMe::mergeInsert(vecPairs &pairs, char **argv, int argc)
{
    struct timeval start1 , end1;
    gettimeofday(&start1, NULL);

    sortPairs(pairs);
    
    if (!LosersAndWinners(getveclosers(), getvecwinners()))
    {
        std::cerr << "Error\n";
        return ;
    }
    gettimeofday(&end1, NULL);
    Output(getvecwinners() , argv , argc);
    std::cout << "Time to process a range of " << get_range() << " elements with std::vector : " << time_me(start1, end1) << " us" << std::endl;

}

vecPairs PmergeMe::sortPairs(vecPairs &v)
{
    if (v.size() < 2)
        return v;

    size_t mid = v.size() / 2;

    vecPairs::iterator it = v.begin();
    vecPairs::iterator itmid = it + mid;

    vecPairs left(it, itmid);
    vecPairs right(itmid, v.end());

    left = sortPairs(left);
    right = sortPairs(right);
    
    vecPairs res ;
    size_t i = 0;
    size_t j = 0;

    while (i < left.size() && j < right.size()) // here we take the the lower pair and push it to res like if i > j ==> j++ and i stay the same to compare with the next j pair ...
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

    while (i < left.size()) // leftover basically the last pair has a higher value so we just push it back
    {
        res.push_back(left[i]);
        i++;
    }
    while (j < right.size()) 
    {
        res.push_back(right[j]);
        j++;
    }
    v = res;
    return v;
    
} 

bool PmergeMe::LosersAndWinners(vecLoser &losers, vecWinner &winners)
{
    vecPairs &res = this->getvecPairs();
    if (res.empty())
        return false;

    vecPairs::iterator it = res.begin();

    // create 2 seperated deque why deque cuz it better at insert he has a smart shift & no need to reallocate again if the memmory is full he can just ask the os for another memmort block and insert the new value 
    while (it != res.end())
    {
        winners.push_back(it->first); // so the first is the higher value in its own Pair but winners[i] < winners[i + 1] (winners are sorted)
        losers.push_back(it->second); // not sorted but we know they belong to an specific winner so winners[i] > loser[i] so we later just insert loser[i] before winners[i]
        it++;
    }

    std::deque<unsigned long > Jacob;
    this->generate_Jacobsthal(Jacob);  // its a sequence similar to fibonacci we use it to get the range of index we need to insert back in the winners

    int track  = 0;
    size_t end;
    size_t start ;
    vecWinner::iterator pos;

    for (size_t i = 0; i < Jacob.size(); i++)
    {
        start = Jacob[i];

        if (i == losers.size() - 1)
            end = losers.size();
        else
            end = Jacob[i + 1];

        if (end > losers.size())
            end = losers.size();
            
        while (end > start)
        {
            pos = std::lower_bound(winners.begin() , winners.begin() + (end + track), losers[end -1]);
            winners.insert(pos, losers[end - 1]);
            track++;  
            end--;
        }
    }
    get_range() = winners.size();
    // now the Remaining value
    if (has_remaining_value())
    {
        get_range()++;
        pos = std::lower_bound(winners.begin() , winners.end(), getRemainingV());
        winners.insert(pos, getRemainingV());
    }
    return true;
}

vecPairs &PmergeMe::getvecPairs()
{
    return this->vecpairs;
}
vecLoser &PmergeMe::getveclosers()
{

    return this->vecloser;
}

vecWinner &PmergeMe::getvecwinners()
{
    return this->vecwinner;
}

void PmergeMe::Output(vecWinner &winners, char **argv, int argc)
{
     if (winners.empty() || v.empty())
     {
        std::cerr << "Error\n";
        return ;
     }
    std::cout << "Before :";
    for (int i = 1; i < argc; i++)
    {
        std::cout << " " << argv[i];
        if (i == argc - 1)
            std::cout << " " << std::endl;
    }
    std::cout << "After :";
    for (size_t i = 0; i < winners.size(); i++)
    {
        std::cout << " " << winners[i];
        if (i == winners.size() - 1)
            std::cout << " " << std::endl;
    }

}


