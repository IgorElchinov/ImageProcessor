#ifndef SRC_CORE_MATRIX_H
#define SRC_CORE_MATRIX_H

#include <cstddef>
#include <cstdint>
#include <exception>

namespace image_processor {

// Class to represent matrix
class Matrix {
    friend class Row;

public:  // ===== Member types =====
    // TODO class column using m(i)

    // Lightweight wrapper for matrix row
    class Row {
        friend class Matrix;

    public:  // ===== Operators =====
        // Element access
        double& operator[](size_t col_num) {
            return owner_->GetElem(num_, col_num);
        }

        // Constant element access
        double operator[](size_t col_num) const {
            return owner_->GetElem(num_, col_num);
        }

    public:  // ===== Getters =====
        size_t GetSize() const {
            return owner_->GetColumnsCount();
        }

    protected:  // ===== Private constructor =====
        // Matrix row cannot exist without its owner
        Row(size_t num, Matrix* owner) : num_(num), owner_(owner){};

    protected:  // ===== Private members =====
        size_t num_;
        Matrix* owner_;
    };

    // Lightweight wrapper for matrix row (constant version)
    class ConstRow {
        friend class Matrix;

    public:  // ===== Operators =====
        // Constant element access
        double operator[](size_t col_num) const {
            return owner_->GetElem(num_, col_num);
        }

    public:  // ===== Getters =====
        size_t GetSize() const {
            return owner_->GetColumnsCount();
        }

    protected:  // ===== Private constructor =====
        // Matrix row cannot exist without its owner
        ConstRow(size_t num, const Matrix* owner) : num_(num), owner_(owner){};

    protected:  // ===== Private members =====
        size_t num_;
        const Matrix* owner_;
    };

public:  // ===== Constructors & destructor =====
    Matrix() : Matrix(0, 0) {
    }

    // TODO: copy & test
    Matrix(const Matrix& other)
        : rows_count_(other.rows_count_),
          columns_count_(other.columns_count_),
          data_ptr_(other.data_ptr_ ? new double[other.rows_count_ * other.columns_count_] : nullptr) {
        // .. logic
    }

    // Initializes new matrix with `rows` rows and `columns` columns
    // `rows` and `columns` can be both zeros ar non-zeros, `std::invalid_argument` is thrown otherwise
    Matrix(size_t rows, size_t columns);

    // Initializes new matrix with `rows` rows and `columns` columns and fills it with `val`
    // `rows` and `columns` can be both zeros ar non-zeros, `std::invalid_argument` is thrown otherwise
    Matrix(size_t rows, size_t columns, double val);

    // TODO: logic & test
    Matrix& operator=(const Matrix& rhv) {
        if (this == &rhv) {
            return *this;
        }
        // ... logic
        return *this;
    }

    ~Matrix() {
        delete[] data_ptr_;
    }

public:  // ===== Operators =====
    // Returns matrix row
    Row operator[](size_t row) {
        return Row(row, this);
    }

    // Returns constant matrix row
    ConstRow operator[](size_t row) const {
        return ConstRow(row, this);
    }

public:  // ===== Common member functions =====
    // Returns element. `std::invalid_argument` is thrown when either `row` or `col` is too large
    double& At(size_t row, size_t col);

    // Returns element. `std::invalid_argument` is thrown when either `row` or `col` is too large
    double At(size_t row, size_t col) const;

public:  // ===== Getters =====
    size_t GetRowsCount() const {
        return rows_count_;
    }
    size_t GetColumnsCount() const {
        return columns_count_;
    }

    const double* GetDataPointer() const {
        return data_ptr_;
    }

public:  // ===== Static member functions =====
    size_t GetInstanceCount() {
        return instance_count;
    }

protected:  // ===== Private member functions =====
    // Allocates memory for `rows` x `columns` elelments
    void Allocate(size_t rows, size_t columns) {
        data_ptr_ = new double[rows * columns];
    }

    // Returns element without checking boundaries
    double& GetElem(size_t row, size_t col) {
        return data_ptr_[row * columns_count_ + col];
    }

    // Returns element without checking boundaries
    double GetElem(size_t row, size_t col) const {
        return data_ptr_[row * columns_count_ + col];
    }

protected:  // ===== Private members =====
    size_t rows_count_;
    size_t columns_count_;
    double* data_ptr_;

    static size_t instance_count;  // Relict
};

}  // namespace image_processor

#endif  // SRC_CORE_MATRIX_H
