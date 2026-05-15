#include "InventorySystem.h"
#include <iostream>

void InventorySystem::onWeightBelowThreshold(int shelfId, const std::string& productName,
    double currentWeight, double threshold) {
    std::cout << "  [ÑÈÑÒÅÌÀ Ó×¨ÒÀ] Ïîëêà #" << shelfId << " (" << productName
        << ") òðåáóåò ïîïîëíåíèÿ!\n";
    std::cout << "  [ÑÈÑÒÅÌÀ Ó×¨ÒÀ] Àâòîìàòè÷åñêèé çàêàç ñîçäàí äëÿ òîâàðà '"
        << productName << "'\n";
    autoOrderRequests[shelfId] = productName;
}

void InventorySystem::onWeightChanged(int shelfId, double oldWeight, double newWeight) {
    std::cout << "  [ÑÈÑÒÅÌÀ Ó×¨ÒÀ] Ïîëêà #" << shelfId << ": " << oldWeight << " -> " << newWeight << " ã\n";
}

void InventorySystem::showAutoOrders() const {
    if (autoOrderRequests.empty()) {
        std::cout << "  [ÑÈÑÒÅÌÀ Ó×¨ÒÀ] Íåò àêòèâíûõ çàêàçîâ\n";
    }
    else {
        std::cout << "  [ÑÈÑÒÅÌÀ Ó×¨ÒÀ] Àêòèâíûå çàêàçû:\n";
        for (const auto& order : autoOrderRequests) {
            std::cout << "    - Ïîëêà #" << order.first << ": " << order.second << "\n";
        }
    }
}