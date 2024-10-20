#include <iostream>

using namespace std;

struct Cl {
    int a;
    Cl ( int  t = 0) { 
        a = t; 
    }
    ~Cl() { 
        a = 0; 
        cout << "Destr\n";
    }
};

const Cl & gg (const Cl & ob)  {
    return ob;
}

int main () {                                 //    На печать:
    const Cl & n = gg(3);                    // Destr
    const Cl * p = &gg(5);                    //Destr
    cout << n.a << endl;	                  //     0 ?????
    cout << p->a << endl;                  // 0 ?????
    return 0;	
}	
