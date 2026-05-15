#pragma once
#include <string>

class IShelfObserver {
public:
    virtual ~IShelfObserver() = default;
    virtual void onWeightBelowThreshold(int shelfId, const std::string& productName,
        double currentWeight, double threshold) = 0;
    virtual void onWeightChanged(int shelfId, double oldWeight, double newWeight) = 0;
};