#pragma once

#include <iostream>
#include <string>

namespace Matrix
{
    template <typename type> class matrix;

    // type Exception
    typedef const int Exception;

    // possible exceptions
    static const int EX_0ROWS = 10;       // matrix can't have 0 rows
    static const int EX_0COLS = 20;       // matrix can't have 0 columns
    static const int EX_ROUTB = 30;       // row index out of bounds
    static const int EX_COUTB = 40;       // column index out of bounds
    static const int EX_INCMP = 50;       // incompatible matrices
    static const int EX_NOSQR = 60;       // not a square matrix
    static const int EX_DETR0 = 70;       // during inversion, determinant is 0

    // more general exceptions
    static const int EX_NULLPTR = 100;    // null pointer exception

    /**
     * Throw an exception with value = exception code.
     * @throws Matrix::Exception
     */
    void throwException(Exception ex, const std::string& msg)
    {
    #ifdef DEBUG
        std::cout << "Matrix::Exception::" << ex << ": " << msg << "\n";
    #endif
        throw ex;
    }

    template <typename type>
    class matrix
    {
        static_assert(std::is_fundamental<type>::value, "Matrix::matrix: template argument should be a primitive type");

    public:
        /**
         * Only another matrix can access properties of a matrix directly
         */
        template <typename T> friend class matrix;

        /**
         * Get row count of matrix.
         * @return int
         */
        int rows() const
        {
            return (int) *this->rows_ptr;
        }

        /**
         * Get column count of matrix.
         * @return int
         */
        int cols() const
        {
            return (int) *this->cols_ptr;
        }

        /**
         * Create a new matrix object.
         * @param rows If DDA is unknown, pass no. of rows
         * @param cols If DDA is unknown, pass no. of cols
         * @throws Matrix::Exception Matrix can't have 0 rows - EX_0ROWS
         * @throws Matrix::Exception Matrix can't have 0 columns - EX_0COLS
         */
        matrix(int rows, int cols)
        {
            if (rows < 1)
                Matrix::throwException(EX_0ROWS, "matrix can't have 0 rows");
            if (cols < 1)
                Matrix::throwException(EX_0COLS, "matrix can't have 0 columns");
            this->rows_ptr = new int(rows);
            this->cols_ptr = new int(cols);
            this->mtx_ptr = new type*[rows];
            for (int i = 0; i < this->rows(); i++) {
                this->mtx_ptr[i] = new type[cols];
                for (int j = 0; j < this->cols(); j++)
                    this->mtx_ptr[i][j] = 0;
            }
            this->refcnt_ptr = new int(1);
        }

        /**
         * Create a new matrix object.
         * @param lst 2D Initialiser list
         * @throws Matrix::Exception Matrix can't have 0 rows - EX_0ROWS
         * @throws Matrix::Exception Matrix can't have 0 columns - EX_0COLS
         */
        matrix(std::initializer_list<std::initializer_list<type>> lst)
        {
            int rows = lst.size();
            int cols = lst.begin()->size();
            if (rows < 1)
                Matrix::throwException(EX_0ROWS, "matrix can't have 0 rows");
            if (cols < 1)
                Matrix::throwException(EX_0COLS, "matrix can't have 0 columns");
            this->rows_ptr = new int(rows);
            this->cols_ptr = new int(cols);
            this->mtx_ptr = new type*[rows];
            int i = 0;
            for (const auto& lrow : lst) {
                this->mtx_ptr[i] = new type[cols];
                int j = 0;
                for (const auto& el : lrow) {
                    this->mtx_ptr[i][j] = el;
                    j++;
                }
                i++;
            }
            this->refcnt_ptr = new int(1);
        }

