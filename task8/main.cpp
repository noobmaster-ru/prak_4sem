#include "matrix.h"

#define SIZE 4
#define SCALAR 10
using namespace std;
int main(){
    double* array = new double[SIZE];
    array[0] = 2.4667;
    array[1] = 342;
    array[2] = 1345.791;
    array[3] = 1.234123;


    cout << endl;
    cout << "null matrix:" << endl;
    matrix m;
    cout << m << endl;

    cout << endl;
    cout << "empty matrix:" << endl;
    matrix m1(2,4);
    cout << m1 << endl;

    cout << endl;
    cout << "matrix(double):" << endl;
    matrix m2(2.4242);
    cout << m2 << endl;

    cout << endl;
    cout << "matrix(double*,int m):" << endl; 
    matrix m3(array,SIZE);
    cout << m3 << endl;

    cout << endl;
    cout << "matrix(int n,double*):" << endl;
    matrix m4(SIZE,array);
    cout << m4 << endl;


    cout << endl;
    cout << "matrix({string}):" << endl;
    matrix m5("{{1,2,3},{6,1.34,65.1}}");
    cout << m5 << endl;

    cout << endl;
    cout << "matrix::identity(int n):" << endl;
    cout << matrix::identity(4) << endl;

    cout << endl;
    cout << "matrix::diagonal(double* vals,int n)" << endl;
    cout << matrix::diagonal(array,SIZE) << endl;

    cout << endl;
    cout << "matrix.rows():" << endl;
    cout << m5.rows() << endl;

    cout << endl;
    cout << "matrix.columns():" << endl;
    cout << m5.columns() << endl;

    cout << endl;
    cout << "matrix.set(int i,int j,value):" << endl;
    cout << m1 << endl;
    m1.set(1,1,234.123);
    m1.set(2,1,3.123);
    cout << m1 << endl;

    cout << endl;
    cout << "matrix * scalar:" << endl;
    cout << m5 << endl;
    cout << m5*3 << endl;

    cout << endl;
    cout << "matrix *= scalar" << endl;
    m5 *= 10;
    cout << m5 << endl;


    // matrix m6("{{1,2,3}}");
    // cout << (m5 == m6) << endl;
    cout << "matrix[int i]:" << endl;
    cout << m5 << endl;
    cout << m5[2] << endl;


    cout << endl;
    cout << "matrix[int j]:" << endl;
    cout << m5 << endl;
    cout << m5[3] << endl;

    cout << endl;
    cout << "matrix[int i, int j]:" << endl;
    cout << m5 << endl;
    cout << m5[2][3] << endl;


    // cout << endl;
    // cout << "(m6 == m5)?" << endl;
    // matrix m6(m5);
    // cout << boolalpha << (m6 == m5) << endl;


    // cout << endl;
    // m6 *= 10;
    // cout << "m6*10 == m5?" << endl;
    // cout << boolalpha << (m6 == m5) << endl;

    // cout << endl;
    // cout << "m6*10 != m5?" << endl;
    // cout << boolalpha << (m6 != m5) << endl;

    // cout << endl;
    // cout << "-m5:" << endl;
    // cout << (-m5) << endl;

    // cout << endl;
    // cout << "m5 + m6:" << endl;
    // cout << (m2 + m6) << endl;

    // cout << m5 << endl;
    // cout << m6 << endl;
    // m5 += m6;
    // cout << m5 << endl;
    delete[] array;
    return 0;
}