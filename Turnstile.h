#pragma once
#include "IExitDevice.h"
#include <string>
#include <iostream>

class Turnstile : public IExitDevice {  
private:
    int id;
    std::string location;
    bool locked;

public:
    Turnstile(int id, const std::string& loc);

    void open() override;
    void close() override;
    bool isOpen() const override;
    std::string getType() const override;

    void unlockForEntry();

    void displayInfo() const;
};