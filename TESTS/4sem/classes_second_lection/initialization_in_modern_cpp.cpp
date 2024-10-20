#include <iostream>

using namespace std;

struct B{
    int t{1};
    B(int k): t(k){};
    B(){};
};

struct A{
    int n = 14;
    B b = B(3);
    int m[4] = {1,2,3,4};
    A(int x = 0, int y = 0): n(x), b(y){};
    static const int cc = 8; 
};
int main(){
    A a1{7,9}, a2;
    cout << a1.n << ' '<< a1.b.t << ' ' << a2.n << ' ' << a1.m[2] << endl;
    return 0;
}