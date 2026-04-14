#include "PmergeMe.hpp"
double time_me(struct timeval start, struct timeval end);
// void print_me(thePairs &v, std::deque<unsigned long> &data)
// {
//     if (!v.empty())
//     {
//         std::cout << "Pairs :";
//         for (size_t i = 0; i < v.size(); i++)
//         {
//             std::cout << " " << v[i].first << " " << v[i].second;
//             if (i == v.size() - 1)
//             {
//                 std::cout << " " << std::endl;
//             }
//         }
//     }
//     if (!data.empty())
//     {
//         for (size_t i = 0; i < data.size(); i++)
//         {
//             std::cout << " " << data[i] << " ";
//             if (i == data.size() - 1)
//             {
//                 std::cout << " " << std::endl ;
//             }
//         }
//     }
    
// }
void PmergeMe::Output(Winner &winners, char **argv, int argc)
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

    double first_algo_time = get_first_algo_time();
    double second_algo_time = get_second_algo_time();
    std::cout << "Time to process a range of " << get_range() << " elements with std::vector : " << first_algo_time<< " us" << std::endl;
    std::cout << "Time to process a range of " << get_range() << " elements with std::deque : "<< second_algo_time << " us" << std::endl;
}

PmergeMe::PmergeMe(char **argv, int argc)
{
    struct timeval start1 , end1 , start2, end2;
    this->first_algo_time = 0;
    this->second_algo_time = 0;
    this->remainingV = 0;
    this->Remainingflag = false;

    if (!this->parse_args(argv, argc))
        return ;

    gettimeofday(&start1, NULL);
        sortPairs(this->getPairs());
    gettimeofday(&end1, NULL);
    this->first_algo_time = time_me(start1, end1);  

    gettimeofday(&start2, NULL);
        if (!LosersAndWinners(getlosers(), getwinners()))
        {
            std::cerr << "Error\n";
            return ;
        }
    gettimeofday(&end2, NULL);
    this->second_algo_time = time_me(start2, end2);

    Output(this->getwinners() , argv , argc);



    
    
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
    std::pair<int, int> p;

    if (!argv || !argv[1])
        return (std::cerr << "Error\n", false);
    
    for (int i = 1; argv[i]; i++)
    {
        if (!digits(argv[i]))// not a digit 
            return (std::cerr << "Error\n", false);
        
        if (i % 2 == 0) // pairing 
        {
            p.first = std::max(atoi(argv[i - 1]), atoi(argv[i])); // so the first is the higher value 
            p.second = std::min(atoi(argv[i - 1]), atoi(argv[i]));
            v.push_back(p);
        }
        if (i + 1 >= argc && !(i % 2 == 0)) // if we have an odd container
        {
            set_remaining_value(true);
            this->setRemainingV(atoi(argv[i]));
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
    double res = micro + sec / 1000000.0;  
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

thePairs &PmergeMe::getResult()
{
    return this->result;
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

bool PmergeMe::LosersAndWinners(Loser &losers, Winner &winners)
{
    thePairs &res = this->getPairs();
    if (res.empty())
        return false;

    thePairs::iterator it = res.begin();

    // create 2 seperated deque
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
    // now the Remaining value
    if (has_remaining_value())
    {
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

double &PmergeMe::get_first_algo_time()
{
    return this->first_algo_time;
}

double &PmergeMe::get_second_algo_time()
{
    return this->second_algo_time;
}

long &PmergeMe::get_range()
{
    return this->range;
}
