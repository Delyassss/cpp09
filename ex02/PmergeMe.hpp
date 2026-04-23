#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include "iostream"
#include "deque"
#include "vector"
#include "algorithm"
#include <time.h>
#include <sys/time.h>
#include <iomanip>
#include <stdlib.h>

typedef std::deque<std::pair<unsigned long, unsigned long> > thePairs;
typedef std::deque<unsigned long> Loser;
typedef std::deque<unsigned long> Winner;

typedef std::vector<std::pair<unsigned long, unsigned long> > vecPairs;
typedef std::vector<unsigned long> vecLoser;
typedef std::vector<unsigned long> vecWinner;


class PmergeMe
{
    private :
        unsigned long             remainingV;
        thePairs v;
        vecPairs vecpairs;
        bool                      Remainingflag;
        Loser loser;
        Loser winner;
        vecLoser vecloser;
        vecWinner vecwinner;
        std::deque<unsigned long> Jacobsthal;
        double first_algo_time;
        long     range;
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        
        


        
        public :
        PmergeMe(char **argv , int argc);
        ~PmergeMe();
        unsigned long               getRemainingV();
        void                        setRemainingV(unsigned long value);
        bool                        parse_args(char **argv, int argc);
        std::deque<unsigned long>   &generate_Jacobsthal(std::deque<unsigned long> &Jacobsthal);
        bool                        &has_remaining_value();
        void                        set_remaining_value(bool flag);
        long                        &get_range();
        
        
        
        
        /*                                        deque                                        */
        void        mergeInsert(thePairs &pairs, char **argv, int argc);
        void        Output(Winner &winners, char **argv , int argc);
        thePairs    &getPairs();
        thePairs    sortPairs(thePairs &v);
        bool        LosersAndWinners(Loser &losers, Winner &winners);
        Loser       &getlosers();
        Winner      &getwinners();
        
        

    /*                                        vector                                        */
        void        mergeInsert(vecPairs &pairs, char **argv, int argc);
        void        Output(vecWinner &winners, char **argv , int argc);
        vecLoser    &getveclosers();
        vecWinner   &getvecwinners();
        vecPairs    sortPairs(vecPairs &v);
        vecPairs    &getvecPairs();
        bool        LosersAndWinners(vecLoser &losers, vecWinner &winners);






};


#endif