#include <cmath>
#include "grayscale.h"
#include "base_filter.h"

Grayscale::Grayscale() = default;

void Grayscale::ApplyFilter(Image* image) {
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int new_colour = std::round(0.299 * pixels[i][j].r + 0.587 * pixels[i][j].g + 0.114 * pixels[i][j].b);
            pixels[i][j].r = new_colour;
            pixels[i][j].g = new_colour;
            pixels[i][j].b = new_colour;
        }
    }
    //image->pixels=pixels;
}

Grayscale::~Grayscale() = default;