#pragma once
#include "TerminalState.h"
#include <memory>
#include <vector>
#include <string>

// Forward declarations для классов состояний
class WaitingState;
class ScanningState;
class PaymentState;
class ReceiptState;

// Контекст - кассовый терминал
class CheckoutTerminal {
private:
    std::shared_ptr<TerminalState> currentState;

    // Указатели на состояния 
    std::shared_ptr<TerminalState> waitingState;
    std::shared_ptr<TerminalState> scanningState;
    std::shared_ptr<TerminalState> paymentState;
    std::shared_ptr<TerminalState> receiptState;

    // Данные текущей сессии
    std::vector<std::pair<std::string, double>> scannedProducts;
    double currentTotal;

public:
    CheckoutTerminal();
    ~CheckoutTerminal() = default;

    // Управление состояниями
    void setState(std::shared_ptr<TerminalState> newState);
    std::shared_ptr<TerminalState> getCurrentState() const { return currentState; }

    // Геттеры для состояний (возвращают shared_ptr<TerminalState>)
    std::shared_ptr<TerminalState> getWaitingState() const { return waitingState; }
    std::shared_ptr<TerminalState> getScanningState() const { return scanningState; }
    std::shared_ptr<TerminalState> getPaymentState() const { return paymentState; }
    std::shared_ptr<TerminalState> getReceiptState() const { return receiptState; }

    // Действия, делегируемые текущему состоянию
    void scanProduct(const std::string& productName, double price);
    void removeLastProduct();
    void proceedToPayment();
    void cancel();
    void completePayment();

    // Вспомогательные методы
    void addProduct(const std::string& name, double price);
    void removeProduct();
    double getTotal() const { return currentTotal; }
    void clearCart();
    void printReceipt() const;
    void showStatus() const;
};