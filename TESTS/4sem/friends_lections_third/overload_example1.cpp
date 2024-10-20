#include <iostream>

using namespace std;
class Complex {
public:
    double re, im;
	Complex (double r = 0, double i = 0)  {	
        re = r;
		im = i;
	}
    Complex operator+ (const Complex & a) {
        Complex temp (re + a.re, im + a.im);
        return temp;
    }  
	 // operator double () { return re; } – функция преобразования
};
int main () {
	Complex x (1, 2), y (5, 8), z;
	double t = 7.5;
	z = x + y;  // O.K. – x.operator+ (y);
	z = z + t;   // O.K. – z.operator+ (Complex (t)); если есть ф-я преобр., то 
	  	          // неоднозначность: '+' -  double  или перегруженный
	// z = t + x;  // Er.! – т.к. первый операнд по умолчанию – типа Complex.
    cout << z.re << ' ' << z.im << endl;
    return 0;
}
