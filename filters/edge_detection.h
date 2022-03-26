#pragma once
#include "matrix.h"
#include "base_filter.h"
class EdgeDetection : public MatrixFilter<int> {
public:
    EdgeDetection(double treshold);
    void ApplyFilter(Image* image) override;
    ~EdgeDetection() override;

private:
    Matrix<int32_t> edge_matrix_;

    double treshold_;
};