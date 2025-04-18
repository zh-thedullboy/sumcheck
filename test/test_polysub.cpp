#include "mvpoly.h"
#include "goldilocks.h"
#include <iostream>


int main() {
    // 创建一个 3 变量的多项式 P(x, y, z) = 3xyz + 2y^2 + z
    Poly p({goldilocks(1), goldilocks(1), goldilocks(1)}); // 最大次数不重要，只需要能覆盖用到的次数
    p.add_term({1, 1, 1}, goldilocks(3)); // 3 * x * y * z
    p.add_term({0, 2, 0}, goldilocks(2)); // 2 * y^2
    p.add_term({0, 0, 1}, goldilocks(1)); // z
    p.add_term({1, 1, 3}, goldilocks(1));
    p.add_term({1, 1, 3}, goldilocks(1));
    p.add_term({1, 1, 3}, goldilocks((((1ull << 32) - 1) << 32) + 1 - 2));

    Poly f = Poly();
    std::cout << "Original Polynomial:\n";
    p.print();
    p.evaluate({3, 3, 3}).print();

    // 替换 x=1, y=2  => r = 2, mask = {2}
    std::vector<goldilocks> mask = {1, 3};
    
    Poly q = p.subsr(1, mask); // 保留变量 x

    std::cout << "\nAfter Substitution (x=1, y=2):\n";
    q.print();

    // 你期望输出的是：
    // 3 * 1 * 2 * z = 6z
    // 2 * 2^2 = 8 (常数项)
    // z = z
    // 最终应该是：6z + z + 8 = 7z + 8
}
