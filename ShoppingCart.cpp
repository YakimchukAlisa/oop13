#include "ShoppingCart.h"
#include "CartMemento.h"
#include <iostream>
#include <iomanip>

ShoppingCart::ShoppingCart(int id, int custId)
    : cartId(id), customerId(custId), totalPrice(0), totalWeight(0) {}

void ShoppingCart::addItem(std::shared_ptr<Product> product) {
    saveState();
    items.push_back(product);
    totalPrice += product->getPrice();
    totalWeight += product->getWeight();
    std::cout << "Корзина: добавлен " << product->getName() << " (" << product->getPrice() << " руб.)\n";
}


double ShoppingCart::calculateTotal() {
    totalPrice = 0;
    for (auto& p : items) totalPrice += p->getPrice();
    return totalPrice;
}

double ShoppingCart::calculateTotalWeight() {
    totalWeight = 0;
    for (auto& p : items) totalWeight += p->getWeight();
    return totalWeight;
}

double ShoppingCart::calculateFinalPrice(std::shared_ptr<Customer> customer) {
    double base = calculateTotal();
    double discount = customer->getDiscount(base);  
    return base - discount;
}

void ShoppingCart::displayCart() const {
    std::cout << "\n=== Корзина ID " << cartId << " ===\n";
    for (auto& p : items)
        std::cout << "  " << p->getName() << " — " << p->getPrice() << " руб., " << p->getWeight() << " г\n";
    std::cout << "Итого: " << totalPrice << " руб., вес: " << totalWeight << " г\n";
}

void ShoppingCart::saveState() {
    // Создаем снимок текущего состояния
    auto memento = std::make_shared<CartMemento>(items, totalPrice, totalWeight);

    // Ограничиваем размер истории
    if (undoStack.size() >= MAX_UNDO_SIZE) {
        std::stack<std::shared_ptr<CartMemento>> newStack;
        // Пропускаем самый старый (нижний) элемент
        while (undoStack.size() > 1) {
            newStack.push(undoStack.top());
            undoStack.pop();
        }
        undoStack = newStack;
    }

    undoStack.push(memento);
    std::cout << "\n  [Memento] Состояние корзины сохранено\n";
}

bool ShoppingCart::undo() {
    if (undoStack.empty()) {
        std::cout << "\n  [Memento] Нечего отменять\n";
        return false;
    }

    // Восстанавливаем состояние
    auto memento = undoStack.top();
    undoStack.pop();

    items = memento->getItems();
    totalPrice = memento->getTotalPrice();
    totalWeight = memento->getTotalWeight();

    std::cout << "\n  [Memento] Последнее действие отменено!\n";
    return true;
}

void ShoppingCart::clearHistory() {
    while (!undoStack.empty()) {
        undoStack.pop();
    }
    std::cout << "\n  [Memento] История операций очищена\n";
}