#include <iostream>

using namespace std;

class A{
public:
    int n;
    A(int x): n(x){};
    A(): A(14){};
};

int main(){
    A a1;
    cout << a1.n << endl;
    return 0;
}