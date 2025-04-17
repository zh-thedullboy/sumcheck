#include "mvpoly.h"
#include "goldilocks.h"
#include "sumcheck.h"
#include <iostream>
#include <string>

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

Poly Prover::get_sum(const unsigned round, const vector<goldilocks>& r){
    std::cout<< "\nround" << round << '\n';
    
    unsigned free_vars = nrnd - round;

    goldilocks deg_j = round>0? g.get_deg(round - 1) : 0;

    Poly g_j(vector<goldilocks>(g.deg.begin(), g.deg.begin() + round));

    for(unsigned x = 0; x < (1ull << free_vars); ++x){
        std::string bit_x = get_bin(x, free_vars);
        vector<goldilocks> assign = {};
        for(const auto& bit: bit_x){
            if(bit & 1) assign.push_back(1);
            else assign.push_back(0);
        }
        Poly res = g.subsr(round, assign);
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