#include <iostream>
#include <string.h>
using namespace std;

class Str {
    char * p; 	// здесь потребуется динамическая память,
    int len;
public:
    Str (const  char * s);
    Str (const Str & a);
    ~ Str ( ) { delete [ ] p; }
    Str & operator= (const Str & a);

};

Str :: Str (const char * s) {
	p = new char [ ( len = strlen (s) ) + 1];
	strcpy (p, s);
}

Str :: Str (const Str & a) {
	p = new char [ (len = a.len) + 1];
	strcpy (p, a.p);
}
void f {
		Str  s1 (“Alice”);	
	 Str  s2 = s1;		
	 Str  s3 (“Kate”);			
		s3 = s1;
}

int main () {

    return 0;
}