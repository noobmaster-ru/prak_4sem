абстрактный класс - device

device:
public:
    std::string name_of_the_device;
    std::string type_of_the_device;
    int year_of_producing;

    -virual turn_on() - включить 
    -virtual turn_off() - выключить 
    -virtual use() - использовать устройство    



telephone:
public:
    -use() - ответить на звонок
    -call(long long number) - набрать номер number



computer:  
public:
    int ram_size;

    - set_ram(int number) - set new ram_size
    - calc(int n, int m) - создать буфер умножения чисел n и m 
        (reject if size(buffer) > ram_size)
    - use() - вывести буфер на экран 



smartphone:
    - append("str") - создать буфер строки "str" 
        (reject if size(buffer) > ram_size)

    -use() - send message: buffer_for_string*buffer_for_mult 

 
device -> telephone  |->    smartphone
device -> computer   |->    smartphone