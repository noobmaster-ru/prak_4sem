#include <iostream>


class A{
    int a;
public:
    void set_a(int n);
    int get_a() const { return a; }
};

void A::set_a(int n){
    a = n;
}

int main (){
    A obj1, obj2;
    obj1.set_a(5);
    obj2.set_a(10);

    std::cout << "a in obj1 = " << obj1.get_a() << '\n';
    std::cout << "a in obj2 = " << obj2.get_a() << '\n';
    return 0;
}