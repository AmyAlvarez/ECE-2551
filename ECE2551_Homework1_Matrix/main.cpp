// ECE 2551 - Homework #1 Matrix Class by Amy Alvarez :^)

#include "matrix.h"
#include <cmath>  // For std::abs

// Simple check function to print test results
void check(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << testName << " passed!" << std::endl;
    } else {
        std::cout << testName << " failed!" << std::endl;
    }
}

//My test functions here

//Constructor Test
void Constructor() {
    Matrix m1;
    check(m1.getRowSize() == 0 && m1.getColSize() == 0, "Test 1: Default Constructor");
}

//Matrix Test
void matrix_test() {
    std::vector<std::vector<double>> data = {{1, 2}, {4, 5}};
    Matrix m2 = Matrix(data);
    check(m2.getRowSize() == 2 && m2.getColSize() == 2, "Test 2: Rows and Columns are two");
}

//Add Test
void add_test() {
    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<double>> data1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    Matrix one = Matrix(data);
    Matrix two = Matrix(data1);
    
    std::vector<std::vector<double>> Result = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix CorrectResult = Matrix(Result);
    Status returnValue = one.add(two);
    
    if (returnValue == NoError) {
        bool correct = true;
        for (size_t row = 0; row < one.getRowSize(); row++) {
            for (size_t col = 0; col < one.getColSize(); col++) {
                if (one.getAt(row, col) != CorrectResult.getAt(row, col)) {
                    correct = false;
                    break;
                }
            }
        }
        check(correct, "Test 3: Result of Addition");
    } else {
        std::cout << "Matrix Addition is not Successful: " << returnValue << std::endl;
    }
}

//Subtraction Test
void subtract_test() {
    std::vector<std::vector<double>> data = {{4, 6, 9}, {10, 12, 13}, {1, 2, 3}};
    std::vector<std::vector<double>> data1 = {{1, 2, 3}, {4, 6, 9}, {1, 2, 3}};

    Matrix m1 = Matrix(data);
    Matrix m2 = Matrix(data1);

    std::vector<std::vector<double>> Result = {{3, 4, 6}, {6, 6, 4}, {0, 0, 0}};
    Matrix CorrectResult = Matrix(Result);
    Status returnValue = m1.subtract(m2);
    if (returnValue == NoError) {
        bool correct = true;
        for (size_t row = 0; row < m1.getRowSize(); row++) {
            for (size_t col = 0; col < m1.getColSize(); col++) {
                if (m1.getAt(row, col) != CorrectResult.getAt(row, col)) {
                    correct = false;
                    break;
                }
            }
        }
        check(correct, "Test 4: Result of Subtraction");
    } else {
        std::cout << "Matrix Subtraction is not Successful: " << returnValue << std::endl;
    }
}

//Multiplication Test
void multiply_test() {
    std::vector<std::vector<double>> data = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> data1 = {{4, 5}, {6, 7}};

    Matrix m1 = Matrix(data);
    Matrix m2 = Matrix(data1);

    std::vector<std::vector<double>> expected = {{16, 19}, {36, 43}};
    Matrix expectedResult = Matrix(expected);
    
    Status returnValue = m1.multiply(m2);
    if (returnValue == NoError) {
        bool correct = true;
        for (size_t row = 0; row < m1.getRowSize(); row++) {
            for (size_t col = 0; col < m1.getColSize(); col++) {
                if (std::abs(m1.getAt(row, col) - expectedResult.getAt(row, col)) > 1e-6) {
                    correct = false;
                    break;
                }
            }
        }
        check(correct, "Test 5: Matrix Multiplication");
    } else {
        std::cout << "Matrix Multiplication failed with error code: " << returnValue << std::endl;
    }
}

//Divide Test
void divide_test() {
    std::vector<std::vector<double>> data = {{2, 4}, {6, 8}};
    double scalar = 2.0;
    Matrix m1 = Matrix(data);

    std::vector<std::vector<double>> expected = {{1, 2}, {3, 4}};
    Matrix expectedResult = Matrix(expected);

    Status returnValue = m1.divide(scalar);
    if (returnValue == NoError) {
        bool correct = true;
        for (size_t row = 0; row < m1.getRowSize(); row++) {
            for (size_t col = 0; col < m1.getColSize(); col++) {
                if (std::abs(m1.getAt(row, col) - expectedResult.getAt(row, col)) > 1e-6) {
                    correct = false;
                    break;
                }
            }
        }
        check(correct, "Test 6: Matrix Division by Scalar");
    } else {
        std::cout << "Matrix Division failed with error code: " << returnValue << std::endl;
    }
}

//Multiplyscalar test
void multiplyscalar_test() {
    std::vector<std::vector<double>> data = {{1, 2}, {4, 4.5}};
    Matrix m1 = Matrix(data);
    double scalar = 2.0;

    std::vector<std::vector<double>> expected = {{2, 4}, {8, 9}};
    Matrix expectedResult = Matrix(expected);

    m1.multiply1(scalar);
    
    bool correct = true;
    for (size_t row = 0; row < m1.getRowSize(); row++) {
        for (size_t col = 0; col < m1.getColSize(); col++) {
            if (std::abs(m1.getAt(row, col) - expectedResult.getAt(row, col)) > 1e-6) {
                correct = false;
                break;
            }
        }
    }
    check(correct, "Test 7: Matrix Multiplication by Scalar");
}

