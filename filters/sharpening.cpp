#include "sharpening.h"
#include "base_filter.h"

Sharpening::Sharpening() : sharp_matrix_({{0,-1,0},{-1,5,-1},{0,-1,0}}) {
}

void Sharpening::ApplyFilter(Image* image) {
    MatrixFilter<int32_t>::ApplyMatrix3(image, sharp_matrix_);
}

Sharpening::~Sharpening()=default;