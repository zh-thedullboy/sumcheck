#include "goldilocks.h"
#include "mvpoly.h"
#include <iostream>
using namespace std;
int main(){
    goldilocks a = goldilocks((1ull << 63) + 239311341);
    goldilocks b = a * a * a * a * a;
    goldilocks c = fpow(a, goldilocks(5));
    a.print();
    b.print();
    c.print();
    return 0;
}