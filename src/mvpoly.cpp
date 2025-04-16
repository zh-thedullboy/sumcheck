#include "goldilocks.h"
#include "mvpoly.h"
#include <vector>
#include <cstdint>

goldilocks fpow(goldilocks base_, goldilocks exp_) {
    __uint128_t base = base_.val;
    uint64_t exp = exp_.val;
    uint64_t p = (((1ull << 32) - 1) << 32) + 1;

    __uint128_t result = 1;
    while (exp > 0) {
      if (exp & 1)
        result = (result * base) % p;
      base = (base * base) % p;
      exp >>= 1;
    }

    return goldilocks((uint64_t)result);
}

Poly::Poly(deg_t edg){
    deg = deg;
    nvar = deg.size();
    monomials = {};
}

void Poly::add_term(const mono_t& exp, coef_t coef){
    auto it = monomials.find(exp);
    bool exists = (it == monomials.end());

    // goldilocks忘了写 == 运算符了,暂时先这样搞... 
    if(goldilocks(coef).val == 0){
        if(exists){
            monomials.erase(exp);
        }
    }else{
        monomials[exp] = coef;
    }
}

goldilocks Poly::evaluate(assign_t assign){
    goldilocks res = 0;
    for(const auto& [exp, coef] : monomials){
        goldilocks m = 0;
        for(int i = 0;i < nvar; ++i){
            m = m * fpow(assign[i], exp[i]);
        }
        res = res + m;
    }
    return res;
}