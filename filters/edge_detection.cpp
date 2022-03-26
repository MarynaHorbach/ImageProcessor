#include "edge_detection.h"
#include "base_filter.h"
#include "grayscale.h"
#include "../exception.cpp"
#include <cmath>

EdgeDetection::EdgeDetection(double treshold)
    : edge_matrix_({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), treshold_(255 * treshold) {
    if (treshold < 0 || treshold > 1) {
        throw WrongArgumentsException(
            "Wrong format of arguments for Edge Detection filter: treshold (from [0,1] were expected): " +
            std::to_string(treshold) + " was given.");
    }
}

void EdgeDetection::ApplyFilter(Image* image) {
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    MatrixFilter<int32_t>::ApplyMatrix3(image, edge_matrix_);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            double new_colour = 0.299 * static_cast<double>(pixels[i][j].red) +
                                0.587 * static_cast<double>(pixels[i][j].green) +
                                0.114 * static_cast<double>(pixels[i][j].blue);
            if (new_colour > treshold_) {
                pixels[i][j].red = 255;
                pixels[i][j].green = 255;
                pixels[i][j].blue = 255;
            } else {
                pixels[i][j].red = 0;
                pixels[i][j].green = 0;
                pixels[i][j].blue = 0;
            }
        }
    }
}

EdgeDetection::~EdgeDetection() = default;
