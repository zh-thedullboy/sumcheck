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

Poly::Poly(deg_t deg):deg(deg){
    nvar = deg.size();
    monomials = {};
}

void Poly::add_term(const mono_t& exp, coef_t coef){
    auto it = monomials.find(exp);
    bool exists = (it != monomials.end());

    // goldilocks忘了写 == 运算符了,暂时先这样搞... 
    if(goldilocks(coef).val != 0){
        if(exists){
            monomials[exp] = monomials[exp] + coef;
            if(monomials[exp].val == 0) monomials.erase(exp);
        }else{
            monomials[exp] = coef.val;
// debug use

// std::cout << "Inserting: ";
// for (const auto& e : exp) {
//     std::cout << e.val << " ";
// }
// std::cout << " => " << coef.val << std::endl;

// monomials[exp] = coef;

// // Print map content after insertion
// std::cout << "Map content after insertion:" << std::endl;
// for (const auto& [exp_key, coef_val] : monomials) {
//     std::cout << "Exp: ";
//     for (const auto& e : exp_key) {
//         std::cout << e.val << " ";
//     }
//     std::cout << "=> " << coef_val.val << std::endl;
// }

        }
    }
}

goldilocks Poly::evaluate(assign_t assign) const{
    goldilocks res = 0;
    for(const auto& [exp, coef] : monomials){
        goldilocks m = coef;
        for(int i = 0;i < nvar; ++i){
            m = m * fpow(assign[i], exp[i]);
        }
        res = res + m;
    }
    return res;
}

Poly Poly::subsr(unsigned r, assign_t mask) const{
    deg_t newdeg(deg.begin(), deg.begin() + r);
    Poly sr(newdeg);
    for(const auto& [exp, coef] : monomials){
        coef_t newcoef = coef;
        for(int i = r;i < nvar; ++i){
            newcoef = newcoef * fpow(mask[i - r], exp[i]);
        }
        mono_t mono(exp.begin(), exp.begin() + r);
        sr.add_term(mono, newcoef);
    }
    return sr;
}

Poly Poly::subsl(assign_t mask) const{
    unsigned r = mask.size();
    deg_t newdeg(deg.begin() + r, deg.end());
    Poly sl(newdeg);
    for(const auto& [exp, coef] : monomials){
        coef_t newcoef = coef;
        for(int i = 0;i < r; ++i){
            newcoef = newcoef * fpow(mask[i], exp[i]);
        }
        mono_t mono(exp.begin() + r, exp.end());
        sl.add_term(mono, newcoef);
    }
    return sl;
}

goldilocks max(goldilocks a, goldilocks b){
    return (a.val > b.val) ? a: b;
}

Poly Poly::operator+(const Poly& other) const{
    deg_t newdeg = {};
    for(int i = 0;i < deg.size(); ++i){
        newdeg.push_back(max(deg[i], other.deg[i]));
    }
    Poly res = Poly(newdeg);
    for(const auto& [exp, coef] : monomials){
        res.add_term(exp, coef);
    }
    for(const auto& [exp, coef] : other.monomials){
        res.add_term(exp, coef);
    }
    return res;
}

bool Poly::operator==(const Poly& other) const{
    for(const auto& [exp, coef] : monomials){
        if(!(other.monomials.at(exp) == coef)) return false;
     }
    for(const auto& [exp, coef] : other.monomials){
        if(!(monomials.at(exp) == coef)) return false;
    }
    return true;
}

void Poly::print() const{
    bool first = true;
    for (const auto& [exp, coef] : monomials) {
        if (!first) std::cout << " + ";
        first = false;

        // print coefficient
        std::cout << coef.val;

        // print exponentiations
        for (size_t i = 0; i < exp.size(); ++i) {
            if (exp[i].val != 0) {
                std::cout << "*x" << i + 1;
                if (exp[i].val != 1) {
                    std::cout << "^" << exp[i].val;
                }
            }
        }
    }
    if (first) std::cout << "0";  // empty polynomial
    std::cout << std::endl;
}