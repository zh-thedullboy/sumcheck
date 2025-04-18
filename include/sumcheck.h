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
        Poly get_sum(const unsigned round, const std::vector<goldilocks>& r) const;
};

class Verifier{
    typedef Poly Oracle;
    private:
        Poly g;
        Oracle oracle;
        unsigned nvar;
        unsigned nrnd;
        std::vector<goldilocks> challenges;
        std::vector<goldilocks> get_random(const unsigned round) const;
    public:
        Verifier(Poly g, Oracle oracle);
        bool exec_proto(const Prover& prover) const;
};

#endif