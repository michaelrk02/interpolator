#pragma once

#include <cstring>
#include <stdexcept>

template <typename _Type>
class Array2D {
public:
    Array2D(void);
    ~Array2D(void);

    void initialize(unsigned int rows, unsigned int cols);
    void destroy(void);

    _Type &at(unsigned int i, unsigned int j);
    const _Type &at(unsigned int i, unsigned int j) const;

    _Type *getData(void);
    const _Type *getData(void) const;

    bool isInitialized(void) const;
    unsigned int getRows(void) const;
    unsigned int getCols(void) const;

private:
    _Type *data;
    unsigned int rows;
    unsigned int cols;
};

template <typename _Type>
Array2D<_Type>::Array2D(void) {
    this->data = NULL;
    this->rows = 0;
    this->cols = 0;
}

template <typename _Type>
Array2D<_Type>::~Array2D(void) {
    this->destroy();
}

template <typename _Type>
void Array2D<_Type>::initialize(unsigned int rows, unsigned int cols) {
    if (this->data == NULL) {
        this->data = new _Type[rows * cols];
        if (this->data != NULL) {
            std::memset(this->data, 0, rows * cols * sizeof(_Type));
            this->rows = rows;
            this->cols = cols;
        } else {
            throw std::runtime_error("cannot initialize 2D array: out of memory");
        }
    } else {
        throw std::logic_error("array was already initialized");
    }
}

template <typename _Type>
void Array2D<_Type>::destroy(void) {
    if (this->data != NULL) {
        delete[] this->data;
        this->rows = 0;
        this->cols = 0;
    }
}

template <typename _Type>
_Type &Array2D<_Type>::at(unsigned int i, unsigned int j) {
    if (this->data == NULL) {
        throw std::logic_error("array was not initialized");
    }
    if ((i >= this->rows) || (j >= this->cols)) {
        throw std::out_of_range("cannot access 2D array element: out of range");
    }
    return this->data[i * this->cols + j];
}

template <typename _Type>
const _Type &Array2D<_Type>::at(unsigned int i, unsigned int j) const {
    if (this->data == NULL) {
        throw std::logic_error("array was not initialized");
    }
    if ((i >= this->rows) || (j >= this->cols)) {
        throw std::out_of_range("cannot access 2D array element: out of range");
    }
    return this->data[i * this->cols + j];
}

template <typename _Type>
_Type *Array2D<_Type>::getData(void) {
    return this->data;
}

template <typename _Type>
const _Type *Array2D<_Type>::getData(void) const {
    return this->data;
}

template <typename _Type>
bool Array2D<_Type>::isInitialized(void) const {
    return this->data != NULL;
}

template <typename _Type>
unsigned int Array2D<_Type>::getRows(void) const {
    return this->rows;
}

template <typename _Type>
unsigned int Array2D<_Type>::getCols(void) const {
    return this->cols;
}

