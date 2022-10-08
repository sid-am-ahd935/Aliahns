#pragma once

#include <iostream>
#include <string>

namespace mtx
{
    // type error
    typedef const std::string& Exception;

    // possible exceptions
    const char *E_0ROWS = "E_0ROWS";
    const char *E_0COLS = "E_0COLS";
    const char *E_ROUTB = "E_ROUTB";
    const char *E_COUTB = "E_COUTB";
    const char *E_INCMP = "E_INCMP";
    const char *E_NOSQR = "E_NOSQR";
    const char *E_DETR0 = "E_DETR0";

    template <typename type>
    class Matrix
    {
    public:

        /**
         * Row number of this matrix
         */
        int rows;

        /**
         * Column number of this matrix
         */
        int cols;

        /**
         * Double pointer to matrix data location
         */
        type **matrix;

        /**
         * Create a null matrix of given size
         * @param n rows of matrix
         * @param cols? cols of matrix
         * @return Matrix<type> a null matrix
         * @throws Exception row index out of bounds - E_ROUTB
         * @throws Exception column index out of bounds - E_COUTB
         */
        static Matrix<type> O(int n, int cols = 0)
        {
            if (cols == 0)
                cols = n;
            return Matrix<type>(n, cols, true);
        }

        /**
         * Create a unit matrix of given size
         * @param n size of matrix
         * @return Matrix<type> a unit matrix
         * @throws Exception row index out of bounds - E_ROUTB
         * @throws Exception column index out of bounds - E_COUTB
         */
        static Matrix<type> I(int n)
        {
            Matrix<type> im = Matrix<type>(n, n);
            for (int i = 0; i < n; i++)
                im.set(i, i, 1);
            return im;
        }

        /**
         * Default constructor
         */
        explicit Matrix()
        {
            this->rows = 0;
            this->cols = 0;
            this->matrix = nullptr;
        }

        /**
         * Create a new Matrix object
         * @param rows If DDA is unknown, pass no. of rows
         * @param cols If DDA is unknown, pass no. of cols
         * @throws Exception matrix can't have 0 rows - E_0ROWS
         * @throws Exception matrix can't have 0 columns - E_0COLS
         */
        explicit Matrix(int rows, int cols)
        {
            if (rows < 1)
                this->throwException(E_0ROWS, "matrix can't have 0 rows");
            if (cols < 1)
                this->throwException(E_0COLS, "matrix can't have 0 columns");
            this->rows = rows;
            this->cols = cols;
            this->matrix = new type*[rows];
            for (int i = 0; i < this->rows; i++) {
                this->matrix[i] = new type[cols];
                for (int j = 0; j < this->cols; j++)
                    this->set(i, j, 0);
            }
        }

        /**
         * Create a new Matrix object
         * @param rows Row size of DDA
         * @param cols Column size of DDA
         * @param arr If DDA is known, pass &dda[0][0]
         * @throws Exception matrix can't have 0 rows - E_0ROWS
         * @throws Exception matrix can't have 0 columns - E_0COLS
         */
        explicit Matrix(int rows, int cols, type *arr)
        {
            if (rows < 1)
                this->throwException(E_0ROWS, "matrix can't have 0 rows");
            if (cols < 1)
                this->throwException(E_0COLS, "matrix can't have 0 columns");
            this->rows = rows;
            this->cols = cols;
            this->matrix = new type*[rows];
            for (int i = 0; i < this->rows; i++) {
                this->matrix[i] = new type[cols];
                for (int j = 0; j < this->cols; j++)
                    this->set(i, j, arr[i*cols +j]);
            }
        }

        /**
         * Constructs a Matrix<double> from a Matrix<type>
         */
        Matrix<double> toDoubleMatrix()
        {
            Matrix<double> dm;
            dm.rows = this->rows;
            dm.cols = this->cols;
            dm.matrix = new double*[rows];
            for (int i = 0; i < dm.rows; i++) {
                dm.matrix[i] = new double[cols];
                for (int j = 0; j < dm.cols; j++)
                    dm.set(i, j, (double) this->get(i, j));
            }
            return dm;
        }

        /**
         * Clears the array of the matrix instance on scope exit
         */
        ~Matrix()
        {
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;
        }

        /**
         * Throw an exception with value = error code
         */
        void throwException(const std::string& errcode, const std::string& msg)
        {
        #ifdef DEBUG
            std::cout << "error: " << errcode << ": " << msg << "\n";
        #endif
            throw errcode;
        }

