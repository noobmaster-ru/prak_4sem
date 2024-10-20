#include <iostream>

using namespace std;

struct Cl {
    int a;
    Cl ( int  t = 0){ 
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
int main () {                       //  На печать:
      const Cl & n = Cl(3);         //  -
      const Cl * p = &gg(5);        //  Destr  :будет напечатано,так как в cl & gg есть return и он вызовет деструктор , 
                                    //   а при cl & n = cl(3) деструктор будет вызван только при return 0;
      cout << n.a << endl;	        //  3
      cout << p->a << endl;         //  0 - ??? - undefined behavior. 
      return 0;	                    //  Destr
}	
