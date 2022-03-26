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
            int new_colour =
                std::round(0.299 * pixels[i][j].red + 0.587 * pixels[i][j].green + 0.114 * pixels[i][j].blue);
            pixels[i][j].red = new_colour;
            pixels[i][j].green = new_colour;
            pixels[i][j].blue = new_colour;
        }
    }
}

Grayscale::~Grayscale() = default;