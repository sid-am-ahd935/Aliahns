// firstly, download the libmatrix.hpp file

#include <iostream>
#include "libmatrix.hpp"

int main()
{
    using namespace std;        // standard namespace
    using namespace mtx;        // namespace for this library

    // 4x4 unit matrix
    Matrix<double> im = Matrix<double>::I(4);

    // 4x4 matrix as C++ DDA
    double m2arr[4][4] = {
        { 0, 2, 3, 4 },
        { 7, 1, 5, 6 },
        { 6, 5, 2, 7 },
        { 4, 3, 2, 3 }
    };

    // the constructor accepts address to 1st element of the C++ DDA
    Matrix<double> m2 = Matrix<double>(4, 4, &m2arr[0][0]);

    cout << "\nResult = ";
    if (m2 == im) cout << "equal\n";
    else cout << "unequal\n";

    try {
        Matrix<double> im = Matrix<double>::I(2);
        Matrix<double> sum = m2 + im;
    } catch (mtx::Exception error) {
        if (error == E_INCMP)
            cout << "incompatible matrices!\n";
    }
    try {
        Matrix<double> sum = m2 + im;
        sum.print();
    } catch (mtx::Exception error) {
        if (error == E_INCMP)
            cout << "incompatible matrices!\n";
    }

    cout << "\ninverse of matrix:\n";
    try {
        m2.inverse().print();
    } catch (mtx::Exception error) {
        if (error == E_DETR0)
            cout << "can't invert, determinant = 0!\n";
    }
    return 0;
}
