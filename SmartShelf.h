#pragma once
#include "IShelfObserver.h"
#include <vector>
#include <memory>
#include <string>

class SmartShelf {
private:
    int id;
    std::string productName;
    double currentWeight;      // текущий вес товара на полке
    double maxWeight;          // максимальный вес (полна€ полка)
    double thresholdPercent;    // порог срабатывани€ в процентах (20% = 0.2)
    bool thresholdNotified;     // уже уведомили?

    std::vector<std::shared_ptr<IShelfObserver>> observers;

public:
    SmartShelf(int id, const std::string& product, double maxWeight, double thresholdPercent = 0.2);

    // ”правление наблюдател€ми
    void attach(std::shared_ptr<IShelfObserver> observer);
    void detach(std::shared_ptr<IShelfObserver> observer);

    // ќсновна€ логика
    void updateWeight(double newWeight);
    double getCurrentWeight() const { return currentWeight; }
    double getWeightPercent() const { return (currentWeight / maxWeight) * 100.0; }

    // —имул€ци€ покупки товара
    void simulatePurchase(double amount);

    void displayInfo() const;

private:
    void notifyWeightChanged(double oldWeight, double newWeight);
    void checkThreshold();
};