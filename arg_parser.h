#pragma once
#include "filters/base_filter.h"
#include<iostream>
#include <vector>
#include <memory>

struct FilterParams{
    std::string name;
    std::vector<std::string> params;
    FilterParams();
    FilterParams(std::string name,const std::vector<std::string>& params);
};

struct ParsedArgs{
    std::string in_file_path;
    std::string out_file_path;
    std::vector<FilterParams> filters;

    ParsedArgs(std::string in, std::string out);
    ParsedArgs();
};

class ArgParser {
public:
    ParsedArgs Parse(int argc, const char* argv[]);
};