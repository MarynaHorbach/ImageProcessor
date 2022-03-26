#include "blur.h"
#include "base_filter.h"
#include "../exception.cpp"
#include <math.h>

Blur::Blur(double sigma) : sq_sigma_(sigma * sigma), half_matrix_size_(std::ceil(3 * sigma)) {
    if (sigma < 0) {
        throw WrongArgumentsException(
            "Wrong format of arguments for Blur filter: sigma (sigma >= 0) was expected: sigma = " +
            std::to_string(sigma) + " was given.");
    }
}

void Blur::ApplyFilter(Image* image) {
    auto& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    auto double_pixels = std::vector<std::vector<DoublePixel>>();
    double constant = std::pow(1 / (2 * M_PI * sq_sigma_), 1 / 2);
    for (int64_t i = 0; i < static_cast<int64_t>(height); ++i) {
        double_pixels.push_back(std::vector<DoublePixel>(width));
        for (int64_t j = 0; j < static_cast<int64_t>(width); ++j) {
            auto new_pixel = DoublePixel{0, 0, 0};
            double sum = 0;
            for (int64_t k = -static_cast<int64_t>(half_matrix_size_); k < static_cast<int64_t>(half_matrix_size_) + 1;
                 ++k) {
                double c1 = std::exp(-(k * k) / (2 * sq_sigma_));
                sum += c1;
                int64_t y1 = std::clamp(j + k, static_cast<int64_t>(0), static_cast<int64_t>(width - 1));
                new_pixel.red += c1 * static_cast<double>(pixels[i][y1].red);
                new_pixel.green += c1 * static_cast<double>(pixels[i][y1].green);
                new_pixel.blue += c1 * static_cast<double>(pixels[i][y1].blue);
            }
            new_pixel.red /= sum;
            new_pixel.green /= sum;
            new_pixel.blue /= sum;
            double_pixels[i][j] = new_pixel;
        }
    }

    auto double_pixels2 = double_pixels;
    for (int64_t i = 0; i < static_cast<int64_t>(width); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(height); ++j) {
            auto new_pixel = DoublePixel{0, 0, 0};
            double sum = 0;
            for (int64_t k = -static_cast<int64_t>(half_matrix_size_); k < static_cast<int64_t>(half_matrix_size_) + 1;
                 ++k) {
                double c1 = std::exp(-(k * k) / (2 * sq_sigma_));
                int64_t y1 = std::clamp(j + k, static_cast<int64_t>(0), static_cast<int64_t>(height - 1));
                sum += c1;
                new_pixel.red += c1 * static_cast<int64_t>(double_pixels[y1][i].red);
                new_pixel.green += c1 * static_cast<int64_t>(double_pixels[y1][i].green);
                new_pixel.blue += c1 * static_cast<int64_t>(double_pixels[y1][i].blue);
            }
            new_pixel.red /= sum;
            new_pixel.green /= sum;
            new_pixel.blue /= sum;
            double_pixels2[j][i] = new_pixel;
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            pixels[i][j].red = static_cast<uint8_t>(std::round(constant * double_pixels2[i][j].red));
            pixels[i][j].green = static_cast<uint8_t>(std::round(constant * double_pixels2[i][j].green));
            pixels[i][j].blue = static_cast<uint8_t>(std::round(constant * double_pixels2[i][j].blue));
        }
    }
}
Blur::~Blur() = default;
