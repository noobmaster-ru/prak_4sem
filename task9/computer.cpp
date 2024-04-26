#include "computer.h"

Computer::Computer(){
    this->type_of_the_device = "Computer";
};
Computer::Computer(std::string name){
    this->name_of_the_device = name;
    this->type_of_the_device = "computer";
};
Computer::Computer(std::string name, int year){
    this->name_of_the_device = name;
    this->type_of_the_device = "computer";
    this->year_of_producing = year;
};

Computer::~Computer(){};


int Computer::get_ram_size(){
    return this->ram_size;
}
void Computer::set_ram(int number){
    this->ram_size = number;
};
// void Computer::append(std::string str){
//     if (this->switch_button != 0){
//         if ((size_t)this->ram_size >= this->buffer_for_multiplication.size() + this->buffer_for_string.size() + str.size()){
//             this->buffer_for_string += str;
//         }
//         else{
//             std::cout << this->name_of_the_device <<"'s ram is out of range. " << std::endl;
//             std::cout << "Please free the buffer or increase its size." << std::endl;
//         }
//     }else{
//         std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
//         std::cout << "Please turn on the" << this->name_of_the_device << " before using."<<std::endl;
//     }
// };


void Computer::calc(int n , int m){
    if (this->switch_button != 0){
        int mult = n * m;
        if ((std::size_t)ram_size >= this->buffer_for_string.size() + this->buffer_for_multiplication.size() + (std::size_t)mult){
            int new_value_for_buffer_for_multiplication;
            if (this->buffer_for_multiplication.size() != 0){
                new_value_for_buffer_for_multiplication = std::stoi(buffer_for_multiplication) * mult;
            }else{
                new_value_for_buffer_for_multiplication = mult;
            }
            this->buffer_for_multiplication.clear();
            this->buffer_for_multiplication += std::to_string(new_value_for_buffer_for_multiplication);
        }else{
            std::cout << this->name_of_the_device <<"'s ram is out of range. " << std::endl;
            std::cout << "Please free the buffer or increase its size." << std::endl;
            exit(0);
        }
    }else{
        std::cout << this->name_of_the_device << " is not turned on!" << std::endl;
        std::cout << "Please turn on the" << this->name_of_the_device << " before using."<<std::endl;
    }
};
void Computer::use(){
    std::cout << std::endl;
    std::cout << "Buffer for multiplication: " << this->buffer_for_multiplication << std::endl; 
};
void Computer::turn_on(){
    this->switch_button = 1;
    std::cout << std::endl;
    std::cout << "Turn on the computer." << std::endl;
    std::cout.flush();
    sleep(2);
};
void Computer::turn_off(){
    this->switch_button = 0;
    std::cout << std::endl;
    std::cout << "Turn off the computer..." << std::endl;
    std::cout.flush();
    sleep(2);
};