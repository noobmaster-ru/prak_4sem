#include <iostream>


using namespace std;


struct A{
    int a;
    A(int t = 0){
        a = t;
    };
};
int f(const int &n, const A &ob){
        return n + ob.a;
}


int main(){
    cout << f(3,5) << endl;
    return 0;
}