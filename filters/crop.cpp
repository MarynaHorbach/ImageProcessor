#include "crop.h"
#include "base_filter.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

void Crop::ApplyFilter(Image* image) {
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    if (width <= width_ && height <= height_) {
        return;
    } else if (width <= width_) {
        pixels.resize(height_);
        //image->SetPixels(pixels);
    } else if (height <= height_) {
        for (auto& vec : pixels) {
            vec.resize(width_);
        }
        //image->SetPixels(pixels);
    } else {
        for (size_t i = 0; i < height_;++i){
            pixels[i] = pixels[i+height - height_];
        }
        pixels.resize(height_);
        for (auto& vec : pixels) {
            vec.resize(width_);
        }
        //image->SetPixels(pixels);
        image->SetHeight(height_);
        image->SetWidth(width_);
    }
}

Crop::~Crop()=default;