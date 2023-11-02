#include <iostream>
#include "BooleanFunction.hpp"

int main()
{
    BooleanFunction func{"10100110"};

    func.print();
    func.printDDNF();
    std::cout << std::endl;
    func.printDKNF();
    std::cout << std::endl;
    func.printGegalkin();

    std::cout << std::endl;

    auto temp = func.findDouble();

    if (func.remainsConstant(true)) {
        std::cout << "зберігає константу 1" << std::endl;
    }
    if (func.remainsConstant(false)) {
        std::cout << "зберігає константу 0" << std::endl;
    }
    if (func.isSelfDoubled()) {
        std::cout << "функція самодвоїста" << std::endl;
    }
    if (func.isMonotonic()) {
        std::cout << "функція монотонна" << std::endl;
    }
    if (func.isLinear()) {
        std::cout << "функція лінійна" << std::endl;
    }
}