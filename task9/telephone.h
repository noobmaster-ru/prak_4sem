#pragma once
#include "device.h"

class Telephone: public virtual Device{
public:
    Telephone();
    Telephone(std::string name,int year);
    Telephone(std::string name);
    ~Telephone();



    void use() override; // answer for calling
    void turn_on() override;
    void turn_off() override;
    
    void call(long long number);
};
