#pragma once
#include <memory>
#include <vector>
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"
#include "Turnstile.h"
#include "CheckoutScale.h"
#include "PaymentSystem.h"
#include "AccessController.h"
#include "HighPrecisionScale.h"
#include "PostalScale.h"
#include "AutoDoor.h"
#include "CheckoutTerminal.h"
#include "SmartShelf.h"
#include "InventorySystem.h"
#include "AdminPanel.h"

class ShopSimulation {
private:
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Product>> regularProducts;      // обычные товары
    std::vector<std::shared_ptr<WeightedProduct>> weightedProducts;  // развесные

    // Разные типы весов
    std::shared_ptr<HighPrecisionScale> highPrecisionScale;
    std::shared_ptr<PostalScale> postalScale;
    std::shared_ptr<CheckoutScale> currentScale;  // текущие активные весы

    // Автоматическая дверь
    std::shared_ptr<AutoDoor> autoDoor;
    std::shared_ptr<Turnstile> entryTurnstile;
    std::shared_ptr<IExitDevice> defaultExit;  // устройство выхода по умолчанию
    std::shared_ptr<IExitDevice> altExit;

    // Счетчики
    int nextCartId;
    int nextCustomerId;

public:
    ShopSimulation();
    void initialize();
    void runSimulation();

private:
    void createCustomers();
    void createProducts();
    void createEquipment();
    std::shared_ptr<ShoppingCart> createCartForCustomer(int custId);
    void scenarioProxy();
    void scenarioDelegation();
    void scenarioState();
    void scenarioObserver();
    void scenarioMemento();
};