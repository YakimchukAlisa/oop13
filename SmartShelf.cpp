#include "SmartShelf.h"
#include <iostream>
#include <algorithm>

SmartShelf::SmartShelf(int id, const std::string& product, double maxWeight, double thresholdPercent)
    : id(id), productName(product), currentWeight(maxWeight),
    maxWeight(maxWeight), thresholdPercent(thresholdPercent), thresholdNotified(false) {
    std::cout << "Создана умная полка #" << id << " для товара '" << productName
        << "', макс. вес: " << maxWeight << " г\n";
}

void SmartShelf::attach(std::shared_ptr<IShelfObserver> observer) {
    observers.push_back(observer);
    std::cout << "  Наблюдатель добавлен к полке #" << id << "\n";
}

void SmartShelf::detach(std::shared_ptr<IShelfObserver> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void SmartShelf::updateWeight(double newWeight) {
    if (newWeight < 0) newWeight = 0;
    if (newWeight > maxWeight) newWeight = maxWeight;

    double oldWeight = currentWeight;
    currentWeight = newWeight;

    notifyWeightChanged(oldWeight, currentWeight);
    checkThreshold();
}

void SmartShelf::simulatePurchase(double amount) {
    if (amount > currentWeight) amount = currentWeight;
    double newWeight = currentWeight - amount;
    std::cout << "\n[Полка #" << id << "] Покупка: -" << amount << " г товара '" << productName << "'\n";
    updateWeight(newWeight);
}

void SmartShelf::notifyWeightChanged(double oldWeight, double newWeight) {
    for (auto& observer : observers) {
        observer->onWeightChanged(id, oldWeight, newWeight);
    }
}

void SmartShelf::checkThreshold() {
    double currentPercent = currentWeight / maxWeight;
    bool isBelowThreshold = currentPercent < thresholdPercent;

    if (isBelowThreshold && !thresholdNotified) {
        std::cout << "\n!!! [СОБЫТИЕ] Полка #" << id << " (" << productName
            << ") вес ниже " << (thresholdPercent * 100) << "% !!!\n";

        for (auto& observer : observers) {
            observer->onWeightBelowThreshold(id, productName, currentWeight, thresholdPercent);
        }
        thresholdNotified = true;
    }
    else if (!isBelowThreshold) {
        thresholdNotified = false;
    }
}

void SmartShelf::displayInfo() const {
    std::cout << "Полка #" << id << ": " << productName
        << ", вес: " << currentWeight << "/" << maxWeight << " г ("
        << getWeightPercent() << "%)\n";
}