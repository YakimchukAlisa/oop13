#include "CartMemento.h"
#include "Product.h"

CartMemento::CartMemento(const std::vector<std::shared_ptr<Product>>& items,
    double totalPrice, double totalWeight)
    : savedItems(items), savedTotalPrice(totalPrice), savedTotalWeight(totalWeight) {
}