#include "matrix.h"
#include <iostream>
#include <cstdlib> 
#include <cmath>
using namespace std;


matrix::matrix(){ // по умолчанию создается пустая матрица
    n_rows = 0;
    m_cols = 0;
    matrix_value= nullptr;
};
matrix::matrix(int n, int m){ // конструктор матрицы размера n x m со значениями 0.0
    n_rows = n;
    m_cols = m;
    matrix_value = new double[n_rows*m_cols];
    for (int i = 0; i < n_rows; i++){
        for (int j = 0; j < m_cols; j++){
            matrix_value[i*m_cols + j] = 0.0;
        }
    }
};
matrix::matrix(double* array, int m){ // матрица-строка из массива длины m;
    n_rows = 1;
    m_cols = m;
    matrix_value = new double[n_rows*m_cols];
    for (int j = 0; j < m_cols; j++){
        matrix_value[j] = array[j];
    }
};
matrix::matrix(double value){ // матрица 1 ́1 с этим элементом
    n_rows = 1;
    m_cols = 1;
    matrix_value = new double[1];
    matrix_value[0] = value;
};
matrix::matrix(int n, double* array){ // матрица-столбец из массива длины n;
    n_rows = n;
    m_cols = 1;
    matrix_value = new double[n_rows*m_cols];
    for (int i = 0; i < n_rows; i++){
        matrix_value[i] = array[i];
    }
};  
matrix::matrix(const char* string){ // строковое представление матрицы: "{{},{},{}}""
    int i = 0, size_of_array = 1, number_of_rows = 0;
    double* array_for_numbers = (double*)malloc(sizeof(double));
    while (string[i] != '\0'){
        if ((string[i] - '0') >= 0 && (string[i] -'0') <= 9){
            double number = string[i] -'0';
            i++;
            while ((string[i] - '0') >= 0 && (string[i] -'0') <= 9){
                number *=10;
                number += string[i] - '0';
                i++;
            }

            if (string[i] == '.'){
                i++;
                double ostatok = (double)(string[i] -'0')/10;
              
                i++;
                int kol_of_del = 1;
                while ((string[i] - '0') >= 0 && (string[i] -'0') <= 9){
                    double transfer_number = (double)(string[i] - '0');
                    kol_of_del++;
                    for (int j = 0; j < kol_of_del; j++){
                        transfer_number = transfer_number/10;
                    }
                    ostatok += transfer_number;
                    i++;
                }

                if (string[i] == '}'){
                    number_of_rows++;
                }
                number = number + ostatok;

            }
            else if (string[i] == '}'){
                number_of_rows++;
            }
            array_for_numbers = (double*)realloc(array_for_numbers, sizeof(double)*size_of_array);

            array_for_numbers[size_of_array-1] = number;
            size_of_array++;
            i++;
        }
        else if (string[i] == '}'){
            number_of_rows++;
            i++;
        }
        else{
            i++;
        }
    }

    // for (int i = 0; i < size_of_array; i++){
    //     cout << array_for_numbers[i] << ' ';
    // }
    //cout << endl << endl;
    // cout << "number of rows =  "<< number_of_rows << ' ' << "size of array =  " << size_of_array << endl;
    n_rows = number_of_rows-1;
    m_cols = (size_of_array-1)/n_rows;
    //cout << "n_rows = " <<  n_rows << ' ' << "m_cols = " << m_cols << endl;
    matrix_value = new double[size_of_array];
    for (int i = 0; i < n_rows; i++){
        for (int j = 0; j < m_cols; j++){
            matrix_value[i*m_cols + j] = array_for_numbers[i*m_cols + j];
            //cout << array_for_numbers[i*n_rows + j] << ' ';
        }
        //cout << endl;
    }
    delete[] array_for_numbers;
    //cout << endl << endl;
};
matrix::matrix(matrix& matr){
    n_rows = matr.n_rows;
    m_cols = matr.m_cols;
    matrix_value = new double[n_rows,m_cols];
    for (int i = 0; i < n_rows; i++){
        for (int j = 0 ; j < m_cols; j++){
            matrix_value[i*m_cols+j] = matr.matrix_value[i*m_cols+j];
        }
    } 
}
matrix::~matrix(){
    if (matrix_value != nullptr)
        delete[] matrix_value;
};



