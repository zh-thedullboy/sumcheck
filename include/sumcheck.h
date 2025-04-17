#ifndef SUMCHECK_H_
#define SUMCHECK_H_

#include "goldilocks.h"
#include "mvpoly.h"
#include <iostream>
#include <vector>

// case where verifier doesn't know about g

class Prover{
    private:
        Poly g;
        unsigned nvar;
        unsigned nrnd;
    public:
        Prover(const Poly& g);
        Poly get_sum(const unsigned round, const vector<goldilocks>& r);
};

#endif