#include "negative.h"
#include "base_filter.h"

Negative::Negative()=default;

void Negative::ApplyFilter(Image* image) {
    std::vector<std::vector<Pixel>>& pixels = image->pixels;
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int new_colour = 255 - pixels[i][j].r;
            pixels[i][j].r = new_colour;
            new_colour = 255 - pixels[i][j].g;
            pixels[i][j].g = new_colour;
            new_colour = 255 - pixels[i][j].b;
            pixels[i][j].b = new_colour;
        }
    }
//    image->pixels=pixels;
}

Negative::~Negative()=default;