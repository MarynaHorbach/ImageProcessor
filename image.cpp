#include "image.h"
#include "bmp.h"

Image::Image(size_t width, size_t height, const std::vector<uint8_t>& byte_array, BitMap* bitmap)
    : pixels({}), bitmap(bitmap), width_(width), height_(height) {
    pixels.resize(height_);
    for (auto& v : pixels) {
        v.resize(width_);
    }
    size_t byte_num = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            pixels[i][j].blue = byte_array[byte_num];
            ++byte_num;
            pixels[i][j].green = byte_array[byte_num];
            ++byte_num;
            pixels[i][j].red = byte_array[byte_num];
            ++byte_num;
        }
    }
}

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