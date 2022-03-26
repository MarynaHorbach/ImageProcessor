#pragma once
#include "matrix.h"
#include "base_filter.h"
class Sharpening : public MatrixFilter<int> {
public:
    Sharpening();
    void ApplyFilter(Image* image) override;
    ~Sharpening() override;

private:
    Matrix<int32_t> sharp_matrix_;
};