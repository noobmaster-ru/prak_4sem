#include <iostream>

using namespace std;

class Complex {
	public:
        double re, im;
		Complex (double r = 0, double i = 0) {
			re = r;
			im = i;
		}
		friend Complex operator+ (const Complex & a, const Complex & b);
};
Complex operator+ (const Complex & a, const Complex & b) {
			Complex temp (a.re + b.re, a.im + b.im);
			return temp;
}
int main () {
    Complex x (1, 2), y (5, 8), z;
    double t = 7.5;
    z = x + y;  // O.K. – operator+ (x, y);
    cout << z.re << ' ' << z.im << endl;
    z = z + t;   // O.K. – operator+ (z, Complex (t));
    cout << z.re << ' ' << z.im << endl;
    z = t + x;   // O.K. – operator+ (Complex (t), x);
    cout << z.re << ' ' << z.im << endl;
}

