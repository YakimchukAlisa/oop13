#pragma once
#include <vector>
#include <memory>
#include <string>

class Product;

// Хранитель состояния корзины
class CartMemento {
private:
    std::vector<std::shared_ptr<Product>> savedItems;
    double savedTotalPrice;
    double savedTotalWeight;

public:
    CartMemento(const std::vector<std::shared_ptr<Product>>& items,
        double totalPrice, double totalWeight);

    std::vector<std::shared_ptr<Product>> getItems() const { return savedItems; }
    double getTotalPrice() const { return savedTotalPrice; }
    double getTotalWeight() const { return savedTotalWeight; }
};