        /**
         * Create a new matrix object.
         * @param rows Row size of DDA
         * @param cols Column size of DDA
         * @param arr If DDA is known, pass &dda[0][0]
         * @throws Matrix::Exception Matrix can't have 0 rows - EX_0ROWS
         * @throws Matrix::Exception Matrix can't have 0 columns - EX_0COLS
         */
        matrix(int rows, int cols, type *arr)
        {
            if (rows < 1)
                Matrix::throwException(EX_0ROWS, "matrix can't have 0 rows");
            if (cols < 1)
                Matrix::throwException(EX_0COLS, "matrix can't have 0 columns");
            this->rows_ptr = new int(rows);
            this->cols_ptr = new int(cols);
            this->mtx_ptr = new type*[rows];
            for (int i = 0; i < this->rows(); i++) {
                this->mtx_ptr[i] = new type[cols];
                for (int j = 0; j < this->cols(); j++)
                    this->mtx_ptr[i][j] = arr[i*cols +j];
            }
            this->refcnt_ptr = new int(1);
        }

        /**
         * Copy a matrix object via constructor.
         * matrix uses smart reference counting approach. When all references are cleared, the memory is auto deleted.
         * @param m2 The source matrix
         */
        matrix(const matrix<type>& m2)
        {
            if (!m2.refcnt_ptr) Matrix::throwException(EX_NULLPTR, "null pointer exception");
            this->mtx_ptr = m2.mtx_ptr;
            this->rows_ptr = m2.rows_ptr;
            this->cols_ptr = m2.cols_ptr;
            this->refcnt_ptr = m2.refcnt_ptr;
            (*this->refcnt_ptr)++;
        }

        /**
         * Copy a matrix object through assignment.
         * matrix uses smart reference counting approach. When all references are cleared, the memory is auto deleted.
         * @param m2 The source matrix
         */
        matrix<type> operator=(const matrix<type>& m2)
        {
            if (!m2.refcnt_ptr) Matrix::throwException(EX_NULLPTR, "null pointer exception");
            // release old matrix data
            (*this->refcnt_ptr)--;
            if ((*this->refcnt_ptr) == 0) {
                for (int i = 0; i < this->rows(); i++)
                    delete[] this->mtx_ptr[i];
                delete[] this->mtx_ptr;
                delete this->rows_ptr;
                delete this->cols_ptr;
                delete this->refcnt_ptr;
            }
            // catch new matrix data
            this->mtx_ptr = m2.mtx_ptr;
            this->rows_ptr = m2.rows_ptr;
            this->cols_ptr = m2.cols_ptr;
            this->refcnt_ptr = m2.refcnt_ptr;
            (*this->refcnt_ptr)++;
            return *this;
        }

        /**
         * Construct a matrix<double> from a matrix<type>.
         */
        matrix<double> toDoubleMatrix()
        {
            matrix<double> dm;
            dm.rows_ptr = new int(this->rows());
            dm.cols_ptr = new int(this->cols());
            dm.refcnt_ptr = new int(1);
            dm.mtx_ptr = new double*[this->rows()];
            for (int i = 0; i < dm.rows(); i++) {
                dm.mtx_ptr[i] = new double[this->cols()];
                for (int j = 0; j < dm.cols(); j++)
                    dm[i][j] = (double) this->mtx_ptr[i][j];
            }
            return dm;
        }

        /**
         * Clears the array of the matrix instance on scope exit.
         */
        ~matrix()
        {
            (*this->refcnt_ptr)--;
            if ((*this->refcnt_ptr) == 0) {
                for (int i = 0; i < this->rows(); i++)
                    delete[] this->mtx_ptr[i];
                delete[] this->mtx_ptr;
                delete this->rows_ptr;
                delete this->cols_ptr;
                delete this->refcnt_ptr;
            }
        }

        /**
         * Get an element of the matrix from an index.
         * @param i Row wise position of element
         * @param j Column wise position of element
         * @return <type> The value at index i, j
         * @throws Matrix::Exception Row index out of bounds - EX_ROUTB
         * @throws Matrix::Exception Column index out of bounds - EX_COUTB
         */
        type get(int i, int j)
        {
            if (i < 0 || i > this->rows())
                Matrix::throwException(EX_ROUTB, "row index out of bounds");
            if (j < 0 || j > this->rows())
                Matrix::throwException(EX_COUTB, "column index out of bounds");
            return this->mtx_ptr[i][j];
        }

