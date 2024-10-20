#include <iostream>

using namespace std;

class X {
	friend void fff ( X *, int); // здесь нет this !
public:
    int a;
	void mmm (int);
};

void fff ( X * p, int i) {
	p -> a = i;
}

void X::mmm (int i) {
	this -> a = i;
}

void f () {
	X obj;
	fff (&obj, 14);
    obj.mmm (15);
    cout << obj.a << endl;
}

int main(){
    f();
    return 0;
}