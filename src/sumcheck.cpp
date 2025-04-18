#include "mvpoly.h"
#include "goldilocks.h"
#include "sumcheck.h"
#include <iostream>
#include <string>
#include <random>

// returns binary representation of x with left padding to length n
std::string get_bin(const unsigned x, const unsigned n){
    unsigned v = x;
    std::string res("");
    while(v){
        if(v & 1) res = "1" + res;
        else res = "0" + res;
        v = v >> 1;
    }
    
    if(res.length() != n){
        return std::string(n - res.length(), '0') + res;
    }
    else return res;
}

Prover::Prover(const Poly& g){
    this->g = g;
    nvar = nrnd = g.get_nvar();
}

Poly Prover::get_sum(const unsigned round, const std::vector<goldilocks>& r) const{
    std::cout<< "\nround" << round << '\n';
    
    unsigned free_vars = nrnd - round;

    goldilocks deg_j = round>0? g.get_deg(round - 1) : 0;

    Poly g_j(std::vector<goldilocks>(g.deg.begin(), g.deg.begin() + round));

    for(unsigned x = 0; x < (1ull << free_vars); ++x){
        std::string bit_x = get_bin(x, free_vars);
        std::vector<goldilocks> assign = {};
        for(const auto& bit: bit_x){
            if(bit & 1) assign.push_back(1);
            else assign.push_back(0);
        }
        Poly res = g.subsr(round, assign);
        // res.print();
        // for(auto e: assign){
        //     e.print();
        // }
        // res.print();
        // std::cout<<'\n';
        for(const auto&[exp, coef]: res.monomials){
            g_j.add_term(exp, coef);
        }
        
    }
    std::cout << "g_j before random subs:";
    g_j.print();
    Poly s_j(g_j.subsl(r));
    std::cout << "g_j after random subs:";
    s_j.print();
    // if(round > 1){
    //     s_j = g_j.subsl(r);
    // }
    // s_j.print();
    return s_j;
}

Verifier::Verifier(Poly g, Oracle oracle):g(g), oracle(oracle){
    nrnd = nvar = g.get_nvar();
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, GOLDILOCKS_ORDER);
    for(int i = 0;i < nrnd; ++i){
        challenges.push_back(goldilocks(dis(gen)));
    }
} 

std::vector<goldilocks> Verifier::get_random(const unsigned round) const{
    if(round <= 1) return {};
    std::vector<goldilocks> r(challenges.begin(), challenges.begin() + round - 1);
    return r;
}

bool Verifier::exec_proto(const Prover& prover) const{
    goldilocks sum;
    Poly last_gj;
    for (int round = 0;round < nrnd + 1; ++round){
        std::vector<goldilocks> rands = get_random(round);
        Poly g_j = prover.get_sum(round, rands);
        if (round == 0) sum = g_j.monomials[{}];
        else if(round == 1){
            if(!(sum == g_j.evaluate({0}) + g_j.evaluate({1}))) return false;
        }
        else if(round > 1){
            // std::cout<< "last round received : ";
            // last_gj.print();
            // std::cout<< "this round received : ";
            // g_j.print();
            // std::cout<< "challenge : ";
            // challenges[round - 2].print();
            if(!(last_gj.evaluate({challenges[round - 2]}) == g_j.evaluate({0}) + g_j.evaluate({1}))) return false;
        }
        std::cout <<"safely passed round " << round << '\n';
        last_gj = g_j;
    }

    if(last_gj.evaluate({challenges[nrnd - 1]}) == oracle.evaluate(challenges)){
        std::cout<<"passed sum is " << sum.val << std::endl;
        return true;
    }
    else return false;
}