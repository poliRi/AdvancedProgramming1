#include "Matrix.h"

//represents a matrix graph
Matrix::Matrix(vector<vector<int>> matrix) {
    this->matrix = matrix;
    rows = matrix.size();
    cols = matrix[0].size();
}

//if the current point is in a valid border
bool Matrix::isValid(int row, int col) {
    return (row >= 0)&&(row < rows)&&(col >= 0)&&(col < cols);
}

// if is unblocked
bool Matrix::isUnBlocked(int row, int col) {
    return (matrix[row][col] != -1);
}

//returns the matrix graph
vector<vector<int>> Matrix::getArea() {
    return matrix;
}

//returns dimensions
pair<int, int> Matrix::getSize() {
    return {rows, cols};
}
