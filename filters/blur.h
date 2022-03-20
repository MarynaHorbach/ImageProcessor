#include "base_filter.h"
class Blur: public Filter{
public:
    Blur(double sigma);
    void ApplyFilter(Image* image) override;
    ~Blur() override;

private:
    double sq_sigma_;
};