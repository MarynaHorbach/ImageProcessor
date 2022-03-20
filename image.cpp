#include "image.h"
#include "bmp.h"

Image::Image(size_t width, size_t height, const std::vector<uint8_t>& byte_array, BitMap* bitmap)
    : pixels({}), bitmap(bitmap), width_(width), height_(height) {
    pixels.resize(height_);
    for (auto& v : pixels) {
        v.resize(width_);
    }
    size_t byte_num = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j].b = byte_array[byte_num];
            ++byte_num;
            pixels[i][j].g = byte_array[byte_num];
            ++byte_num;
            pixels[i][j].r = byte_array[byte_num];
            ++byte_num;
        }
    }
}

// std::vector<std::vector<Pixel>> Image::GetPixels() const {
//     return pixels;
// }

// void Image::SetPixels(std::vector<std::vector<Pixel>> &new_pixels) {
//     pixels = new_pixels;
//     width_ = (pixels[0]).size();
//     height_ = pixels.size();
//     this->bitmap->Upgrade(pixels);
// }

std::vector<Pixel>& Image::operator[](size_t x) {
    return pixels[x];
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

void Image::SetWidth(size_t w) {
    width_ = w;
}
void Image::SetHeight(size_t h) {
    height_ = h;
}