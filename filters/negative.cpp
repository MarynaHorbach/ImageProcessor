#include "negative.h"
#include "base_filter.h"

Negative::Negative() = default;

void Negative::ApplyFilter(Image* image) {
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int new_colour = 255 - pixels[i][j].red;
            pixels[i][j].red = new_colour;
            new_colour = 255 - pixels[i][j].green;
            pixels[i][j].green = new_colour;
            new_colour = 255 - pixels[i][j].blue;
            pixels[i][j].blue = new_colour;
        }
    }
}

Negative::~Negative() = default;