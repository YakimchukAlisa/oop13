#pragma once
#include "IShelfObserver.h"
#include <vector>
#include <string>

class AdminPanel : public IShelfObserver {
private:
    std::vector<std::string> notifications;
    bool soundEnabled;

public:
    AdminPanel(bool enableSound = true);

    void onWeightBelowThreshold(int shelfId, const std::string& productName,
        double currentWeight, double threshold) override;

    void onWeightChanged(int shelfId, double oldWeight, double newWeight) override;

    void showNotifications() const;
};