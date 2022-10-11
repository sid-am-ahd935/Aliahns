# Library Details
Library namespace name: `Matrix`

Library class name: `matrix`

## Member variables

#### Row count of matrix
```c++
int rows()
```

#### Column count of matrix
```c++
int cols()
```

## Overloaded operators
 - `=` Copy matrix references
 - `+` Add two matrices
 - `-` Subtract 2nd from 1st matrix
 - `*` Multiply a matrix with a scalar or another matrix
 - `^` Calculate matrix to the power of +ve integer
 - `==` Compare two matrices for equality
 - `[][]` Access a posn of the matrix

## Member functions

#### Create a null matrix of given size
 - `param` n Rows of matrix
 - `param` cols? Cols of matrix
 - `return` matrix<type> A null matrix
 - `throws` Matrix::Exception Row index out of bounds - `EX_ROUTB`
 - `throws` Matrix::Exception Column index out of bounds - `EX_COUTB`
```c++
matrix<type> Matrix::O<type>(int n, int cols = 0)
```

#### Create a unit matrix of given size
 - `param` n Size of matrix
 - `return` matrix<type> A unit matrix
 - `throws` Matrix::Exception Row index out of bounds - `EX_ROUTB`
 - `throws` Matrix::Exception Column index out of bounds - `EX_COUTB`
```c++
matrix<type> Matrix::I<type>(int n)
```

#### Create null Matrix object
 - `param` rows If DDA is unknown, pass no. of rows
 - `param` cols If DDA is unknown, pass no. of cols
 - `throws` Matrix::Exception Matrix can't have 0 rows - `EX_0ROWS`
 - `throws` Matrix::Exception Matrix can't have 0 columns - `EX_0COLS`
```c++
matrix(int rows, int cols)
```

#### Create a new matrix object
 - `param` lst 2D initializer list. See [demo.cpp](demo.cpp)
 - `throws` Matrix::Exception Matrix can't have 0 rows - EX_0ROWS
 - `throws` Matrix::Exception Matrix can't have 0 columns - EX_0COLS
```c++
matrix(initializer_list<initializer_list<type>> lst)
```

#### Create Matrix object from DDA
The constructor accepts address to 1st element of the C++ DDA.
 - `param` rows Row size of DDA
 - `param` cols Column size of DDA
 - `param` arr If DDA is known, pass &dda[0][0]
 - `throws` Matrix::Exception Matrix can't have 0 rows - `EX_0ROWS`
 - `throws` Matrix::Exception Matrix can't have 0 columns - `EX_0COLS`
```c++
matrix(int rows, int cols, type *arr)
```

#### Copy a Matrix object via constructor
Matrix uses smart reference counting approach.
When all references are cleared, the memory is auto deleted on scope close.
 - `param` m2 The source matrix
```c++
matrix(const matrix<type>& m2)
```

#### Get an element of the matrix from an index
 - `param` i Row wise position of element
 - `param` j Column wise position of element
 - `return` type The value at index i, j
 - `throws` Matrix::Exception Row index out of bounds - `EX_ROUTB`
 - `throws` Matrix::Exception Column index out of bounds - `EX_COUTB`
```c++
type get(int i, int j)
```

#### Set an element of the matrix to an index
 - `param` i Row wise position of element
 - `param` j Column wise position of element
 - `param` val Value to be set
 - `throws` Matrix::Exception Row index out of bounds - `EX_ROUTB`
 - `throws` Matrix::Exception Column index out of bounds - `EX_COUTB`
```c++
void set(int i, int j, type val)
```

#### Compare two matrices for equality
 - `param` m2 The matrix to compare to
 - `return` boolean True if equal
```c++
bool equals(const matrix<type>& m2)
```

#### Add two compatible matrices
 - `param` m2 The matrix to add
 - `return` matrix<type> The matrix of sums
 - `throws` Matrix::Exception If matrices aren't compatible - `EX_INCMP`
```c++
matrix<type> add(const matrix<type>& m2)
```

#### Subtract 2nd from 1st matrix
 - `param` m2 The matrix to subtract
 - `return` matrix<type> The matrix of differences
 - `throws` Matrix::Exception If matrices aren't compatible - `EX_INCMP`
```c++
matrix<type> subtract(const matrix<type>& m2)
```

#### Multiply a matrix by a scalar
 - `param` scalar Scalar to multiply by
 - `return` matrix The matrix of products
```c++
matrix<type> scale(type scalar)
```

#### Multiply two compatible matrices
 - `param` m2 The matrix to multiply by
 - `return` matrix<type> The matrix after multiplication
 - `throws` Matrix::Exception If matrices aren't compatible - `EX_INCMP`
```c++
matrix<type> multiply(const matrix<type>& m2)
```

#### Calculate matrix to the power of +ve integer
 - `param` index Power of matrix
 - `return` matrix<type> The resulting matrix
 - `throws` Matrix::Exception Same as errors of Matrix::multiply method
```c++
matrix<type> power(int index)
```

#### Exclude a row and a column
Useful for calculating determinants and cofactor matrices.
 - `param` row The row to exclude
 - `param` col The column to exclude
 - `return` matrix<type> The sub matrix
 - `throws` Matrix::Exception Row index out of bounds - `EX_ROUTB`
 - `throws` Matrix::Exception Column index out of bounds - `EX_COUTB`
```c++
matrix<type> excludeRowCol(int row, int col)
```

#### Calculate determinant of this matrix
 - `return` double The determinant
 - `throw` Matrix::Exception If matrix isn't a square matrix - `EX_NOSQR`
```c++
double determinant()
```

#### Calculate the transpose of this matrix
 - `return` matrix<type> The transpose
```c++
matrix<type> transpose()
```

#### Calculate the cofactor matrix of this matrix
 - `return` matrix<type> The cofactor matrix
 - `throws` Matrix::Exception If matrix isn't a square matrix - `EX_NOSQR`
```c++
matrix<type> cofactor()
```

#### Calculate the adjoint of this matrix
 - `return` matrix<type> The adjoint
 - `throws` Matrix::Exception If matrix isn't a square matrix - `EX_NOSQR`
```c++
matrix<type> adjoint()
```

#### Calculate the inverse of this matrix
 - `return` matrix<double> The inverse
 - `throws` Matrix::Exception If matrix isn't a square matrix - `EX_NOSQR`
 - `throws` Matrix::Exception If determinant is 0 - `EX_DETR0`
```c++
matrix<double> inverse()
```

#### Display the matrix
 - `param` msg? The message to print
```c++
void print(const std::string& msg = "")
```

## Details of possible exceptions
Each exception has type of `Matrix::Exception` and may have a value equal to the following
 - `EX_0ROWS`  Matrix can't have 0 rows
 - `EX_0COLS`  Matrix can't have 0 columns
 - `EX_ROUTB`  Row index out of bounds
 - `EX_COUTB`  Column index out of bounds
 - `EX_INCMP`  Incompatible matrices
 - `EX_NOSQR`  Not a square matrix
 - `EX_DETR0`  During inversion, determinant is 0

## Compiler flags
The following flags can be enabled by using `-D` option as a CLI argument to `g++` and `clang++`.
 - `-D DEBUG` On `Matrix::Exception` prints the message.
 - `-D ALLOW_PRIMITIVES_ONLY` Only allows matrix of primitive datatype.