        /**
         * Set an element of the matrix to an index.
         * @param i Row wise position of element
         * @param j Column wise position of element
         * @param val Value to be set
         * @throws Matrix::Exception Row index out of bounds - EX_ROUTB
         * @throws Matrix::Exception Column index out of bounds - EX_COUTB
         */
        void set(int i, int j, type val)
        {
            if (i < 0 || i > this->rows())
                Matrix::throwException(EX_ROUTB, "row index out of bounds");
            if (j < 0 || j > this->cols())
                Matrix::throwException(EX_COUTB, "column index out of bounds");
            this->mtx_ptr[i][j] = val;
        }

        /**
         * Access a posn of the matrix.
         * @param i Row of matrix
         */
        type*& operator[](int i) const
        {
            return this->mtx_ptr[i];
        }

        /*
         * Compares two matrices for equality.
         * @param m2 The matrix to compare to
         * @return boolean True if equal
         */
        bool equals(const matrix<type>& m2)
        {
            if (this->rows() != m2.rows() || this->cols() != m2.cols())
                return false;
            for (int i = 0; i < this->rows(); i++)
                for (int j = 0; j < this->cols(); j++)
                    if (this->mtx_ptr[i][j] != m2[i][j])
                        return false;
            return true;
        }

        /**
         * Add two compatible matrices.
         * @param m2 The matrix to add
         * @return matrix<type> The matrix of sums
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> add(const matrix<type>& m2, bool sub = false)
        {
            if (m2.rows() != this->rows() || m2.cols() != this->cols())
                Matrix::throwException(EX_INCMP, "incompatible matrices for addition");
            matrix<type> nm = matrix<type>(this->rows(), this->cols());
            for (int i = 0; i < this->rows(); i++)
                for (int j = 0; j < this->cols(); j++) {
                    type rslt = this->mtx_ptr[i][j] + (sub ? (-1) * m2[i][j] : m2[i][j]);
                    nm[i][j] = rslt;
                }
            return nm;
        }

        /**
         * Subtract 2nd from 1st matrix.
         * @param m2 The matrix to subtract
         * @return matrix<type> The matrix of differences
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> subtract(const matrix<type>& m2)
        {
            if (m2.rows() != this->rows() || m2.cols() != this->cols())
                Matrix::throwException(EX_INCMP, "incompatible matrices for subtraction");
            return this->add(m2, true);
        }

        /**
         * Multiply a matrix by a scalar.
         * @param scalar Scalar to multiply by
         * @return matrix The matrix of products
         */
        matrix<type> scale(type scalar)
        {
            matrix<type> nm = matrix<type>(this->rows(), this->cols());
            for (int i = 0; i < this->rows(); i++)
                for (int j = 0; j < this->cols(); j++) {
                    type rslt = scalar * this->mtx_ptr[i][j];
                    nm[i][j] = rslt;
                }
            return nm;
        }

        /**
         * Multiply two compatible matrices.
         * @param m2 The matrix to multiply by
         * @return matrix<type> The matrix after multiplication
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> multiply(const matrix<type>& m2)
        {
            if (this->cols() != m2.rows())
                Matrix::throwException(EX_INCMP, "incompatible matrices for multiplication");
            int m = this->rows();
            int n = this->cols(); // same
            n = m2.rows();           // same
            int o = m2.cols();
            matrix<type> nm = matrix<type>(m, o);
            for (int i = 0; i < m; i++)
                for (int j = 0; j < o; j++) {
                    double sum = 0;
                    for (int k = 0; k < n; k++)
                        sum += this->mtx_ptr[i][k] * m2[k][j];
                    nm[i][j] = sum;
                }
            return nm;
        }

        /**
         * Calculate matrix to the power of +ve integer.
         * @param index Power of matrix
         * @return matrix<type> The resulting matrix
         * @throws Matrix::Exception Same as Exceptions of matrix::multiply method
         */
        matrix<type> power(int index)
        {
            matrix<type> nm = *this;
            for (int i = 0; i < index - 1; i++) {
                matrix<type> tmp = nm.multiply(*this);
                nm = tmp;
            }
            return nm;
        }

