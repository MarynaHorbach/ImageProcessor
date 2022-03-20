#pragma once

#include <string>
#include <vector>

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

#pragma pack(push, 1)
struct BitMapFileHeader {
    uint16_t bm_type = 0;
    uint32_t bm_size = 0;
    uint16_t bm_reserved = 0;
    uint16_t bm_reserved2 = 0;
    uint32_t offset = 0;
};

struct BitMapHeader{
    uint32_t h_size = 0;
    uint32_t bm_width = 0;
    uint32_t bm_height = 0;
    uint16_t planes = 1;
    uint16_t bm_bit_count = 24;
    uint32_t compression = 0;
    uint32_t image_size = 0;
    uint32_t x_pix_meter = 0;
    uint32_t y_pix_meter = 0;
    uint32_t used_colors = 0;
    uint32_t important_colors = 0;
};
#pragma pack(pop)

class BitMap{
public:
    BitMapFileHeader file_header;
    BitMapHeader bm_header;
    std::vector<uint8_t> image_array;
    void Upgrade(const std::vector<std::vector<Pixel>>& pixels);
};






