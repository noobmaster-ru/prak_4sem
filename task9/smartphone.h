#pragma once
#include "device.h"
#include "computer.h"
#include "telephone.h"

class Smartphone: public Telephone, public Computer{
public:
    Smartphone();
    Smartphone(std::string name);
    Smartphone(std::string name, int year);
    ~Smartphone();

    void append(std::string str);

    void use() override;
    void turn_on() override; 
    void turn_off() override;
};