#include "mvpoly.h"
#include "goldilocks.h"
#include "sumcheck.h"
#include <iostream>
#include <string>

// returns binary representation of x with left padding to length n
// std::string get_bin(const unsigned x, const unsigned n){
//     unsigned v = x;
//     std::string res("");
//     while(v){
//         if(v & 1) res = "1" + res;
//         else res = "0" + res;
//     }
    
//     if(res.length() != n){
//         return std::string(n - res.length(), '0') + res;
//     }
//     else return res;
// }

// Prover::Prover(const Poly& g){
//     this->g = g;
//     nvar = nrnd = g.get_nvar();
// }

// Poly Prover::get_sum(const unsigned round, const vector<goldilocks>& r){
//     std::cout<< "\nround" << round << '\n';
    
//     unsigned free_vars = nrnd - round;

//     goldilocks deg_j = round>0? g.get_deg(round - 1) : 0;
//     Poly g_j({goldilocks(deg_j)});

//     for(unsigned x = 0; x < 1ull << free_vars; ++x){
//         std::string bit_x = get_bin(x, free_vars);

//     }
// }