//Transpose Test
void transpose_test() {
    std::vector<std::vector<double>> data = {{2, 4, 6}, {8, 9, 10}, {4, 7, 1}};
    Matrix m1 = Matrix(data);

    std::vector<std::vector<double>> expected = {{2, 8, 4}, {4, 9, 7}, {6, 10, 1}};
    Matrix expectedResult = Matrix(expected);

    m1.transpose();

    bool correct = true;
    for (size_t row = 0; row < m1.getRowSize(); row++) {
        for (size_t col = 0; col < m1.getColSize(); col++) {
            if (std::abs(m1.getAt(row, col) - expectedResult.getAt(row, col)) > 1e-6) {
                correct = false;
                break;
            }
        }
    }
    check(correct, "Test 8: Matrix Transposition");
}

//Zeroing Test
void zero_test() {
    std::vector<std::vector<double>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = Matrix(data);

    m1.zero();

    bool correct = true;
    for (size_t row = 0; row < m1.getRowSize(); row++) {
        for (size_t col = 0; col < m1.getColSize(); col++) {
            if (m1.getAt(row, col) != 0) {
                correct = false;
                break;
            }
        }
    }
    check(correct, "Test 9: Zeroing Matrix");
}

//Square Matrix Test
void isSquare_test() {
    std::vector<std::vector<double>> data = {{1, 2}, {4, 5}};
    Matrix m1 = Matrix(data);

    bool result = m1.isSquare();
    check(result, "Test 10: Matrix is Square");

    std::vector<std::vector<double>> nonSquareData = {{1, 2, 3}, {4, 5, 6}};
    Matrix m2 = Matrix(nonSquareData);

    result = m2.isSquare();
    check(!result, "Test 11: Matrix is not Square");
}

//Matrix Dimensions Test
void hasSameDimensionAs_test() {
    std::vector<std::vector<double>> data1 = {{1, 2}, {3, 4}};
    Matrix m1 = Matrix(data1);

    std::vector<std::vector<double>> data2 = {{5, 6}, {7, 8}};
    Matrix m2 = Matrix(data2);

    bool result = m1.hasSameDimensionAs(m2);
    check(result, "Test 12: Matrices have same dimensions");

    std::vector<std::vector<double>> data3 = {{1, 2, 3}, {4, 5, 6}};
    Matrix m3 = Matrix(data3);

    result = m1.hasSameDimensionAs(m3);
    check(!result, "Test 13: Matrices do not have same dimensions");
}

//Determinant Test
void getDeterminant_test() {
    std::vector<std::vector<double>> data = {{6, 1, 1}, {4, -2, 5}, {2, 8, 7}};
    Matrix m1 = Matrix(data);

    double expected = -306.0;
    double result = m1.getDeterminant();

    check(std::abs(result - expected) < 1e-6, "Test 14: Determinant of Matrix");
}

//Minor Test
void getMinor_test() {
    std::vector<std::vector<double>> data = {{1, 0, 2, -1}, {0, 1, 0, -1}, {0, 0, -6, 8}, {0, 0, 0, 5}};
    Matrix m1 = Matrix(data);

    std::vector<std::vector<double>> expected = {{1, 0, -1}, {0, 1, -1}, {0, 0, 5}};
    Matrix expectedResult = Matrix(expected);

    Matrix result = m1.getMinor(2, 2);

    bool correct = true;
    for (size_t row = 0; row < result.getRowSize(); row++) {
        for (size_t col = 0; col < result.getColSize(); col++) {
            if (result.getAt(row, col) != expectedResult.getAt(row, col)) {
                correct = false;
                break;
            }
        }
    }
    check(correct, "Test 15: Minor of Matrix");
}

//Get At Test
void getAt_test() {
    std::vector<std::vector<double>> data = {{1, -1}, {2, 3}};
    Matrix m1 = Matrix(data);

    double expected = 3.0;
    double result = m1.getAt(1, 1);  // Element at position (1, 1)

    check(result == expected, "Test 16: Get At");
}

//Dot Product Test
void dotProduct_test() {
    std::vector<double> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {9, 8, 7};

    double expected = 46.0;
    double result = HelpingFunctions::dotProduct(vec1, vec2);

    check(result == expected, "Test 17: Dot Product of Vectors");
}


int main() {
    Constructor();  
    matrix_test();
    add_test();
    subtract_test();
    multiply_test();
    divide_test();
    multiplyscalar_test();
    transpose_test();
    zero_test();
    isSquare_test();
    hasSameDimensionAs_test();
    getDeterminant_test();
    getMinor_test();
    getAt_test();
    dotProduct_test();
    
    return 0;
}

