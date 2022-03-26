#pragma once
#include <vector>
#include "filters/filter_creator.h"

class Controller {
public:
    Controller(Image* image);
    void Apply(std::vector<std::shared_ptr<Filter>> seq);

private:
    Image* image_;
};