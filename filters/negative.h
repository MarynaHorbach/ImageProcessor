#pragma once

#include "base_filter.h"
class Negative : public Filter {
public:
    Negative();
    void ApplyFilter(Image* image) override;
    ~Negative() override;
};