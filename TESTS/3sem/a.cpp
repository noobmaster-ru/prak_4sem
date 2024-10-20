#include<iostream>

using namespace std;

class A  {

public:

   A(int) { cout<<1;}

   A(const A& r=A(1)) { cout<<2;}

   A(A&&r) { cout <<3;}

  ~A() { cout<<4;}

};

 

A  f() { A a; return a;}

 

int main() { f(); cout<<5; }