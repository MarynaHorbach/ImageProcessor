#include "arg_parser.h"

FilterParams::FilterParams() = default;

FilterParams::FilterParams(std::string name, const std::vector<std::string>& params) : name(name), params(params) {
}

ParsedArgs::ParsedArgs(std::string in, std::string out) : in_file_path(in), out_file_path(out), filters({}) {
}

ParsedArgs::ParsedArgs() = default;

ParsedArgs ArgParser::Parse(int argc, const char *argv[]) {
    if (argc == 0) {
        // do smth
        throw std::invalid_argument("Expected at least 3 arguments, 0 given.");
    }
    if (argc < 4) {
        throw std::invalid_argument("Expected at least 3 arguments, less were given.");
    }
    // int i = 2;
    ParsedArgs result;
    result.in_file_path = argv[2];
    result.out_file_path = argv[3];
    if (argc == 4) {
        return result;
    }
    int i = 4;
    while (i < argc) {
        std::string filter_name = argv[i];  // remember that it has "-" before the name
        ++i;
        std::vector<std::string> filter_params = {};
        char start_of_filter = '-';
        while (i < argc && char(argv[i][0]) != start_of_filter) {
            filter_params.emplace_back(argv[i]);
            ++i;
        }
        result.filters.push_back(FilterParams(filter_name, filter_params));
    }
    return result;
}
