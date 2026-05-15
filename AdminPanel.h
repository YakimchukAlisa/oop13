#pragma once
#include "IShelfObserver.h"
#include <iostream>
#include <string>
#include <vector>

class AdminPanel : public IShelfObserver {
private:
    std::vector<std::string> notifications;
    bool soundEnabled;

public:
    AdminPanel(bool enableSound = true) : soundEnabled(enableSound) {}

    void onWeightBelowThreshold(int shelfId, const std::string& productName,
        double currentWeight, double threshold) override {
        std::cout << "\n  [АДМИН ПАНЕЛЬ] !!! ВНИМАНИЕ АДМИНИСТРАТОРУ !!!\n";
        std::cout << "     Полка #" << shelfId << " (" << productName
            << ") почти пуста! Осталось: " << currentWeight << " г\n";

        if (soundEnabled) {
            std::cout << "    [ЗВУКОВОЙ СИГНАЛ] Бип-бип-бип!\n";
        }

        std::cout << "    → Отображаю уведомление на экране: 'Требуется пополнение полки "
            << shelfId << "'\n";
        std::cout << "     [ДЕЙСТВИЕ АДМИНИСТРАТОРА] Ожидаю подтверждения...\n";

        notifications.push_back("Полка #" + std::to_string(shelfId) + ": " + productName);
    }

    void onWeightChanged(int shelfId, double oldWeight, double newWeight) override {
        // Админу не нужно видеть каждое изменение, только критические
        // Можно показывать только при сильных изменениях
        double changePercent = (newWeight - oldWeight) / oldWeight * 100;
        if (changePercent < -10) {  // резкое уменьшение >10%
            std::cout << "  [АДМИН ПАНЕЛЬ] Подозрительное изменение на полке #" << shelfId
                << ": -" << -changePercent << "% за короткое время\n";
        }
    }

    void showNotifications() const {
        if (notifications.empty()) {
            std::cout << "  [АДМИН ПАНЕЛЬ] Нет непрочитанных уведомлений\n";
        }
        else {
            std::cout << "  [АДМИН ПАНЕЛЬ] Непрочитанные уведомления:\n";
            for (const auto& notif : notifications) {
                std::cout << "    - " << notif << "\n";
            }
        }
    }
};