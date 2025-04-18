#include <cstdint>
#include <iostream>
#include "goldilocks.h"
// p = 2^64 - 2^32 + 1

typedef uint64_t i64;
typedef __uint128_t i128;

goldilocks::goldilocks(i64 v){
    val = v % p;
}
// goldilocks::goldilocks() : val(0) {}
goldilocks goldilocks::operator+(const goldilocks& n) const{
    i128 sum = (i128)val + n.val;
    return goldilocks((i64)(sum % p));
}
goldilocks goldilocks::operator-(const goldilocks& n) const{
    i128 sum = (i128)p + val - n.val;
    return goldilocks((i64)(sum % p));
}
goldilocks goldilocks::operator*(const goldilocks& n) const{
    i128 product = (i128)val * n.val;
    return goldilocks((i64)(product % p));
}
bool goldilocks::operator==(const goldilocks& n) const{
    return val == n.val;
}
goldilocks& goldilocks::operator=(const i64 n){
    val = n % p;
    return *this;
}
goldilocks& goldilocks::operator=(const goldilocks& n){
    if(this != &n){
        val = n.val;
    }
    return *this;
}
void goldilocks::print() const {
    std::cout << val << std::endl;
}

goldilocks goldilocksFp2::w = 7;
goldilocksFp2::goldilocksFp2(i64 a, i64 b):a(goldilocks(a)),b(goldilocks(b)){}
goldilocksFp2::goldilocksFp2(goldilocks a, goldilocks b):a(a),b(b){}
goldilocksFp2 goldilocksFp2::operator+(const goldilocksFp2& n) const{
    return goldilocksFp2(a + n.a, b + n.b);
}
goldilocksFp2 goldilocksFp2::operator-(const goldilocksFp2& n) const{
    return goldilocksFp2(a - n.a, b - n.b);
}
goldilocksFp2 goldilocksFp2::operator*(const goldilocksFp2& n) const{
    goldilocks ac = a * n.a;
    goldilocks bd = b * n.b;
    goldilocks ad = a * n.b;
    goldilocks bc = b * n.a;
    return goldilocksFp2(ac + bd * w, ad + bc);
}
void goldilocksFp2::print() const{
    std::cout << a.val << " + " << b.val << "ω" << std::endl;
}