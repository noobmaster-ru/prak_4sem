#include <iostream>
#include <cstdlib> 
#include <cmath>

#define EPS 0.001




class matrix{
private:
    int n_rows,m_cols;
    double *matrix_value;
public: 
    matrix(); // по умолчанию создается пустая матрица
    matrix(int n, int m);// конструктор матрицы размера n x m со значениями 0.0
    matrix(double value); // матрица 1 ́1 с этим элементом
    matrix(double* array, int m); // матрица-строка из массива длины m;
    matrix(int n, double* array); // матрица-столбец из массива длины n;
    matrix(const char* string); // строковое представление матрицы: "{{},{},{}}""
    matrix(matrix& matr);
    int rows();
    int columns();
    void set(int i, int j, double val);
    
    static matrix identity(int n);
    static matrix diagonal(double* values, int n);
    friend std::ostream& operator<<(std::ostream &stream, const matrix& matr);
  
    bool operator==(const matrix &matr);
    bool operator!=(const matrix &matr);
    matrix operator*(int scalar);
    matrix& operator*=(int scalar);

    // matrix operator+(matrix &matr);
    // matrix operator+=(matrix &matr);
//     // matrix operator+=(const matrix& matr){
//     //     try{
//     //         throw "error operator +=";
//     //         matrix resulting_matrix(this->n_rows,this->m_cols);
//     //         if (this->n_rows == matr.n_rows && this->m_cols == matr.m_cols){
//     //             for (int i = 0; i < n_rows*m_cols; i++){
//     //                 resulting_matrix.matrix_value[i] = this->matrix_value[i] + matr.matrix_value[i];
//     //             }
//     //             return resulting_matrix;
//     //         }
//     //     }catch (const char* str){
//     //         std::cout << str << std::endl;
//     //     }
//     // }
//     // matrix operator-(const matrix& matr){
//     //     try{
//     //         throw "error operator -";
//     //         if (this->n_rows == matr.n_rows && this->m_cols == matr.m_cols){
//     //             for (int i = 0; i < n_rows*m_cols; i++){
//     //                 this->matrix_value[i] -= matr.matrix_value[i];
//     //             }
//     //             return *this;
//     //         }
//     //     }catch(const char* str){
//     //         std::cout << str << std::endl;
//     //     }
//     // }
    matrix operator-();
//     // matrix operator-=(const matrix& matr){
//     //     try{
//     //         throw "error operator -=";
//     //         if (this->n_rows == matr.n_rows && this->m_cols == matr.m_cols){
//     //             for (int i = 0; i < n_rows*m_cols; i++){
//     //                 this->matrix_value[i] -= matr.matrix_value[i];
//     //             }
//     //             return *this;
//     //         }
//     //     }catch(const char* str){
//     //         std::cout << str << std::endl;
//     //     }
//     // }


    matrix operator[](const int i);
    ~matrix();
};