#ifndef _MATRIX_H
#define _MATRIX_H
#include "interface.h"

class Matrix : public Searchable {

    vector<vector<int>> matrix;
    int rows;
    int cols;

    public:
        Matrix(vector<vector<int>> matrix);
        bool isValid(int row, int col);
        bool isUnBlocked(int row, int col);
        vector<vector<int>> getArea();
        pair<int, int> getSize();
};

#endif // _MATRIX_H
