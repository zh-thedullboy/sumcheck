#ifndef MVPOLY_H_
#define MVPOLY_H_

#include "goldilocks.h"
#include <vector>
#include <map>
#include <iostream>

using std::map;
using std::vector;

// fast exponentiation on goldilocks field
goldilocks fpow(goldilocks base_, goldilocks exp_);

// comparer
struct goldilocks_vector_less {
    bool operator()(const std::vector<goldilocks>& a, const std::vector<goldilocks>& b) const {
      size_t n = std::min(a.size(), b.size());
      for (size_t i = 0; i < n; ++i) {
        if (a[i].val != b[i].val)
          return a[i].val > b[i].val;
      }
      return a.size() > b.size();
    }
};
  
// viewing the multi-variate polynomial as a combination of monomials
class Poly{
public:
    typedef vector<goldilocks> mono_t;
    typedef goldilocks coef_t;
    typedef vector<goldilocks> deg_t;
    typedef vector<goldilocks> assign_t;
 private:
    unsigned nvar;  // number of variables
public:
    map<mono_t, coef_t, goldilocks_vector_less> monomials;
    Poly(deg_t deg = {});
    goldilocks evaluate(assign_t assign);
    void add_term(const mono_t& exp, coef_t coef);
    unsigned get_nvar() const{return nvar;}
    // get degree of x_i (index starts from 0 !!!)
    deg_t deg; // max degree wrt specific variables
    goldilocks get_deg(int i) const{return deg[i];}
    // substitute some x_i-s with specific number for all i >= r    i.e. partly assign
    Poly subsr(unsigned r, assign_t mask);
    Poly subsl(assign_t mask);
    Poly operator+(const Poly& other)const;
    void print() const{
        bool first = true;
        for (const auto& [exp, coef] : monomials) {
            if (!first) std::cout << " + ";
            first = false;
    
            // 打印系数
            std::cout << coef.val;
    
            // 打印每个变量的指数（形如 x0^2 x1^3 ...）
            for (size_t i = 0; i < exp.size(); ++i) {
                if (exp[i].val != 0) {
                    std::cout << "*x" << i + 1;
                    if (exp[i].val != 1) {
                        std::cout << "^" << exp[i].val;
                    }
                }
            }
        }
        if (first) std::cout << "0";  // 没有任何项
        std::cout << std::endl;
    }
};

#endif