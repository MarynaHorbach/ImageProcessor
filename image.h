#pragma once

#include "bmp.h"

#include <vector>
#include <string>

class Image {
public:
    Image(size_t width, size_t height, const std::vector<uint8_t>& byte_array, BitMap* bitmap);

    std::vector<Pixel>& operator[](size_t x);
    size_t GetWidth() const;
    size_t GetHeight() const;
    void SetWidth(size_t w);
    void SetHeight(size_t h);

    std::vector<std::vector<Pixel>> pixels;
    BitMap* bitmap;

private:
    size_t width_;
    size_t height_;
};