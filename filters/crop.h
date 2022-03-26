#include "base_filter.h"
class Crop : public Filter {
public:
    Crop(int64_t width, int64_t height);
    void ApplyFilter(Image* image) override;
    ~Crop() override;

private:
    size_t width_;
    size_t height_;
};