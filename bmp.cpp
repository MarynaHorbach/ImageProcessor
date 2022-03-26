#include "bmp.h"

void BitMap::Upgrade(const std::vector<std::vector<Pixel>>& pixels) {
    bm_header.bm_height = pixels.size();
    bm_header.bm_width = (pixels[0]).size();
    image_array.resize(3 * pixels.size() * pixels[0].size());
    size_t index = 0;
    for (size_t i = 0; i < bm_header.bm_height; ++i) {
        for (size_t j = 0; j < bm_header.bm_width; ++j) {
            image_array[index] = static_cast<uint8_t>(pixels[i][j].blue);
            ++index;
            image_array[index] = static_cast<uint8_t>(pixels[i][j].green);
            ++index;
            image_array[index] = static_cast<uint8_t>(pixels[i][j].red);
            ++index;
        }
    }
}
