#include "crop.h"
#include "base_filter.h"
#include "../exception.cpp"
Crop::Crop(int64_t width, int64_t height) : width_(width), height_(height) {
    if (width <= 0 || height <= 0) {
        throw WrongArgumentsException(
            "Wrong format of arguments for Crop filter: width >= 0, height >= 0 were expected: width = " +
            std::to_string(width) + ", height = " + std::to_string(height) + " were given.");
    }
}

void Crop::ApplyFilter(Image* image) {
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    if (width <= width_ && height <= height_) {
        return;
    } else if (width <= width_) {
        pixels.resize(height_);
    } else if (height <= height_) {
        for (auto& vec : pixels) {
            vec.resize(width_);
        }
    } else {
        for (size_t i = 0; i < height_; ++i) {
            pixels[i] = pixels[i + height - height_];
        }
        pixels.resize(height_);
        for (auto& vec : pixels) {
            vec.resize(width_);
        }

        image->SetHeight(height_);
        image->SetWidth(width_);
    }
}

Crop::~Crop() = default;