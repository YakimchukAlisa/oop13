#include "InventorySystem.h"
#include <iostream>

void InventorySystem::onWeightBelowThreshold(int shelfId, const std::string& productName,
    double currentWeight, double threshold) {
    std::cout << "\n  [СИСТЕМА УЧЁТА] Автоматическая обработка:\n";
    std::cout << "     Полка #" << shelfId << " (" << productName
        << ") осталось " << currentWeight << " г (ниже " << (threshold * 100) << "%)\n";
    std::cout << "     АВТОМАТИЧЕСКИ создаю заказ поставщику на товар '" << productName << "'\n";
    std::cout << "     Отправляю запрос на склад\n";
    autoOrderRequests[shelfId] = productName;
}

void InventorySystem::onWeightChanged(int shelfId, double oldWeight, double newWeight) {
    // Система учёта логирует изменения для аналитики
    std::cout << "  [СИСТЕМА УЧЁТА] Логирование: полка #" << shelfId
        << " изменила вес: " << oldWeight << " -> " << newWeight << " г\n";
}

void InventorySystem::showAutoOrders() const {
    if (autoOrderRequests.empty()) {
        std::cout << "  [СИСТЕМА УЧЁТА] Нет активных заказов\n";
    }
    else {
        std::cout << "  [СИСТЕМА УЧЁТА] Активные заказы поставщикам:\n";
        for (const auto& order : autoOrderRequests) {
            std::cout << "    - Полка #" << order.first << ": " << order.second << " (ожидается доставка)\n";
        }
    }
}