#pragma once

#include "base_filter.h"
#include "../arg_parser.h"
#include <vector>

class FilterFactory {
public:
    static std::vector<std::shared_ptr<Filter>> CreateFilterSeq(std::vector<FilterParams>& filters);
private:
    static std::shared_ptr<Filter> CreateFilter(std::string& name, std::vector<std::string>& params);
};