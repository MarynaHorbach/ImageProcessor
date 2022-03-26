#include "base_filter.h"
#include "../bmp.h"

class Blur : public Filter {
public:
    Blur(double sigma);
    void ApplyFilter(Image* image) override;
    ~Blur() override;

private:
    double sq_sigma_;
    size_t half_matrix_size_;
};