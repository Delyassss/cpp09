#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include "iostream"
#include "deque"
#include "vector"
#include "algorithm"

typename std::vector<std::pair<unsigned long, unsigned long> > thePairs
class PmergeMe
{
    private :
        unsigned long remainingV ;
        thePairs v;
        thePairs result;

        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
     
    public :
        PmergeMe(char **argv);
        ~PmergeMe();
        unsigned long getRemainingV();
        void        setRemainingV(unsigned long value);
        bool        PmergeMe::parse_args(char **argv);
        thePairs    &getPairs();
        thePairs    sortPairs(thePairs &v);
        thePairs    &getResult();
}


#endif