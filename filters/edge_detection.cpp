#include "edge_detection.h"
#include "base_filter.h"
#include "grayscale.h"

EdgeDetection::EdgeDetection(int treshold)
    : edge_matrix_({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), treshold_(treshold) {
}

void EdgeDetection::ApplyFilter(Image* image) {
    auto gs = Grayscale();
    gs.ApplyFilter(image);
    MatrixFilter<int32_t>::ApplyMatrix3(image, edge_matrix_);
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    auto width = image->GetWidth();
    auto height = image->GetHeight();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (pixels[i][j].r > treshold_){
                pixels[i][j].r = 255;
                pixels[i][j].g = 255;
                pixels[i][j].b = 255;
            } else{
                pixels[i][j].r = 0;
                pixels[i][j].g = 0;
                pixels[i][j].b = 0;
            }
        }
    }
    image->pixels = pixels;
}

EdgeDetection::~EdgeDetection() = default;
