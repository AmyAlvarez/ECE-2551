// ECE 2551 - Homework #1 Matrix Class by Amy Alvarez :^) 

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

// Enum for status reporting
enum Status {
    NoError,
    DimensionMismatch,
    DivideByZero,
    NotSquareMatrix
};

// Matrix class definition
class Matrix {
private:
    std::vector<std::vector<double>> data; // Stores matrix data

public:
    // Constructors
    Matrix(const std::vector<std::vector<double>>& data);
    Matrix();

    // Getters for matrix size and elements
    size_t getRowSize() const;
    size_t getColSize() const;
    double getAt(size_t row, size_t col) const;

    // Basic matrix operations
    Status add(const Matrix& other);
    Status subtract(const Matrix& other);
    Status multiply(const Matrix& other);
    Status divide(double scalar);
    void multiply1(double scalar);
    void transpose();
    void zero();
    
    // Other matrix functions
    bool isSquare() const;
    bool hasSameDimensionAs(const Matrix& other) const;
    double getDeterminant() const;
    Matrix getMinor(size_t rowToExclude, size_t colToExclude) const;
};

class HelpingFunctions {
public:
    static double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2);
};

#endif // MATRIX_H
