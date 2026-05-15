#include "ShopSimulation.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Система автоматизации магазина ===\n";

    ShopSimulation shop;
    shop.initialize();
    shop.runSimulation();

    return 0;
}