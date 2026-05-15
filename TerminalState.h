#pragma once
#include <memory>
#include <string>

class CheckoutTerminal;

// Базовый интерфейс для всех состояний
class TerminalState {
public:
    virtual ~TerminalState() = default;

    // Действия, которые могут быть вызваны
    virtual void scanProduct(CheckoutTerminal* terminal, const std::string& productName, double price) = 0;
    virtual void removeLastProduct(CheckoutTerminal* terminal) = 0;
    virtual void proceedToPayment(CheckoutTerminal* terminal) = 0;
    virtual void cancel(CheckoutTerminal* terminal) = 0;
    virtual void completePayment(CheckoutTerminal* terminal) = 0;

    // Получение названия состояния
    virtual std::string getStateName() const = 0;
};