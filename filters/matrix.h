#pragma once

#include <vector>

template<typename num>
class Matrix{
public:
    Matrix(std::vector<std::vector<num>> matrix):matrix_(matrix){
        height_ = matrix_.size();
        width_ = matrix[0].size();
    }

    std::vector<num> operator[](size_t pos){
        return matrix_[pos];
    }

   void push_back(std::vector<num> x){ //NOLINT
        matrix_.push_back(x);
    }

    ~Matrix() = default;

private:
    std::vector<std::vector<num>> matrix_;
    size_t height_;
    size_t width_;
};