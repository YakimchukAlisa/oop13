#include "AdminPanel.h"
#include <iostream>

AdminPanel::AdminPanel(bool enableSound) : soundEnabled(enableSound) {}

void AdminPanel::onWeightBelowThreshold(int shelfId, const std::string& productName,
    double currentWeight, double threshold) {
    std::cout << "\n  [АДМИН ПАНЕЛЬ] !!! ВНИМАНИЕ АДМИНИСТРАТОРУ !!!\n";
    std::cout << "     Полка #" << shelfId << " (" << productName
        << ") почти пуста! Осталось: " << currentWeight << " г\n";

    if (soundEnabled) {
        std::cout << "     [ЗВУКОВОЙ СИГНАЛ] Бип-бип-бип!\n";
    }

    std::cout << "    → Отображаю уведомление на экране: 'Требуется пополнение полки "
        << shelfId << "'\n";

    notifications.push_back("Полка #" + std::to_string(shelfId) + ": " + productName);
}

void AdminPanel::onWeightChanged(int shelfId, double oldWeight, double newWeight) {
    double changePercent = (newWeight - oldWeight) / oldWeight * 100;
    if (changePercent < -10) {
        std::cout << "  [АДМИН ПАНЕЛЬ] Подозрительное изменение на полке #" << shelfId
            << ": -" << -changePercent << "% за короткое время\n";
    }
}

void AdminPanel::showNotifications() const {
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