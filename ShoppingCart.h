#pragma once
#include <vector>
#include <memory>
#include <stack>
#include "CartMemento.h"
#include "Product.h"
#include "Customer.h"

class ShoppingCart {
    int cartId;
    int customerId;
    std::vector<std::shared_ptr<Product>> items;
    double totalPrice;
    double totalWeight;
private:
    std::stack<std::shared_ptr<CartMemento>> undoStack;
    static const size_t MAX_UNDO_SIZE = 10;

public:
    ShoppingCart(int id, int custId);
    void addItem(std::shared_ptr<Product> product);
    double calculateTotal();
    double calculateTotalWeight();
    double calculateFinalPrice(std::shared_ptr<Customer> customer);
    void displayCart() const;
    void saveState();                           // сохранить текущее состояние
    bool undo();                                // отменить последнее действие
    bool canUndo() const { return !undoStack.empty(); }
    void clearHistory();                        // очистить историю
};