#include "matrix.h"

#include <stdexcept>

size_t image_processor::Matrix::instance_count = 0;

double& image_processor::Matrix::At(size_t row, size_t col) {
    if (row >= GetRowsCount() || col >= GetColumnsCount()) {
        throw std::out_of_range("Either row or column is out of range.");
    }
    return GetElem(row, col);
}

double image_processor::Matrix::At(size_t row, size_t col) const {
    if (row >= GetRowsCount() || col >= GetColumnsCount()) {
        throw std::out_of_range("Either row or column is out of range.");
    }
    return GetElem(row, col);
}

image_processor::Matrix::Matrix(size_t rows, size_t columns)
    : rows_count_(rows), columns_count_(columns), data_ptr_(nullptr) {
    ++instance_count;
    if (rows == 0 && columns == 0) {
        return;
    }
    if (rows == 0 || columns == 0) {
        throw std::invalid_argument("Matrix can be either zeros or non-zeros.");
    }
    Allocate(rows, columns);
}

image_processor::Matrix::Matrix(size_t rows, size_t columns, double def) : Matrix(rows, columns) {
    for (size_t x = 0; x < rows; ++x) {
        for (size_t y = 0; y < columns; ++y) {
            GetElem(x, y) = def;
        }
    }
}