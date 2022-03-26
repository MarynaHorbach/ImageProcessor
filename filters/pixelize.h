#pragma once
#include "matrix.h"
#include "base_filter.h"
class Pixelize : public Filter {
public:
    Pixelize(int64_t convol);
    void ApplyFilter(Image* image) override;
    void ApplyMatrix(Image* image);
    ~Pixelize() override = default;

private:
    int64_t convol_;
};