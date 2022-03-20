#include "filter_creator.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "blur.h"
#include <string>

std::shared_ptr<Filter> FilterFactory::CreateFilter(std::string& name, std::vector<std::string>& params) {
    if (name == "-crop") {
        if (params.size() != 2) {
            throw std::invalid_argument("Expected 2 arguments, not " + std::to_string(params.size()));
        }
        return std::make_shared<Crop>(size_t(std::stoi(params[0])), size_t(std::stoi(params[1])));
    } else if (name == "-gs") {
        if (!params.empty()) {
            throw std::invalid_argument("No arguments were required");
        }
        return std::make_shared<Grayscale>();
    } else if (name == "-neg") {
        if (!params.empty()) {
            throw std::invalid_argument("No arguments were required");
        }
        return std::make_shared<Negative>();
    } else if (name == "-sharp") {
        if (!params.empty()) {
            throw std::invalid_argument("No arguments were required");
        }
        return std::make_shared<Sharpening>();
    } else if (name == "-edge") {
        if (params.size() > 1) {
            throw std::invalid_argument("Expected 1 argument, more were given");
        }
        if (params.empty()) {
            throw std::invalid_argument("No arguments were given, 1 expected: treshold");
        }
        return std::make_shared<EdgeDetection>(std::stoi(params[0]));
    } else if (name == "-blur") {
        if (params.size() > 1) {
            throw std::invalid_argument("Expected 1 argument, more were given");
        }
        if (params.empty()) {
            throw std::invalid_argument("No arguments were given, 1 expected: treshold");
        }
        return std::make_shared<Blur>(std::stoi(params[0]));
    } else {
        throw std::invalid_argument("Filter " + name + " doesn't exist. Check the spelling.");
    }
}

std::vector<std::shared_ptr<Filter>> FilterFactory::CreateFilterSeq(std::vector<FilterParams>& filters) {
    std::vector<std::shared_ptr<Filter>> filter_seq;
    for (auto& f : filters) {
        filter_seq.push_back(CreateFilter(f.name, f.params));
    }
    return filter_seq;
}