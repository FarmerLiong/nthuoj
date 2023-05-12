#include <iostream>
using namespace std;
const int mod = 1000000009;

class Matrix {
private:
  int n;
  long long **matrix;
public:
  // The Default Constructor
  Matrix() {
    n = 0;
    matrix = nullptr;
  }
  // TODO: The Destructor
  ~Matrix();

  // TODO: The Customize Constructor
  Matrix(int n);
  
  // TODO: Copy contructor
  // Will be trigger when the following condition:
  // Matrix m = ref; -> Call copy contructor to copy from 'ref' to 'm'
  Matrix(const Matrix& ref);

  // TODO: copy assignment,
  // Will be trigger when the following condition:
  // Matrix a;
  // a = ref; -> Call copy assignment to copy from 'ref' to 'a'
  Matrix& operator=(const Matrix& ref);

  // TODO: Overload operator()
  // This operator allow the following code
  // This operator can help you access the data easily
  // 1. cout << m(1, 2) << endl; -> Shorthand of `cout << m.matrix[1, 2] << endl;`
  // 2. m(1, 2) = 100; -> Shorthand of `m.matrix[1, 2] = 100`
  long long& operator()(const int& row, const int& column) const;

  // Utilities functions
  // TODO: Make the matrix identity matrix
  void toIdentity();
  void toZero() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        matrix[i][j] = 0;
    }
  }

  // TODO: Overload operator * 
  Matrix operator*(const Matrix& rhs) const;

  // TODO: Return the matrix power of 'k'
  Matrix power(int k) const;

  friend ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.n; i++) {
      for (int j = 0; j < matrix.n; j++)
        os << matrix(i, j) << ' ';
      os << endl;
    }
    return os;
  }
};

// TODO: Construct a matrix
Matrix constructMatrix(int n);


int main() {
  int n, m;
  cin >> n >> m;
  if (m <= n) {
    cout << 1 << endl;
  } else {
    Matrix base = constructMatrix(n);
    base = base.power(m - n);
    int ans = 0;
    for (int i = 0; i < n; i++)
      ans = (ans + base(n - 1, i)) % mod;
    cout << ans << endl;
  }
  return 0;
}

Matrix::~Matrix() {
  for (int i = 0; i < n; i++) delete[] matrix[i];
  delete[] matrix;  
}

Matrix::Matrix(int n) {
  this->n = n;
  this->matrix = new long long*[n];
  for (int i = 0; i < n; i++)
    this->matrix[i] = new long long[n];
}

Matrix::Matrix(const Matrix& ref) {
  this->n = ref.n;
  this->matrix = new long long*[n];
  for (int i = 0; i < n; i++) {
    this->matrix[i] = new long long[n];
    for (int j = 0; j < n; j++) 
      this->matrix[i][j] = ref(i, j);
  }
}

Matrix& Matrix::operator=(const Matrix& ref) {
  this->n = ref.n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      this->matrix[i][j] = ref(i, j);
  return *this;
}

long long& Matrix::operator()(const int& row, const int& coloumn) const {
  return this->matrix[row][coloumn];
}

void Matrix::toIdentity() {
  for (int i = 0; i < n; i++)
    this->matrix[i][i] = 1;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
  Matrix M(this->n);
  for (int row = 0; row < this->n; row++) {
    for (int col = 0; col < this->n; col++) {
      for (int i = 0; i < this->n; i++) {
        M(row, col) = (M(row, col) + this->matrix[row][i]* rhs(i, col) )% mod;
      }
    }
  }
  return M;
} 

Matrix Matrix::power(int k) const {
  Matrix init(this->n);
  Matrix ret(*this);
  init.toIdentity();
  while(k) {
    if (k % 2) init = init * ret;
    ret = ret * ret;
    k /= 2;
  }
  return init;
}

Matrix constructMatrix(int n) {
  Matrix M(n);
  for (int i = 1; i < n; i++) M(i - 1, i) = 1; 
  for (int i = 0; i < n; i++) M(n - 1, i) = 1; 
  return M;
}