#include "io.h"
#include <stdio.h>
#include <fstream>
#include <cmath>

Reader::Reader(const std::string& file) : file_(file) {
}

BitMap Reader::Read() const {
    BitMap bitmap = BitMap();
    std::ifstream input{file_, std::ios::in | std::ios::binary};
    if (input.is_open()) {
        input.seekg(0, input.beg);
        input.read(reinterpret_cast<char *>(&(bitmap.file_header)), sizeof(bitmap.file_header));
        input.read(reinterpret_cast<char *>(&(bitmap.bm_header)), sizeof(bitmap.bm_header));
        input.seekg(bitmap.file_header.offset, input.beg);
        bitmap.bm_header.h_size = sizeof(BitMapHeader);
        bitmap.file_header.offset = sizeof(bitmap.file_header) + sizeof(bitmap.bm_header);
        bitmap.file_header.bm_size = bitmap.file_header.offset;
        int64_t new_size = bitmap.bm_header.bm_width * bitmap.bm_header.bm_height * bitmap.bm_header.bm_bit_count / 8;
        bitmap.image_array.resize(new_size);
        if (bitmap.bm_header.bm_width % 4 == 0) {
            input.read(reinterpret_cast<char *>(bitmap.image_array.data()), bitmap.image_array.size());
            bitmap.file_header.bm_size += bitmap.image_array.size();
        } else {
            int64_t width_in_bytes = bitmap.bm_header.bm_width * bitmap.bm_header.bm_bit_count / 8;
            int64_t padding_size_bytes = 4 * std::floor((width_in_bytes + 3) / 4) - width_in_bytes;
            std::vector<uint8_t> arr_for_padding(padding_size_bytes);
            for (size_t i = 0; i < bitmap.bm_header.bm_height; ++i) {
                input.read(reinterpret_cast<char *>(bitmap.image_array.data() + width_in_bytes * i),
                           width_in_bytes);
                input.read(reinterpret_cast<char *>(arr_for_padding.data()),
                           padding_size_bytes);
            }
            bitmap.file_header.bm_size += bitmap.bm_header.bm_height * (width_in_bytes + padding_size_bytes);
        }
    }
    input.close();
    return bitmap;
}


Writer::Writer(const std::string& file) : file_(file) {
}


void Writer::Write(const BitMap& bitmap) const {
    std::ofstream output{file_, std::ios::out | std::ios::binary};
    if (output.is_open()) {
        output.write(reinterpret_cast<const char *>(&bitmap.file_header), sizeof(bitmap.file_header));
        output.write(reinterpret_cast<const char *>(&(bitmap.bm_header)), sizeof(bitmap.bm_header));
        output.seekp(bitmap.file_header.offset, output.beg);
        if (bitmap.bm_header.bm_width % 4 == 0) {
            output.write(reinterpret_cast<const char *>(bitmap.image_array.data()), bitmap.image_array.size());
        } else {
            auto width_in_bytes = bitmap.bm_header.bm_width * bitmap.bm_header.bm_bit_count / 8;
            size_t padding_size_bytes = 4 * std::floor((width_in_bytes + 3) / 4) - width_in_bytes;
            std::vector<uint8_t> arr_for_padding(padding_size_bytes);
            for (size_t i = 0; i < bitmap.bm_header.bm_height; ++i) {
                output.write(reinterpret_cast<const char *>(bitmap.image_array.data() + width_in_bytes * i),
                             width_in_bytes);
                output.write(reinterpret_cast<const char *>(arr_for_padding.data()),
                             padding_size_bytes);
            }
        }
    }
    output.close();
}