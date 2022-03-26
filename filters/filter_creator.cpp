#include "filter_creator.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "blur.h"
#include "pixelize.h"
#include "../exception.cpp"
#include <string>

std::shared_ptr<Filter> FilterFactory::CreateFilter(std::string& name, std::vector<std::string>& params) {
    if (name == "-crop") {
        if (params.size() != 2) {
            throw WrongArgumentsException("Crop filter expected 2 arguments, " + std::to_string(params.size()) +
                                          " were given");
        }
        WrongArgumentsException e("");
        bool indicator = false;
        try {
            return std::make_shared<Crop>(size_t(std::stoi(params[0])), size_t(std::stoi(params[1])));
        } catch (WrongArgumentsException& except) {
            e = except;
            indicator = true;
            throw e;
        } catch (...) {
            if (!indicator) {
                throw WrongArgumentsException("Wrong format of arguments for Crop filter: width, height were expected");
            } else {
                throw e;
            }
        }
    } else if (name == "-gs") {
        if (!params.empty()) {
            throw WrongArgumentsException("Grayscale filter does not expect arguments, but " +
                                          std::to_string(params.size()) + " were given");
        }
        return std::make_shared<Grayscale>();
    } else if (name == "-neg") {
        if (!params.empty()) {
            throw WrongArgumentsException("Negative filter does not expect arguments, but " +
                                          std::to_string(params.size()) + " were given");
        }
        return std::make_shared<Negative>();
    } else if (name == "-sharp") {
        if (!params.empty()) {
            throw WrongArgumentsException("Sharpening filter does not expect arguments, " +
                                          std::to_string(params.size()) + " were given");
        }
        return std::make_shared<Sharpening>();
    } else if (name == "-edge") {
        if (params.size() != 1) {
            throw WrongArgumentsException("Edge Detection filter expected 1 argument, " +
                                          std::to_string(params.size()) + " were given");
        }
        WrongArgumentsException e("");
        bool indicator = false;
        try {
            return std::make_shared<EdgeDetection>(std::stod(params[0]));
        } catch (WrongArgumentsException& except) {
            e = except;
            indicator = true;
            throw e;
        } catch (...) {
            if (!indicator) {
                throw WrongArgumentsException(
                    "Wrong format of arguments for Edge Detection filter: treshold (from [0,1]) were expected");
            } else {
                throw e;
            }
        }
    } else if (name == "-blur") {
        if (params.size() != 1) {
            throw WrongArgumentsException("Blur filter expected 1 argument, " + std::to_string(params.size()) +
                                          " were given.");
        }
        WrongArgumentsException e("");
        bool indicator = false;
        try {
            return std::make_shared<Blur>(std::stod(params[0]));
        } catch (WrongArgumentsException& except) {
            e = except;
            indicator = true;
            throw e;
        } catch (...) {
            if (!indicator) {
                throw WrongArgumentsException(
                    "Wrong format of arguments for Blur filter: sigma (sigma > 0) was expected: sigma = " + params[0] +
                    " was given.");
            } else {
                throw e;
            }
        }
    } else if (name == "-pix") {
        if (params.size() != 1) {
            throw WrongArgumentsException("Pixelize expected 1 argument, " + std::to_string(params.size()) +
                                        " were given.");
        }
        WrongArgumentsException e("");
        bool indicator = false;
        try {
            return std::make_shared<Pixelize>(std::stoi(params[0]));
        } catch (WrongArgumentsException& except) {
            e = except;
            indicator = true;
            throw e;
        } catch (...) {
            if (!indicator) {
                throw WrongArgumentsException(
                    "Wrong format of arguments for Pixelize filter: convolution_number (>= 1) was expected.");
            } else {
                throw e;
            }
        }
    } else {
        throw WrongFilterException(
            "Filter " + name +
            " doesn't exist. Check the spelling. Run app without parameters ro see help information.");
    }
}

std::vector<std::shared_ptr<Filter>> FilterFactory::CreateFilterSeq(std::vector<FilterParams>& filters) {
    std::vector<std::shared_ptr<Filter>> filter_seq;
    for (auto& f : filters) {
        filter_seq.push_back(CreateFilter(f.name, f.params));
    }
    return filter_seq;
}