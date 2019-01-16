#include "Matrix.h"

Matrix::Matrix(vector<vector<int>> matrix) {
    this->matrix = matrix;
    rows = matrix.size();
    cols = matrix[0].size();
}

bool Matrix::isValid(int row, int col) {
    return (row >= 0)&&(row < rows)&&(col >= 0)&&(col < cols);
}

bool Matrix::isUnBlocked(int row, int col) {
    return (matrix[row][col] != -1);
}

vector<vector<int>> Matrix::getArea() {
    return matrix;
}

pair<int, int> Matrix::getSize() {
    return {rows, cols};
}
