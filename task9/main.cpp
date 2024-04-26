#include "telephone.h"
#include "computer.h"
#include "smartphone.h"

int main(){
    Smartphone iphone("iphone14",2023);
    iphone.turn_on();
    iphone.calc(2,1);
    iphone.append("aaa");
    iphone.use();
    iphone.turn_off();

    Computer besm6("besm6",1965);
    besm6.turn_on();
    besm6.set_ram(150);
    besm6.calc(45,3);
    besm6.use();
    besm6.turn_off();

    Telephone vef("vef",1970);
    vef.turn_on();
    // stdvef.get_year_of_producing;
    vef.call(88005553535);
    vef.turn_off();

    return 0;
}