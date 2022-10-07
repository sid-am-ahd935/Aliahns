# Library Details
Library namespace name: `mtx`

Library class name: `Matrix`

## Member variables

#### Row size of matrix
```c++
int rows
```

#### Column size of matrix
```c++
int cols
```

## Overloaded operators
 - `+` Adds to matrices
 - `-` Subtracts 2nd from 1st matrix
 - `*` Multiplies a matrix with a scalar or another matrix
 - `^` Calculates power (+ve integer) of a matrix
 - `==` Compares two matrices for equality

## Member functions

#### Create a null matrix of given size
 - `param` n rows of matrix
 - `param` cols? cols of matrix
 - `return` Matrix<type> a null matrix
 - `throws` mtx::Exception row index out of bounds - `E_ROUTB`
 - `throws` mtx::Exception column index out of bounds - `E_COUTB`
```c++
static Matrix<type> O(int n, int cols = 0)
```

#### Create a unit matrix of given size
 - `param` n size of matrix
 - `return` Matrix<type> a unit matrix
 - `throws` mtx::Exception row index out of bounds - `E_ROUTB`
 - `throws` mtx::Exception column index out of bounds - `E_COUTB`
```c++
static Matrix<type> I(int n)
```

#### Create empty matrix object
 - `param` rows If DDA is unknown, pass no. of rows
 - `param` cols If DDA is unknown, pass no. of cols
 - `throws` mtx::Exception matrix can't have 0 rows - `E_0ROWS`
 - `throws` mtx::Exception matrix can't have 0 columns - `E_0COLS`
```c++
explicit Matrix(int rows, int cols)
```

#### Create matrix object from DDA
The constructor accepts address to 1st element of the C++ DDA.
See [demo.cpp](demo.cpp).
 - `param` rows Row size of DDA
 - `param` cols Column size of DDA
 - `param` arr If DDA is known, pass &dda[0][0]
 - `throws` mtx::Exception matrix can't have 0 rows - `E_0ROWS`
 - `throws` mtx::Exception matrix can't have 0 columns - `E_0COLS`
```c++
explicit Matrix(int rows, int cols, type *arr)
```

#### Get an element of the matrix from an index
 - `param` i row wise position of element
 - `param` j column wise position of element
 - `return` type The value at index i, j
 - `throws` mtx::Exception row index out of bounds - `E_ROUTB`
 - `throws` mtx::Exception column index out of bounds - `E_COUTB`
```c++
type get(int i, int j)
```

#### Set an element of the matrix to an index
 - `param` i row wise position of element
 - `param` j column wise position of element
 - `param` val value to be set
 - `throws` mtx::Exception row index out of bounds - `E_ROUTB`
 - `throws` mtx::Exception column index out of bounds - `E_COUTB`
```c++
void set(int i, int j, type val)
```

#### Compare two matrices for equality
 - `param` m2 The matrix to compare to
 - `return` boolean true if equal
```c++
bool equals(Matrix<type>& m2)
```

#### Add two compatible matrices
 - `param` m2 The matrix to add
 - `return` Matrix<type> The matrix of sums
 - `throws` mtx::Exception If matrices aren't compatible - `E_INCMP`
```c++
Matrix<type> add(Matrix<type>& m2)
```

#### Subtract two compatible matrices
 - `param` m2 The matrix to subtract
 - `return` Matrix<type> The matrix of differences
 - `throws` mtx::Exception If matrices aren't compatible - `E_INCMP`
```c++
Matrix<type> subtract(Matrix<type>& m2)
```

#### Multiply a matrix by a scalar
 - `param` scalar Scalar to multiply by
 - `return` matrix The matrix of products
```c++
Matrix<type> scale(type scalar)
```

#### Multiply two compatible matrices
 - `param` m2 The matrix to multiply by
 - `return` Matrix<type> The matrix after multiplication
 - `throws` mtx::Exception If matrices aren't compatible - `E_INCMP`
```c++
Matrix<type> multiply(Matrix<type>& m2)
```

#### Calculate matrix to the power of index
 - `param` index Power of matrix
 - `return` Matrix<type> The resulting matrix
 - `throws` mtx::Exception same as errors of Matrix::multiply method
```c++
Matrix<type> power(int index)
```

#### Exclude a row and a column
Useful for calculating determinants and cofactor matrices.
 - `param` row The row to exclude
 - `param` col The column to exclude
 - `return` Matrix<type> The sub matrix
 - `throws` mtx::Exception row index out of bounds - `E_ROUTB`
 - `throws` mtx::Exception column index out of bounds - `E_COUTB`
```c++
Matrix<type> excludeRowCol(int row, int col)
```

#### Calculate determinant of matrix
 - `return` double The determinant
 - `throw` mtx::Exception If matrix isn't a square matrix - `E_NOSQR`
```c++
double determinant()
```

#### Calculate the transpose of this matrix
 - `return` Matrix<type> The transpose
```c++
Matrix<type> transpose()
```

#### Calculate the cofactor matrix of this matrix
 - `return` Matrix<type> The cofactor matrix
 - `throws` mtx::Exception If matrix isn't a square matrix - `E_NOSQR`
```c++
Matrix<type> cofactor()
```

#### Calculate the adjoint of this matrix
 - `return` Matrix<type> The adjoint
 - `throws` mtx::Exception If matrix isn't a square matrix - `E_NOSQR`
```c++
Matrix<type> adjoint()
```

#### Calculate the inverse of this matrix
 - `return` Matrix<double> The inverse
 - `throws` mtx::Exception If matrix isn't a square matrix - `E_NOSQR`
 - `throws` mtx::Exception If determinant is 0 - `E_DETR0`
```c++
Matrix<double> inverse()
```

#### Display the matrix
 - `param` msg? The message to print
```c++
void print(const std::string& msg = "")
```

## Details of possible exceptions
Each exception has type of `mtx::Exception` and may have a value equal to the following
 - `E_0ROWS`  matrix can't have 0 rows
 - `E_0COLS`  matrix can't have 0 columns
 - `E_ROUTB`  row index out of bounds
 - `E_COUTB`  column index out of bounds
 - `E_INCMP`  incompatible matrices
 - `E_NOSQR`  not a square matrix
 - `E_DETR0`  during inversion, determinant is 0
