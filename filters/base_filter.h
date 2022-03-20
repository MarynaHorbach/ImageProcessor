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
        size_t width = image->GetWidth();
        size_t height = image->GetHeight();
        std::vector<std::vector<Pixel>> new_pixels = image->pixels;
        if (width < 1 || height < 1) {
            throw(std::invalid_argument("Image is smaller than crop"));
        }
        int r = 0;
        int g = 0;
        int b = 0;
        r += (matrix[0][0] * pixels[0][0].r + matrix[0][1] * pixels[0][1].r + matrix[0][2] * pixels[0][2].r +
              matrix[1][0] * pixels[0][0].r + matrix[1][1] * pixels[0][0].r + matrix[1][2] * pixels[0][1].r +
              matrix[2][0] * pixels[1][0].r + matrix[2][1] * pixels[1][0].r + matrix[2][2] * pixels[1][1].r);
        g += (matrix[0][0] * pixels[0][0].g + matrix[0][1] * pixels[0][1].g + matrix[0][2] * pixels[0][2].g +
              matrix[1][0] * pixels[0][0].g + matrix[1][1] * pixels[0][0].g + matrix[1][2] * pixels[0][1].g +
              matrix[2][0] * pixels[1][0].g + matrix[2][1] * pixels[1][0].g + matrix[2][2] * pixels[1][1].g);
        b += (matrix[0][0] * pixels[0][0].b + matrix[0][1] * pixels[0][1].b + matrix[0][2] * pixels[0][2].b +
              matrix[1][0] * pixels[0][0].b + matrix[1][1] * pixels[0][0].b + matrix[1][2] * pixels[0][1].b +
              matrix[2][0] * pixels[1][0].b + matrix[2][1] * pixels[1][0].b + matrix[2][2] * pixels[1][1].b);
        new_pixels[0][0].r = r;
        new_pixels[0][0].g = g;
        new_pixels[0][0].b = b;
        for (int64_t j = 1; j < width - 1; ++j) {
            r = 0;
            g = 0;
            b = 0;
            r += matrix[0][0] * pixels[0][j - 1].r + matrix[0][1] * pixels[0][j].r + matrix[0][2] * pixels[0][j + 1].r;
            g += matrix[0][0] * pixels[0][j - 1].g + matrix[0][1] * pixels[0][j].g + matrix[0][2] * pixels[0][j + 1].g;
            b += matrix[0][0] * pixels[0][j - 1].b + matrix[0][1] * pixels[0][j].b + matrix[0][2] * pixels[0][j + 1].b;
            for (int x = 0; x < 2; ++x) {
                for (int y = -1; y < 2; ++y) {
                    r += matrix[x + 1][y + 1] * int(pixels[x][j + y].r);
                    g += matrix[x + 1][y + 1] * int(pixels[x][j + y].g);
                    b += matrix[x + 1][y + 1] * int(pixels[x][j + y].b);
                }
            }
            new_pixels[0][j].r = std::min(255, std::max(0, r));
            new_pixels[0][j].g = std::min(255, std::max(0, g));
            new_pixels[0][j].b = std::min(255, std::max(0, b));
        }
        r = 0;
        g = 0;
        b = 0;
        size_t w = width-1;
        r += (matrix[0][0] * pixels[0][w-1].r + matrix[0][1] * pixels[0][w].r + matrix[0][2] * pixels[0][w].r +
              matrix[1][0] * pixels[0][w-1].r + matrix[1][1] * pixels[0][w].r + matrix[1][2] * pixels[0][w].r +
              matrix[2][0] * pixels[1][w-1].r + matrix[2][1] * pixels[1][w].r + matrix[2][2] * pixels[1][w].r);
        g += (matrix[0][0] * pixels[0][w-1].g + matrix[0][1] * pixels[0][w].g + matrix[0][2] * pixels[0][w].g +
              matrix[1][0] * pixels[0][w-1].g + matrix[1][1] * pixels[0][w].g + matrix[1][2] * pixels[0][w].g +
              matrix[2][0] * pixels[1][w-1].g + matrix[2][1] * pixels[1][w].g + matrix[2][2] * pixels[1][w].g);
        b += (matrix[0][0] * pixels[0][w-1].b + matrix[0][1] * pixels[0][w].b + matrix[0][2] * pixels[0][w].b +
              matrix[1][0] * pixels[0][w-1].b + matrix[1][1] * pixels[0][w].b + matrix[1][2] * pixels[0][w].b +
              matrix[2][0] * pixels[1][w-1].b + matrix[2][1] * pixels[1][w].b + matrix[2][2] * pixels[1][w].b);
        new_pixels[0][w].r = r;
        new_pixels[0][w].g = g;
        new_pixels[0][w].b = b;
        pixels.push_back(pixels[0]);
        for (int64_t i = 1; i < height; ++i) {
            r = 0;
            g = 0;
            b = 0;
            r += matrix[0][0] * pixels[i - 1][0].r + matrix[0][1] * pixels[i][0].r + matrix[0][2] * pixels[i + 1][0].r;
            g += matrix[1][0] * pixels[i - 1][0].g + matrix[0][1] * pixels[i][0].g + matrix[0][2] * pixels[i + 1][0].g;
            b += matrix[2][0] * pixels[i - 1][0].b + matrix[0][1] * pixels[i][0].b + matrix[0][2] * pixels[i + 1][0].b;
            for (int x = -1; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    r += matrix[x + 1][y + 1] * int(pixels[x][i + y].r);
                    g += matrix[x + 1][y + 1] * int(pixels[x][i + y].g);
                    b += matrix[x + 1][y + 1] * int(pixels[x][i + y].b);
                }
            }
            new_pixels[i][0].r = std::min(255, std::max(0, r));
            new_pixels[i][0].g = std::min(255, std::max(0, g));
            new_pixels[i][0].b = std::min(255, std::max(0, b));
            for (int64_t j = 1; j < width - 1; ++j) {
                r = 0;
                g = 0;
                b = 0;
                for (int x = -1; x < 2; ++x) {
                    for (int y = -1; y < 2; ++y) {
                        r += matrix[x + 1][y + 1] * int(pixels[i + x][j + y].r);
                        g += matrix[x + 1][y + 1] * int(pixels[i + x][j + y].g);
                        b += matrix[x + 1][y + 1] * int(pixels[i + x][j + y].b);
                    }
                }
                new_pixels[i][j].r = std::min(255, std::max(0, r));
                new_pixels[i][j].g = std::min(255, std::max(0, g));
                new_pixels[i][j].b = std::min(255, std::max(0, b));
            }
        }
        new_pixels.pop_back();
        image->pixels = new_pixels;
    };
};