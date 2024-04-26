#pragma once
#include <iostream>
#include <string>
#include <unistd.h>

class Device{
public:
    std::string name_of_the_device = "Unknown device";
    std::string type_of_the_device = "Unknown type";
    int year_of_producing  = 0;
    int switch_button = 0; // 0 - not working , 1 - working

    Device(){};
    virtual ~Device(){};

    int get_switch_button(){return switch_button;};
    int get_year_of_producing(){return year_of_producing;};
    std::string get_name(){return name_of_the_device;};
    std::string get_type(){return type_of_the_device;};

    virtual void use() = 0; // виртуальная функция
    virtual void turn_on() = 0; // виртуальная функция
    virtual void turn_off() = 0; // виртуальная функция
};