#include <iostream>

using namespace std;

int x = 0;
namespace N { 
	int x = 1;		 
	struct B { 			
		int x = 2;		 	
		void b();				
	};
    struct D : B {
        int x = 3;
        void d(){
            cout << "d::x = " << x << endl;					
            cout << "d: ::x = " << ::x << endl;
            cout << "d: B::x = " << B::x << endl;
            cout << "d: N::x = " << N::x << endl;
        }
    };
}

void N::B::b() { 
    D d1;  
    cout << d1.x << endl;  // 3
}

int main() {	
    int x = 5;
    N::D od;
    cout << "main:   x = " << x << endl;
    cout << "main:   ::x = " << ::x << endl;  // ::x наверх выше область видимости поднимается
    cout << "main:   B::x = " << od.B::x << endl; 
    cout << "main:   D::x = " << od.x << endl;
    cout << "main:   N::x = " << N::x << endl;
    return 0; 
