#include "base_filter.h"
class Grayscale : public Filter {
public:
    Grayscale();
    void ApplyFilter(Image* image) override;
    ~Grayscale() override;
};