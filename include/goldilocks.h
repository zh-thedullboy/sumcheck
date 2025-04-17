#ifndef _GOLDILOCKS_H_
#define _GOLDILOCKS_H_

#include <cstdint>
typedef uint64_t i64;
typedef __uint128_t i128;
class goldilocks{
    private:
        i64 p = (((1ull << 32) - 1) << 32) + 1;
    public:
        i64 val;
        goldilocks(i64 v = 0);
        // goldilocks();
        goldilocks  operator+(const goldilocks& n) const;
        goldilocks  operator-(const goldilocks& n) const;
        goldilocks  operator*(const goldilocks& n) const;
        goldilocks&  operator=(const i64 n);
        goldilocks&  operator=(const goldilocks& n);
        goldilocks minus(i64 v);
        void print() const;
};

class goldilocksFp2{
    private:
        static goldilocks w; // ω^2 = w
    public:
        goldilocks a, b;
        goldilocksFp2(i64 a, i64 b);
        goldilocksFp2(goldilocks a, goldilocks b);
        goldilocksFp2  operator+(const goldilocksFp2& n) const;
        goldilocksFp2  operator-(const goldilocksFp2& n) const;
        goldilocksFp2  operator*(const goldilocksFp2& n) const;
        void print() const;
};

#endif