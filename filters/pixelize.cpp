#include "pixelize.h"
#include "crop.h"
#include "../exception.cpp"
#include <cmath>

Pixelize::Pixelize(int64_t convol) : convol_(convol) {
    if (convol < 1) {
        throw WrongArgumentsException(
            "Wrong format of arguments for Pixelize filter: convolution_number (>= 1) was expected, but " +
            std::to_string(convol) + " was given");
    }
}

void Pixelize::ApplyFilter(Image* image) {
    int k = convol_;
    int64_t height = image->GetHeight();
    int64_t width = image->GetWidth();
    auto value = pow(3, k);
    if (value > std::min(height, width)) {
        while (value > std::min(height, width)) {
            --k;
            value /= 3;
        }
        std::cout << "Convolution number was too big for the size of the picture, so it was decreased to " +
                         std::to_string(k)
                  << std::endl;
    }
    for (int i = 0; i < k; ++i) {
        ApplyMatrix(image);
    }
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    std::vector<std::vector<Pixel>> new_pixels;
    width = image->GetWidth();
    height = image->GetHeight();
    int64_t ext = std::pow(3, k);
    for (int64_t i = 0; i < height; ++i) {
        std::vector<Pixel> row(width * ext);
        for (int64_t j = 0; j < width; ++j) {
            for (int64_t t = j * ext; t < j * ext + ext; ++t) {
                row[t] = pixels[i][j];
            }
        }
        for (int64_t t = 0; t < ext; ++t) {
            new_pixels.push_back(row);
        }
    }
    image->SetHeight(new_pixels.size());
    image->SetWidth(new_pixels[0].size());
    image->pixels = new_pixels;
}

void Pixelize::ApplyMatrix(Image* image) {
    int64_t width = image->GetWidth();
    int64_t height = image->GetHeight();
    auto crop = Crop(3 * (width / 3), 3 * (height / 3));
    crop.ApplyFilter(image);
    width = image->GetWidth();
    height = image->GetHeight();
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    std::vector<std::vector<Pixel>> new_pixels;
    int red = 0;
    int green = 0;
    int blue = 0;
    for (int64_t i = 0; i < height - 2; i += 3) {
        new_pixels.push_back(std::vector<Pixel>(width / 3));
        for (int64_t j = 0; j < width - 2; j += 3) {
            red = 0;
            green = 0;
            blue = 0;
            for (int64_t x = 0; x < 3; ++x) {
                for (int64_t y = 0; y < 3; ++y) {
                    int64_t x1 = std::clamp(i + x, static_cast<int64_t>(0), height - 1);
                    int64_t y1 = std::clamp(j + y, static_cast<int64_t>(0), width - 1);
                    red += int(pixels[x1][y1].red);
                    green += int(pixels[x1][y1].green);
                    blue += int(pixels[x1][y1].blue);
                }
            }
            red /= 9;
            green /= 9;
            blue /= 9;
            new_pixels[i / 3][j / 3].red = std::min(255, std::max(0, red));
            new_pixels[i / 3][j / 3].green = std::min(255, std::max(0, green));
            new_pixels[i / 3][j / 3].blue = std::min(255, std::max(0, blue));
        }
    }
    image->SetHeight(new_pixels.size());
    image->SetWidth(new_pixels[0].size());
    image->pixels = new_pixels;
}
