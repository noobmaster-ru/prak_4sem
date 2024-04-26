#include "telephone.h"

Telephone::Telephone(){
    this->type_of_the_device = "Telephone";
};
Telephone::Telephone(std::string name, int year){
    this->type_of_the_device = "Telephone";
    this->name_of_the_device = name;
    this->year_of_producing = year;
};
Telephone::Telephone(std::string name){
    this->name_of_the_device = name;
    this->type_of_the_device = "Telephone";
};
Telephone::~Telephone(){}; 

void Telephone::turn_on(){
    this->switch_button = 1;
    std::cout << std::endl;
    std::cout << "Turn on the telephone." << std::endl;
    std::cout.flush();
    sleep(2);
};
void Telephone::turn_off(){
    this->switch_button = 0;
    std::cout << std::endl;
    std::cout << "Turn off the telephone." << std::endl;
    std::cout.flush();
    sleep(2);
};
void Telephone::use(){
    if (this->switch_button != 0){
        std::cout << std::endl;
        std::cout << this->name_of_the_device << " is asnwering for call, please wait." << std::endl;
        for (int i = 0; i < 5; i++){
            std::cout << '.';
            std::cout.flush();
            sleep(1);
        }
        std::cout << std::endl;
        std::cout <<"End of the calling."<< std::endl;
    }else{
        std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
        std::cout << "Please turn on the telephone before using."<<std::endl;
    }
}

void Telephone::call(long long  number){
    if (this->switch_button != 0){
        std::cout << std::endl;
        std::cout << this->name_of_the_device << " is calling to " << number << std::endl;
        for (int i = 0; i < std::to_string(number).size(); i++){
            std::cout << std::to_string(number)[i];
            std::cout.flush();
            sleep(1);
        }
    }else{
        std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
        std::cout << "Please turn on the telephone before using."<<std::endl;
    }
};