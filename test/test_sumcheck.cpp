#include "sumcheck.h"
#include "mvpoly.h"
#include "goldilocks.h"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cassert>


/*
returns a polynomial with nvar variables and degree of each is consistently degree
*/
Poly get_random_polynomial(unsigned nvar = 0, unsigned degree = 3){
    std::string get_base(unsigned num, const unsigned n, const unsigned base){
        if (base < 2 || base > 36) {
            throw std::invalid_argument("Base must be in range 2-36");
        }
    
    
        const std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string result = "";
    
        while (num > 0) {
            result += digits[num % base];
            num /= base;
        }
    
        std::reverse(result.begin(), result.end());
        if(result.length() != n){
            return std::string(n - result.length(), '0') + result;
        }
        return result;
    }

    assert(degree <= 8);
    using std::vector;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, GOLDILOCKS_ORDER);

    if(nvar == 0)  nvar = 5;
    vector<goldilocks> deg;
    
    // as the degree actually doesn't matter, let the order in each variable consistent
    // this way generating random monomials will be more convenient :)
    for(int i = 0; i < nvar; ++i){
        deg.push_back(goldilocks(degree));
    }
    Poly g(deg);


    // all variables were set to max_degree degree. we can view the monomials as a base-degree nvar-digit number
    // max_mask shouldn't be too large
    assert(nvar * std::log2(degree + 1) < 32);
    unsigned max_mask = (unsigned)std::pow(degree + 1, nvar);
    for(unsigned x = 0; x < max_mask; ++x){
        std::string bit_x = get_base(x, nvar, degree + 1);
        std::vector<goldilocks> exp = {};
        for(const auto& bit: bit_x){
           exp.push_back(goldilocks(bit - '0'));
        }
        goldilocks coef = dis(gen) % 90 + 10;
        g.add_term(exp, coef);
    }
    return g;
}


int main(){

    Poly g = get_random_polynomial(7, 3);
    g.print();
    Prover pr(g);
    Verifier ve(g, g);
    bool suc = ve.exec_proto(pr);
    if(!suc) std::cout << "sumcheck failed \n";
    return 0;
}