        /**
         * Get an element of the matrix from an index
         * @param i row wise position of element
         * @param j column wise position of element
         * @return <type> The value at index i, j
         * @throws Exception row index out of bounds - E_ROUTB
         * @throws Exception column index out of bounds - E_COUTB
         */
        type get(int i, int j)
        {
            if (i < 0 || i > this->rows)
                this->throwException(E_ROUTB, "row index out of bounds");
            if (j < 0 || j > this->rows)
                this->throwException(E_COUTB, "column index out of bounds");
            return this->matrix[i][j];
        }

        /**
         * Set an element of the matrix to an index
         * @param i row wise position of element
         * @param j column wise position of element
         * @param val value to be set
         * @throws Exception row index out of bounds - E_ROUTB
         * @throws Exception column index out of bounds - E_COUTB
         */
        void set(int i, int j, type val)
        {
            if (i < 0 || i > this->rows)
                this->throwException(E_ROUTB, "row index out of bounds");
            if (j < 0 || j > this->cols)
                this->throwException(E_COUTB, "column index out of bounds");
            this->matrix[i][j] = val;
        }

        /*
         * Compares two matrices for equality
         * @param m2 The matrix to compare to
         * @return boolean true if equal
         */
        bool equals(Matrix<type>& m2)
        {
            if (this->rows != m2.rows || this->cols != m2.cols)
                return false;
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    if (this->get(i, j) != m2.get(i, j))
                        return false;
            return true;
        }

        /**
         * Add two compatible matrices
         * @param m2 The matrix to add
         * @return Matrix<type> The matrix of sums
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> add(Matrix<type>& m2, bool sub = false)
        {
            if (m2.rows != this->rows || m2.cols != this->cols)
                this->throwException(E_INCMP, "incompatible matrices for addition");
            Matrix<type> nm = Matrix<type>(this->rows, this->cols);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++) {
                    type rslt = this->get(i, j) + (sub ? (-1) * m2.get(i, j) : m2.get(i, j));
                    nm.set(i, j, rslt);
                }
            return nm;
        }

        /**
         * Subtract two compatible matrices
         * @param m2 The matrix to subtract
         * @return Matrix<type> The matrix of differences
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> subtract(Matrix<type>& m2)
        {
            if (m2.rows != this->rows || m2.cols != this->cols)
                this->throwException(E_INCMP, "incompatible matrices for subtraction");
            return this->add(m2, true);
        }

        /**
         * Multiplies a matrix by a scalar
         * @param scalar Scalar to multiply by
         * @return Matrix The matrix of products
         */
        Matrix<type> scale(type scalar)
        {
            Matrix<type> nm = Matrix<type>(this->rows, this->cols);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++) {
                    type rslt = scalar * this->get(i, j);
                    nm.set(i, j, rslt);
                }
            return nm;
        }

        /**
         * Multiplies two compatible matrices
         * @param m2 The matrix to multiply by
         * @return Matrix<type> The matrix after multiplication
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> multiply(Matrix<type>& m2)
        {
            if (this->cols != m2.rows)
                this->throwException(E_INCMP, "incompatible matrices for multiplication");
            int m = this->rows;
            int n = this->cols; // same
            n = m2.rows;        // same
            int o = m2.cols;
            Matrix<type> nm = Matrix<type>(m, o);
            for (int i = 0; i < m; i++)
                for (int j = 0; j < o; j++) {
                    double sum = 0;
                    for (int k = 0; k < n; k++)
                        sum += this->get(i, k) * m2.get(k, j);
                    nm.set(i, j, sum);
                }
            return nm;
        }

        /**
         * Calculate matrix to the power of index
         * @param index Power of matrix
         * @return Matrix<type> The resulting matrix
         * @throws Exception same as errors of Matrix::multiply method
         */
        Matrix<type> power(int index)
        {
            Matrix<type> nm = *this;
            for (int i = 0; i < index - 1; i++) {
                Matrix<type> tmp = nm.multiply(*this);
                nm = tmp;
            }
            return nm;
        }

        /*
         * Compares two matrices for equality
         * @param m2 The matrix to compare to
         * @return boolean true if equal
         */
        bool operator==(Matrix<type>& m2)
        {
            return this->equals(m2);
        }

        /**
         * Add two compatible matrices
         * @param m2 The matrix to add
         * @return Matrix<type> The matrix of sums
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> operator+(Matrix<type>& m2)
        {
            return this->add(m2);
        }

        /**
         * Subtract two compatible matrices
         * @param m2 The matrix to subtract
         * @return Matrix<type> The matrix of differences
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> operator-(Matrix<type>& m2)
        {
            return this->subtract(m2);
        }

        /**
         * Multiplies a matrix by a scalar
         * @param scalar Scalar to multiply by
         * @return Matrix The matrix of products
         */
        Matrix<type> operator*(type scalar)
        {
            return this->scale(scalar);
        }

