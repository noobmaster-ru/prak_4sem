#pragma once
#include "device.h"

class Computer: public virtual Device{
public:
    int ram_size = 100; // 100 by default
    std::string buffer_for_string;
    std::string buffer_for_multiplication;

    Computer();
    Computer(std::string name);
    Computer(std::string name, int year);
    ~Computer();

    void set_ram(int number);
    int get_ram_size();

    // void append(std::string str);
    void calc(int n , int m);


    void use() override;
    void turn_on() override; 
    void turn_off() override;
};