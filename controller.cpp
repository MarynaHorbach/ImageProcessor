#include "controller.h"

Controller::Controller(Image *image): image_(image) {}

void Controller::Apply(std::vector<std::shared_ptr<Filter>> seq) {
    std::vector<std::vector<Pixel>> pixels;
    for(auto filter : seq){
        filter->ApplyFilter(image_);
    }
    image_->bitmap->Upgrade(image_->pixels);
}

