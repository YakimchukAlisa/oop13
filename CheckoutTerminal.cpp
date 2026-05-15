#include "CheckoutTerminal.h"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

// ========== КОНКРЕТНЫЕ СОСТОЯНИЯ (объявлены до реализации CheckoutTerminal) ==========

class WaitingState : public TerminalState {
public:
    void scanProduct(CheckoutTerminal* terminal, const std::string& productName, double price) override {
        std::cout << "  [Ожидание] Начинаем сканирование...\n";
        terminal->addProduct(productName, price);
        terminal->setState(terminal->getScanningState());
    }

    void removeLastProduct(CheckoutTerminal* terminal) override {
        std::cout << "  [Ожидание] Нет товаров для удаления\n";
    }

    void proceedToPayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Ожидание] Нет товаров для оплаты\n";
    }

    void cancel(CheckoutTerminal* terminal) override {
        std::cout << "  [Ожидание] Нечего отменять\n";
    }

    void completePayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Ожидание] Нет активной оплаты\n";
    }

    std::string getStateName() const override { return "Ожидание"; }
};

class ScanningState : public TerminalState {
public:
    void scanProduct(CheckoutTerminal* terminal, const std::string& productName, double price) override {
        terminal->addProduct(productName, price);
        std::cout << "  [Сканирование] Товар добавлен. Всего: " << terminal->getTotal() << " руб.\n";
    }

    void removeLastProduct(CheckoutTerminal* terminal) override {
        terminal->removeProduct();
        std::cout << "  [Сканирование] Последний товар удален\n";
    }

    void proceedToPayment(CheckoutTerminal* terminal) override {
        if (terminal->getTotal() > 0) {
            std::cout << "  [Сканирование] Переход к оплате. Сумма: " << terminal->getTotal() << " руб.\n";
            terminal->setState(terminal->getPaymentState());
        }
        else {
            std::cout << "  [Сканирование] Корзина пуста, оплата невозможна\n";
        }
    }

    void cancel(CheckoutTerminal* terminal) override {
        std::cout << "  [Сканирование] ОТМЕНА ОПЕРАЦИИ! Корзина очищена\n";
        terminal->clearCart();
        terminal->setState(terminal->getWaitingState());
    }

    void completePayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Сканирование] Сначала перейдите к оплате\n";
    }

    std::string getStateName() const override { return "Сканирование"; }
};

class PaymentState : public TerminalState {
public:
    void scanProduct(CheckoutTerminal* terminal, const std::string& productName, double price) override {
        std::cout << "  [Оплата] Нельзя сканировать во время оплаты\n";
    }

    void removeLastProduct(CheckoutTerminal* terminal) override {
        std::cout << "  [Оплата] Нельзя удалять товары во время оплаты\n";
    }

    void proceedToPayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Оплата] Уже в процессе оплаты\n";
    }

    void cancel(CheckoutTerminal* terminal) override {
        std::cout << "  [Оплата] ОПЛАТА ОТМЕНЕНА! Возврат в режим сканирования\n";
        terminal->setState(terminal->getScanningState());
    }

    void completePayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Оплата] ОПЛАТА ПРОШЛА УСПЕШНО!\n";
        terminal->setState(terminal->getReceiptState());
    }

    std::string getStateName() const override { return "Оплата"; }
};

class ReceiptState : public TerminalState {
public:
    void scanProduct(CheckoutTerminal* terminal, const std::string& productName, double price) override {
        std::cout << "  [Печать чека] Дождитесь завершения печати\n";
    }

    void removeLastProduct(CheckoutTerminal* terminal) override {
        std::cout << "  [Печать чека] Нельзя удалять товары\n";
    }

    void proceedToPayment(CheckoutTerminal* terminal) override {
        std::cout << "  [Печать чека] Оплата уже выполнена\n";
    }

    void cancel(CheckoutTerminal* terminal) override {
        std::cout << "  [Печать чека] Нельзя отменить, чек печатается\n";
    }

    void completePayment(CheckoutTerminal* terminal) override {
        terminal->printReceipt();
        terminal->clearCart();
        terminal->setState(terminal->getWaitingState());
        std::cout << "  [Печать чека] ЧЕК ВЫДАН. Терминал готов к следующему покупателю\n";
    }

    std::string getStateName() const override { return "Печать чека"; }
};

// ========== РЕАЛИЗАЦИЯ CHECKOUTTERMINAL ==========

CheckoutTerminal::CheckoutTerminal() : currentTotal(0) {
    // Создаем состояния
    waitingState = std::make_shared<WaitingState>();
    scanningState = std::make_shared<ScanningState>();
    paymentState = std::make_shared<PaymentState>();
    receiptState = std::make_shared<ReceiptState>();

    // Начинаем с состояния "Ожидание"
    currentState = waitingState;
    std::cout << "  *** Состояние терминала: " << currentState->getStateName() << " ***\n";
}

void CheckoutTerminal::setState(std::shared_ptr<TerminalState> newState) {
    currentState = newState;
    std::cout << "  *** Состояние терминала: " << currentState->getStateName() << " ***\n";
}

void CheckoutTerminal::scanProduct(const std::string& productName, double price) {
    currentState->scanProduct(this, productName, price);
}

void CheckoutTerminal::removeLastProduct() {
    currentState->removeLastProduct(this);
}

void CheckoutTerminal::proceedToPayment() {
    currentState->proceedToPayment(this);
}

void CheckoutTerminal::cancel() {
    currentState->cancel(this);
}

void CheckoutTerminal::completePayment() {
    currentState->completePayment(this);
}

void CheckoutTerminal::addProduct(const std::string& name, double price) {
    scannedProducts.push_back({ name, price });
    currentTotal += price;
}

void CheckoutTerminal::removeProduct() {
    if (!scannedProducts.empty()) {
        auto last = scannedProducts.back();
        currentTotal -= last.second;
        scannedProducts.pop_back();
    }
}

void CheckoutTerminal::clearCart() {
    scannedProducts.clear();
    currentTotal = 0;
}

void CheckoutTerminal::printReceipt() const {
    std::cout << "\n  ========== ЧЕК ==========\n";
    for (const auto& product : scannedProducts) {
        std::cout << "    " << std::left << std::setw(20) << product.first
            << std::right << std::setw(10) << product.second << " руб.\n";
    }
    std::cout << "    ------------------------\n";
    std::cout << "    ИТОГО: " << currentTotal << " руб.\n";
    std::cout << "  ==========================\n\n";
}

void CheckoutTerminal::showStatus() const {
    std::cout << "Терминал: " << currentState->getStateName()
        << ", товаров: " << scannedProducts.size()
        << ", сумма: " << currentTotal << " руб.\n";
}