ostream& operator<<(ostream &stream, const matrix& matr){
    for (int i = 0; i < matr.n_rows; i++){
        for (int j = 0; j < matr.m_cols; j++){
            stream << matr.matrix_value[i*matr.m_cols + j] << " ";
        }
        stream << '\n'; 
    }
    return stream;
}   
matrix matrix::identity(int n){
    matrix iden_matrix(n,n);
    for (int i = 1; i <= iden_matrix.rows(); i++){
        for (int j = 1; j <= iden_matrix.columns(); j++){
            iden_matrix.set(i,j,1);
        }

    }
    return iden_matrix;
};
matrix matrix::diagonal(double* values, int n){
    matrix diagonal_matrix(n,n);
    for (int i = 1; i <= diagonal_matrix.rows(); i++){
        diagonal_matrix.set(i,i,values[i-1]);
    }
    return diagonal_matrix;
};
int matrix::rows(){return n_rows;}
int matrix::columns(){return m_cols;}
void matrix::set(int i, int j, double val){
    try{
        if (i > n_rows || j > m_cols ){
            throw "error set";
        }
        matrix_value[(i-1)*m_cols + j-1] = val;
    }catch (const char *str){
        std::cout << str << std::endl;
    }
}; 


matrix matrix::operator*(int scalar){
    matrix result(n_rows,m_cols);
    for (int i = 0; i < n_rows*m_cols; i++){
        result.matrix_value[i] = matrix_value[i]*scalar;
    }
    return result;
}
matrix& matrix::operator*=(int scalar){
    for (int i = 0; i < n_rows*m_cols; i++){
        matrix_value[i] = matrix_value[i] * scalar;
    }
    return *this;
}


class class_str{
    private:
        friend class matrix;
        matrix&  m_parent;
        int m_row;
        class_str(matrix& parent, int row): m_parent(parent) , m_row(row){}
    public:
        matrix operator[](int col){
            matrix one_elem;
            one_elem[0] = m_parent[(m_row-1)*m_parent.rows() +(col-1)];
            return one_elem;
        }
};
matrix matrix::operator[](const int i){
    try{
        if ((i > n_rows && i > m_cols) || i < 0 ){
            throw "error operator []";
        }
        if (i <= n_rows){ // we are returning row
            matrix resulting_matrix(1,m_cols);
            for (int j = 0; j < m_cols; j++){
                resulting_matrix.matrix_value[j] = this->matrix_value[(i-1)*m_cols+j];
                //std::cout << resulting_matrix.matrix_value[j] << std::endl;
            }
            return resulting_matrix;
        }
        if (i <= m_cols){ // return column
            matrix resulting_matrix(n_rows,1);
            for (int j = 0; j < n_rows; j++){
                resulting_matrix.matrix_value[j] = this->matrix_value[j*m_cols+(i-1)];
                //std::cout << resulting_matrix.matrix_value[j] << std::endl;
            }
            return resulting_matrix;        
        }
        class_str(*this,i);

    }catch (const char* str){
        std::cout << str << std::endl;
    }
    matrix empty;
    return empty;
}


bool matrix::operator==(const matrix &matr){
    try{
        if (n_rows != matr.n_rows || m_cols != matr.m_cols){
            throw "error operator ==";
        }
        for (int i = 0; i < n_rows*m_cols; i++){
            if (fabs(matr.matrix_value[i]- matrix_value[i]) > EPS){
                return false;
            }
        }
        return true;
    }catch (const char * str){
        std::cout << str << std::endl;
    }
    return false;
}
bool matrix::operator!=(const matrix &matr){
    return 1 - (*this==matr);
}
matrix matrix::operator-(){
    matrix result(n_rows,m_cols);
    for (int i = 0; i < m_cols*n_rows; i++){
        result.matrix_value[i] = matrix_value[i]*(-1);
    }
    return result;
}   

// matrix matrix::operator+(const matrix &matr){
//     // try{
//     //     if (this->n_rows != matr.n_rows || this->m_cols != matr.m_cols){
//     //         throw "error operator +";
//     //     }
//         matrix result(matr.n_rows,matr.m_cols);
//         for (int i = 0; i < matr.n_rows; i++){
//             for (int j = 0; j < matr.m_cols;j++){
//                 result.matrix_value[i*m_cols+j] = this->matrix_value[i*m_cols+j] + matr.matrix_value[i*m_cols+j];
//             }
//         }
//         return result;
//     // }catch (const char * str){
//     //     std::cout << str << std::endl;
//     //     return *this;
//     // }
// }

// matrix matrix::operator+=(const matrix &matr){
//     // try{
//     //     if (this->n_rows != matr.n_rows || this->m_cols != matr.m_cols){
//     //         throw "error operator +";
//     //     }

//         for (int i = 0; i < n_rows; i++){
//             for (int j = 0; j < matr.m_cols;j++){
//                 this->matrix_value[i*m_cols+j] = this->matrix_value[i*m_cols+j] + matr.matrix_value[i*m_cols+j];
//             }
//         }
//         return *this;
//     // }catch (const char * str){
//     //     std::cout << str << std::endl;
//     //     return *this;
//     // }
// }