        /**
         * Multiplies two compatible matrices
         * @param m2 The matrix to multiply by
         * @return Matrix<type> The matrix after multiplication
         * @throws Exception If matrices aren't compatible - E_INCMP
         */
        Matrix<type> operator*(Matrix<type>& m2)
        {
            return this->multiply(m2);
        }

        /**
         * Calculate matrix to the power of index
         * @param index Power of matrix
         * @return Matrix<type> The resulting matrix
         * @throws Exception same as errors of Matrix::multiply method
         */
        Matrix<type> operator^(int index)
        {
            return this->power(index);
        }

        /**
         * Excludes a row and a column and generates a sub matrix. Useful for calculating determinants and cofactor matrices.
         * @param row The row to exclude
         * @param col The column to exclude
         * @return Matrix<type> The sub matrix
         * @throws Exception row index out of bounds - E_ROUTB
         * @throws Exception column index out of bounds - E_COUTB
         */
        Matrix<type> excludeRowCol(int row, int col)
        {
            if (row < 0 || row > this->rows)
                this->throwException(E_ROUTB, "row index out of bounds");
            if (col < 0 || col > this->rows)
                this->throwException(E_COUTB, "column index out of bounds");
            Matrix<type> subm = Matrix(this->rows - 1, this->cols - 1);
            bool skipRow = false;
            for (int j = 0; j < this->rows - 1; j++) {
                bool skipCol = false;
                int jSelf = j;
                if (j == row)
                    skipRow = true;
                if (skipRow)
                    jSelf++;
                for (int k = 0; k < this->cols - 1; k++) {
                    int kSelf = k;
                    if (k == col)
                        skipCol = true;
                    if (skipCol)
                        kSelf++;
                    subm.set(j, k, this->get(jSelf, kSelf));
                }
            }
            return subm;
        }

        /**
         * Calculate determinant of matrix
         * @return double The determinant
         * @throw Exception If matrix isn't a square matrix - E_NOSQR
         */
        double determinant()
        {
            if (this->rows != this->cols)
                this->throwException(E_NOSQR, "not a square matrix");
            int n = this->rows;
            double det = 0;
            if (n == 1)
                return this->get(0, 0);
            else if (n == 2)
                return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);
            else
                for (int i = 0; i < n; i++) {
                    double coeff = pow(-1, i) * this->get(0, i);
                    Matrix<type> subm = this->excludeRowCol(0, i);
                    double subdet = subm.determinant();
                    double term = coeff * subdet;
                    det += term;
                }
            return det;
        }

        /**
         * Calculate the transpose of this matrix
         * @return Matrix<type> The transpose
         */
        Matrix<type> transpose()
        {
            Matrix<type> nm = Matrix<type>(this->cols, this->rows);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++)
                    nm.set(j, i, this->get(i, j));
            return nm;
        }

        /**
         * Calculate the cofactor matrix of this matrix
         * @return Matrix<type> The cofactor matrix
         * @throws Exception If matrix isn't a square matrix - E_NOSQR
         */
        Matrix<type> cofactor()
        {
            if (this->rows != this->cols)
                this->throwException(E_NOSQR, "not a square matrix");
            Matrix<type> nm = Matrix<type>(this->rows, this->cols);
            for (int i = 0; i < this->rows; i++)
                for (int j = 0; j < this->cols; j++) {
                    double coeff = pow(-1, i + 1 + j + 1);
                    Matrix<type> subm = this->excludeRowCol(i, j);
                    nm.set(i, j, coeff * subm.determinant());
                }
            return nm;
        }

        /**
         * Calculate the adjoint of this matrix
         * @return Matrix<type> The adjoint
         * @throws Exception If matrix isn't a square matrix - E_NOSQR
         */
        Matrix<type> adjoint()
        {
            if (this->rows != this->cols)
                this->throwException(E_NOSQR, "not a square matrix");
            return this->cofactor().transpose();
        }

        /**
         * Calculate the inverse of this matrix
         * @return Matrix<double> The inverse
         * @throws Exception If matrix isn't a square matrix - E_NOSQR
         * @throws Exception If determinant is 0 - E_DETR0
         */
        Matrix<double> inverse()
        {
            if (this->rows != this->cols)
                this->throwException(E_NOSQR, "not a square matrix");
            double determinant = this->determinant();
            if (determinant == 0)
                this->throwException(E_DETR0, "determinant is 0");
            return this->adjoint().scale(1/determinant).toDoubleMatrix();
        }

        /**
         * Display the matrix
         * @param msg? The message to print
         */
        void print(const std::string& msg = "")
        {
            if (msg != "")
                std::cout << msg << "\n";
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->cols; j++)
                    std::cout << this->get(i, j) << ((j < this->cols -1)? ", " : "");
                std::cout << "\n";
            }
        }
    };
}
