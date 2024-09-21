// ECE 2551 - Homework #1 Matrix Class by Amy Alvarez :)

#include "matrix.h"

// Constructor with data
Matrix::Matrix(const std::vector<std::vector<double>>& data) : data(data) {}

// Default constructor
Matrix::Matrix() = default;

// Get the number of rows
size_t Matrix::getRowSize() const {
    return data.size();
}

// Get the number of columns
size_t Matrix::getColSize() const {
    return data.empty() ? 0 : data[0].size();
}

// Get element at (row, col)
double Matrix::getAt(size_t row, size_t col) const {
    return data[row][col];
}

// Add another matrix
Status Matrix::add(const Matrix& other) {
    if (getRowSize() != other.getRowSize() || getColSize() != other.getColSize()) {
        return DimensionMismatch;
    }
    for (size_t i = 0; i < getRowSize(); i++) {
        for (size_t j = 0; j < getColSize(); j++) {
            data[i][j] += other.data[i][j];
        }
    }
    return NoError;
}

// Subtract another matrix
Status Matrix::subtract(const Matrix& other) {
    if (getRowSize() != other.getRowSize() || getColSize() != other.getColSize()) {
        return DimensionMismatch;
    }
    for (size_t i = 0; i < getRowSize(); i++) {
        for (size_t j = 0; j < getColSize(); j++) {
            data[i][j] -= other.data[i][j];
        }
    }
    return NoError;
}

// Multiply by another matrix
Status Matrix::multiply(const Matrix& other) {
    if (getColSize() != other.getRowSize()) {
        return DimensionMismatch;
    }
    std::vector<std::vector<double>> result(getRowSize(), std::vector<double>(other.getColSize(), 0));
    for (size_t i = 0; i < getRowSize(); i++) {
        for (size_t j = 0; j < other.getColSize(); j++) {
            for (size_t k = 0; k < getColSize(); k++) {
                result[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    data = result;
    return NoError;
}

// Divide by scalar
Status Matrix::divide(double scalar) {
    if (scalar == 0) {
        return DivideByZero;
    }
    for (auto& row : data) {
        for (auto& elem : row) {
            elem /= scalar;
        }
    }
    return NoError;
}

// Multiply by scalar
void Matrix::multiply1(double scalar) {
    for (auto& row : data) {
        for (auto& elem : row) {
            elem *= scalar;
        }
    }
}

// Transpose matrix
void Matrix::transpose() {
    std::vector<std::vector<double>> result(getColSize(), std::vector<double>(getRowSize()));
    for (size_t i = 0; i < getRowSize(); i++) {
        for (size_t j = 0; j < getColSize(); j++) {
            result[j][i] = data[i][j];
        }
    }
    data = result;
}

// Set all elements to zero
void Matrix::zero() {
    for (auto& row : data) {
        std::fill(row.begin(), row.end(), 0);
    }
}

// Check if matrix is square
bool Matrix::isSquare() const {
    return getRowSize() == getColSize();
}

// Check if two matrices have the same dimensions
bool Matrix::hasSameDimensionAs(const Matrix& other) const {
    return getRowSize() == other.getRowSize() && getColSize() == other.getColSize();
}

// Get determinant (only for square matrices)
double Matrix::getDeterminant() const {
    if (!isSquare()) {
        throw std::runtime_error("Not a square matrix :(");
    }
    if (getRowSize() == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    double determinant = 0;
    for (size_t i = 0; i < getColSize(); i++) {
        Matrix minor = getMinor(0, i);
        determinant += (i % 2 == 0 ? 1 : -1) * data[0][i] * minor.getDeterminant();
    }
    return determinant;
}

// Get minor matrix
Matrix Matrix::getMinor(size_t rowToExclude, size_t colToExclude) const {
    std::vector<std::vector<double>> result;
    for (size_t i = 0; i < getRowSize(); i++) {
        if (i == rowToExclude) continue;
        std::vector<double> row;
        for (size_t j = 0; j < getColSize(); j++) {
            if (j == colToExclude) continue;
            row.push_back(data[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

// Dot product of two vectors
double HelpingFunctions::dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Vectors must be same size");
    }
    double result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}