        /*
         * Compares two matrices for equality.
         * @param m2 The matrix to compare to
         * @return boolean True if equal
         */
        bool operator==(const matrix<type>& m2)
        {
            return this->equals(m2);
        }

        /**
         * Add two compatible matrices.
         * @param m2 The matrix to add
         * @return matrix<type> The matrix of sums
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> operator+(const matrix<type>& m2)
        {
            return this->add(m2);
        }

        /**
         * Subtract 2nd from 1st matrix.
         * @param m2 The matrix to subtract
         * @return matrix<type> The matrix of differences
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> operator-(const matrix<type>& m2)
        {
            return this->subtract(m2);
        }

        /**
         * Multiply a matrix by a scalar.
         * @param scalar Scalar to multiply by
         * @return matrix The matrix of products
         */
        matrix<type> operator*(type scalar)
        {
            return this->scale(scalar);
        }

        /**
         * Multiply two compatible matrices.
         * @param m2 The matrix to multiply by
         * @return matrix<type> The matrix after multiplication
         * @throws Matrix::Exception If matrices aren't compatible - EX_INCMP
         */
        matrix<type> operator*(const matrix<type>& m2)
        {
            return this->multiply(m2);
        }

        /**
         * Calculate matrix to the power of +ve integer
         * @param index Power of matrix
         * @return matrix<type> The resulting matrix
         * @throws Matrix::Exception Same as Exceptions of matrix::multiply method
         */
        matrix<type> operator^(int index)
        {
            return this->power(index);
        }

        /**
         * Excludes a row and a column and generates a sub matrix.
         * Useful for calculating determinants and cofactor matrices.
         * @param row The row to exclude
         * @param col The column to exclude
         * @return matrix<type> The sub matrix
         * @throws Matrix::Exception Row index out of bounds - EX_ROUTB
         * @throws Matrix::Exception Column index out of bounds - EX_COUTB
         */
        matrix<type> excludeRowCol(int row, int col)
        {
            if (row < 0 || row > this->rows())
                Matrix::throwException(EX_ROUTB, "row index out of bounds");
            if (col < 0 || col > this->rows())
                Matrix::throwException(EX_COUTB, "column index out of bounds");
            matrix<type> subm = matrix<type>(this->rows() - 1, this->cols() - 1);
            bool skipRow = false;
            for (int j = 0; j < this->rows() - 1; j++) {
                bool skipCol = false;
                int jSelf = j;
                if (j == row)
                    skipRow = true;
                if (skipRow)
                    jSelf++;
                for (int k = 0; k < this->cols() - 1; k++) {
                    int kSelf = k;
                    if (k == col)
                        skipCol = true;
                    if (skipCol)
                        kSelf++;
                    subm[j][k] = this->mtx_ptr[jSelf][kSelf];
                }
            }
            return subm;
        }

        /**
         * Calculate determinant of this matrix.
         * @return double The determinant
         * @throw Exception If matrix isn't a square matrix - EX_NOSQR
         */
        double determinant()
        {
            if (this->rows() != this->cols())
                Matrix::throwException(EX_NOSQR, "not a square matrix");
            int n = this->rows();
            double det = 0;
            if (n == 1)
                return this->mtx_ptr[0][0];
            else if (n == 2)
                return this->mtx_ptr[0][0] * this->mtx_ptr[1][1] - this->mtx_ptr[0][1] * this->mtx_ptr[1][0];
            else
                for (int i = 0; i < n; i++) {
                    double coeff = pow(-1, i) * this->mtx_ptr[0][i];
                    matrix<type> subm = this->excludeRowCol(0, i);
                    double subdet = subm.determinant();
                    double term = coeff * subdet;
                    det += term;
                }
            return det;
        }

