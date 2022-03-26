#pragma once
#include <string>
#include "bmp.h"
class Reader {
public:
    explicit Reader(const std::string& file);
    BitMap Read() const;

private:
    std::string file_;
};

class Writer {
public:
    explicit Writer(const std::string& file);
    void Write(const BitMap& bitmap) const;

private:
    std::string file_;
};
