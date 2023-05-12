#include "function.h"
using namespace std;

Matrix::~Matrix(){
    for (int i = 0; i < n; i++) {
        delete [] this->matrix[i];
    } delete this->matrix;
}

Matrix::Matrix(int n){
    this->n = n;
    this->matrix = new long long*[n];
    for (int i = 0; i < n; i++) {
        this->matrix[i] = new long long[n];
    }
    toZero();    
}

Matrix::Matrix(const Matrix& ref){
    this->n = ref.n;
    this->matrix = new long long*[n];
    for (int i = 0; i < n; i++) {
        this->matrix[i] = new long long[n];
        for (int j = 0; j < n; j++) {
            this->matrix[i][j] = ref(i, j);
        }
    }
}

Matrix& Matrix::operator=(const Matrix& ref){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            this->matrix[i][j] = ref(i, j);
        }
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const {
    return this->matrix[row][column];
} 

void Matrix::toIdentity(){
    for (int i = 0; i < n; i++) 
        this->matrix[i][i] = 1;
}
 
Matrix Matrix::operator*(const Matrix& rhs) const {
    Matrix M(n);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            for (int i = 0; i < n; i++) {
                M(row, col) = (M(row,col) + this->matrix[row][i] * rhs(i, col)) % mod;
            }
            // cout << M(row, col) << " ";
        }
        // cout << endl;
    }
    return M;
}

void show(const Matrix& m) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << m(row, col);
        }
        cout << endl;
    }
}

Matrix Matrix::power(int k) const {
    Matrix init(this->n);
    Matrix ret(this->n);
    ret = *this;
    init.toIdentity();
    while (k) {
        if (k % 2 == 1) init = init * ret;
        ret = ret * ret;
        k /= 2;
    }
    return init;
}

Matrix constructMatrix(int n){
//  construct ret matrix
    Matrix ret(n);
    for (int i = 1; i < n; i++) ret(i-1, i) = 1;
    for (int i = 0; i < n; i++) ret(n-1, i) = 1;
    return ret;
}

