#pragma once
#include "IShelfObserver.h"
#include <map>
#include <string>

class InventorySystem : public IShelfObserver {
private:
    std::map<int, std::string> autoOrderRequests;

public:
    void onWeightBelowThreshold(int shelfId, const std::string& productName,
        double currentWeight, double threshold) override;

    void onWeightChanged(int shelfId, double oldWeight, double newWeight) override;

    void showAutoOrders() const;
};