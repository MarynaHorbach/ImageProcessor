#include "blur.h"
#include "base_filter.h"

#include <math.h>

struct DoublePixel {
    double r;
    double g;
    double b;
};

Blur::Blur(double sigma) : sq_sigma_(sigma * sigma) {
}

void Blur::ApplyFilter(Image* image) {
    auto pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();

    auto double_pixels = std::vector<std::vector<DoublePixel>>();
    double constant = std::pow(1 / (2 * M_PI * sq_sigma_), 1 / 2);
    for (int64_t i = 0; i < height; ++i) {
        double_pixels.push_back(std::vector<DoublePixel>(width));
        for (int64_t j = 0; j < width; ++j) {
            auto new_pixel = DoublePixel{0, 0, 0};
            for (int64_t k = 0; k < width; ++k) {
                new_pixel.r += std::exp(-std::abs(j - k) / (2 * sq_sigma_));
                new_pixel.g += std::exp(-std::abs(j - k) / (2 * sq_sigma_));
                new_pixel.b += std::exp(-std::abs(j - k) / (2 * sq_sigma_));
            }
            auto new_pixel2 = DoublePixel{0, 0, 0};
            for (int64_t k = 0; k < height; ++k) {
                new_pixel2.r += std::exp(-std::abs(i - k) / (2 * sq_sigma_));
                new_pixel2.g += std::exp(-std::abs(i - k) / (2 * sq_sigma_));
                new_pixel2.b += std::exp(-std::abs(i - k) / (2 * sq_sigma_));
            }
            double_pixels[i][j].r = static_cast<double>(pixels[i][j].r) * new_pixel.r * new_pixel2.r;
            double_pixels[i][j].g = static_cast<double>(pixels[i][j].g) * new_pixel.g * new_pixel2.g;
            double_pixels[i][j].b = static_cast<double>(pixels[i][j].b) * new_pixel.b * new_pixel2.b;
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            pixels[i][j].r = static_cast<uint8_t>(std::round(constant * double_pixels[i][j].r));
            pixels[i][j].g = static_cast<uint8_t>(std::round(constant * double_pixels[i][j].g));
            pixels[i][j].b = static_cast<uint8_t>(std::round(constant * double_pixels[i][j].b));
        }
    }
    image->pixels = pixels;
}

Blur::~Blur() = default;
