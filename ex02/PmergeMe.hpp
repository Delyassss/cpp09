#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include "iostream"
#include "deque"
#include "vector"
#include "algorithm"
#include <time.h>
#include <sys/time.h>
#include <iomanip>

typedef std::vector<std::pair<unsigned long, unsigned long> > thePairs;
typedef std::deque<unsigned long> Loser;
typedef std::deque<unsigned long> Winner;


class PmergeMe
{
    private :
        unsigned long remainingV;
        thePairs v;
        thePairs result;
        bool                      Remainingflag;
        std::deque<unsigned long> loser;
        std::deque<unsigned long> winner;
        std::deque<unsigned long> Jacobsthal;
        double first_algo_time;
        double second_algo_time;
        long     range;




        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
     
    public :
        PmergeMe(char **argv , int argc);
        ~PmergeMe();
        unsigned long getRemainingV();
        void        setRemainingV(unsigned long value);
        bool        parse_args(char **argv, int argc);
        thePairs    &getPairs();
        thePairs    sortPairs(thePairs &v);
        thePairs    &getResult();
        bool        LosersAndWinners(Loser &losers, Winner &winners);
        Loser       &getlosers();
        Winner        &getwinners();
        std::deque<unsigned long> &generate_Jacobsthal(std::deque<unsigned long> &Jacobsthal);
        bool        &has_remaining_value();
        void        set_remaining_value(bool flag);
        void        Output(Winner &winners, char **argv , int argc);
        double      &get_first_algo_time();
        double      &get_second_algo_time();
        long        &get_range();






};


#endif