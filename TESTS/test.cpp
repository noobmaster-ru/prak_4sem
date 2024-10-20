// #include <iostream>
// #include <vector>
// using namespace std;

// class A{
// public:
//     virtual void f() const { cout << "debugger";}
//     virtual void g() { cout << "link editor";}
// };

// class B : public A{
// public:
//     void f() { cout << "programming system";}
//     void g() {cout << "automated testing system";}
// };

// int main(){
//     B b;
//     A &r =b;
//     b.B::f();
//     return 0;
// }

// class A{
// public:
//     static int k;
//     A(){ k += 2;}
//     A(const A&){k += 3;}
//     ~A(){k -= 1;}
// };

// void f(A & a, int n){
//     try {if (n == 0) throw A(); else throw 1;}
//     catch(int x){f(a,x-1);}
//     catch(A&a){throw;}
// }

// int A::k = -1;

// int main(){
//     try { A a; f(a,10);}
//     catch (A a) { cout << A::k*10 +a.k;}
//     return 0;
// }

// struct B {
//     int n= 10;
//     B* operator- (const B* b) {n= b->n-3; return this;}

// };

// struct D: B{
//     D* operator- (const D* d) {n= d->n-5; return this;}
// };

// B&f(B&b){
//     if (typeid (b) == typeid (D))
//         cout << 1;
//     else
//         cout << 2;
//     return b;
// }
// int main() {
//     B b;
//     D d;
//     cout << (f(d) - &f(b)) -> n << endl;
//     return 0;
// }


// template <class T, int n> T f(){
//     T s=0;
//     for(; n ;--n){ s+=n; }
//     return s;
// }

// int main() {
//     cout << f <int, 10> () << endl;
//     return 0;
// }


// template <class T> T f (vector <T> & v) {
//     typename vector <T>::iterator i = v.begin();
//     i= i+1;
//     return *i;
// }

// int main() {
//     vector <int> v = {1,2,3};
//     cout << f <int> (v) << endl;
//     return 0;
// }


// class A {
// public:
//     static int k;
//     A() {k += 2; }
//     A (const A&) { k += 3;}
//     ~A() {k -= 1; }
// };

// void f (A& a, int n) { try { if (n==0) throw a; else throw 1; }
// catch (int x) { f (a, x-1); }
// catch (A & a) { throw ; }
// }

// int A::k=0;

// int main() {
//     A a; try { f (a,10); } catch(...) {}
//     cout << A::k;
// }


// class spb { public: spb * ths;
//     spb () { ths = this; }
//     virtual spb * operator [] (spb &) { cout << 1; return this; }
// };

// class spd: public spb { public: };

// int main() { spb s1; spd s2;
//     if (dynamic_cast<spd*> (s2 [s2])) 
//         cout<<2;
//     else 
//         cout << 3;
//     return 0;
// }

asbc 