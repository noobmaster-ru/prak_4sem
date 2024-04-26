#include "smartphone.h"

Smartphone::Smartphone():Telephone{},Computer{}{
    this->type_of_the_device = "Smartphone";
};
Smartphone::Smartphone(std::string name):Telephone{name},Computer{name}{
    this->name_of_the_device = name;
    this->type_of_the_device = "Smartphone";

};
Smartphone::Smartphone(std::string name, int year):Telephone{name,year},Computer{name,year}{
    this->name_of_the_device = name;
    this->type_of_the_device = "Smartphone";
    this->year_of_producing = year;
};
Smartphone::~Smartphone(){};

void Smartphone::append(std::string str){
    if (this->switch_button != 0){
        if ((size_t)this->ram_size >= this->buffer_for_multiplication.size() + this->buffer_for_string.size() + str.size()){
            this->buffer_for_string += str;
        }
        else{
            std::cout << this->name_of_the_device <<"'s ram is out of range. " << std::endl;
            std::cout << "Please free the buffer or increase its size." << std::endl;
        }
    }else{
        std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
        std::cout << "Please turn on the" << this->name_of_the_device << " before using."<<std::endl;
    }
};

void Smartphone::use(){
    if (this->switch_button != 0){
        std::cout << std::endl;
        for (int i = 0; i < std::stoi(this->buffer_for_multiplication); i++){
            std::cout << "Message: " << this->buffer_for_string << std::endl;
            std::cout.flush();
            sleep(1);
        }
    }else{
        std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
        std::cout << "Please turn on the" << this->name_of_the_device << " before using."<<std::endl;
    }
};
void Smartphone::turn_on(){
    this->switch_button = 1;
    std::cout << std::endl;
    std::cout << "Turn on the smartphone." << std::endl;
    std::cout.flush();
    sleep(2);
}; 
void Smartphone::turn_off(){
    this->switch_button = 0;
    std::cout << std::endl;
    std::cout << "Turn off the smartphone..." << std::endl;
    std::cout.flush();
    sleep(2);
};