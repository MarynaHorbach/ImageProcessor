#pragma once

#include "../image.h"
#include "matrix.h"

#include <vector>
#include <string>
#include <memory>

#include <iostream>

class Filter {
public:
    Filter();
    virtual void ApplyFilter(Image* image) = 0;
    virtual ~Filter();
};


template <typename num>
class MatrixFilter : public Filter {
public:
    MatrixFilter() = default;
    virtual void ApplyFilter(Image* image) override = 0;
    static void ApplyMatrix3(Image* image, Matrix<num>& matrix) {
        std::vector<std::vector<Pixel>>& pixels = image->pixels;
        int64_t width = image->GetWidth();
        int64_t height = image->GetHeight();
        std::vector<std::vector<Pixel>> new_pixels;
        if (width < 1 || height < 1) {
            throw(std::invalid_argument("Image is smaller than crop"));
        }
        int red = 0;
        int green = 0;
        int blue = 0;
        for (int64_t i = 0; i < height; ++i) {
            new_pixels.push_back(std::vector<Pixel>(width));
            for (int64_t j = 0; j < width; ++j) {
                red = 0;
                green = 0;
                blue = 0;
                std::vector<std::pair<int64_t, int64_t>> for_matrix = {{-1, 0}, {1, 0}, {0, 0}, {0, -1}, {0, 1}};
                for (auto& [x, y] : for_matrix) {
                    int64_t x1 = std::clamp(i + x, static_cast<int64_t>(0), height - 1);
                    int64_t y1 = std::clamp(j + y, static_cast<int64_t>(0), width - 1);
                    red += matrix[x + 1][y + 1] * int(pixels[x1][y1].red);
                    green += matrix[x + 1][y + 1] * int(pixels[x1][y1].green);
                    blue += matrix[x + 1][y + 1] * int(pixels[x1][y1].blue);
                }
                new_pixels[i][j].red = std::min(255, std::max(0, red));
                new_pixels[i][j].green = std::min(255, std::max(0, green));
                new_pixels[i][j].blue = std::min(255, std::max(0, blue));
            }
        }
        image->pixels = new_pixels;
    };
};