        /**
         * Calculate the transpose of this matrix.
         * @return matrix<type> The transpose
         */
        matrix<type> transpose()
        {
            matrix<type> nm = matrix<type>(this->cols(), this->rows());
            for (int i = 0; i < this->rows(); i++)
                for (int j = 0; j < this->cols(); j++)
                    nm[j][i] = this->mtx_ptr[i][j];
            return nm;
        }

        /**
         * Calculate the cofactor matrix of this matrix.
         * @return matrix<type> The cofactor matrix
         * @throws Matrix::Exception If matrix isn't a square matrix - EX_NOSQR
         */
        matrix<type> cofactor()
        {
            if (this->rows() != this->cols())
                Matrix::throwException(EX_NOSQR, "not a square matrix");
            matrix<type> nm = matrix<type>(this->rows(), this->cols());
            for (int i = 0; i < this->rows(); i++)
                for (int j = 0; j < this->cols(); j++) {
                    double coeff = pow(-1, i + 1 + j + 1);
                    matrix<type> subm = this->excludeRowCol(i, j);
                    nm[i][j] = coeff * subm.determinant();
                }
            return nm;
        }

        /**
         * Calculate the adjoint of this matrix.
         * @return matrix<type> The adjoint
         * @throws Matrix::Exception If matrix isn't a square matrix - EX_NOSQR
         */
        matrix<type> adjoint()
        {
            if (this->rows() != this->cols())
                Matrix::throwException(EX_NOSQR, "not a square matrix");
            return this->cofactor().transpose();
        }

        /**
         * Calculate the inverse of this matrix.
         * @return matrix<double> The inverse
         * @throws Matrix::Exception If matrix isn't a square matrix - EX_NOSQR
         * @throws Matrix::Exception If determinant is 0 - EX_DETR0
         */
        matrix<double> inverse()
        {
            if (this->rows() != this->cols())
                Matrix::throwException(EX_NOSQR, "not a square matrix");
            double determinant = this->determinant();
            if (determinant == 0)
                Matrix::throwException(EX_DETR0, "determinant is 0");
            return this->toDoubleMatrix().adjoint().scale(1/determinant);
        }

        /**
         * Display the matrix.
         * @param msg? The message to print
         */
        void print(const std::string& msg = "")
        {
            if (msg != "")
                std::cout << msg << "\n";
            for (int i = 0; i < this->rows(); i++) {
                for (int j = 0; j < this->cols(); j++)
                    std::cout << this->mtx_ptr[i][j] << ((j < this->cols() -1)? ", " : "");
                std::cout << "\n";
            }
        }

    private:
        /**
         * Row number of this matrix.
         */
        int *rows_ptr;

        /**
         * Column number of this matrix.
         */
        int *cols_ptr;

        /**
         * Double pointer to matrix data location.
         */
        type **mtx_ptr;

        /**
         * Stores a count of references.
         */
        int *refcnt_ptr;

        /**
         * Default constructor.
         */
        matrix()
            : rows_ptr(nullptr), cols_ptr(nullptr), mtx_ptr(nullptr), refcnt_ptr(nullptr)
        {}
    };

    /**
     * Create a null matrix of given size.
     * @param n Rows of matrix
     * @param cols? Cols of matrix
     * @return matrix<type> A null matrix
     * @throws Matrix::Exception Row index out of bounds - EX_ROUTB
     * @throws Matrix::Exception Column index out of bounds - EX_COUTB
     */
    template <typename type>
    matrix<type> O(int n, int cols = 0)
    {
        if (cols == 0)
            cols = n;
        return matrix<type>(n, cols);
    }

    /**
     * Create a unit matrix of given size.
     * @param n Size of matrix
     * @return matrix<type> A unit matrix
     * @throws Matrix::Exception Row index out of bounds - EX_ROUTB
     * @throws Matrix::Exception Column index out of bounds - EX_COUTB
     */
    template <typename type>
    matrix<type> I(int n)
    {
        matrix<type> im = matrix<type>(n, n);
        for (int i = 0; i < n; i++)
            im[i][i] = 1;
        return im;
    }
}
