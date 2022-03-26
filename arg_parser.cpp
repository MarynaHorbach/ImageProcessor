#include "arg_parser.h"
#include "exception.cpp"

FilterParams::FilterParams() = default;

FilterParams::FilterParams(std::string name, const std::vector<std::string>& params) : name(name), params(params) {
}

ParsedArgs::ParsedArgs(std::string in, std::string out) : in_file_path(in), out_file_path(out), filters({}) {
}

ParsedArgs::ParsedArgs() = default;

ParsedArgs ArgParser::Parse(int argc, const char* argv[]) {
    if (argc < 3) {
        throw WrongArgumentsException("Expected at least 3 arguments, " + std::to_string(argc) + " were given.");
    } else if (argc == 3) {
        ParsedArgs result;
        result.in_file_path = argv[1];
        result.out_file_path = argv[2];
        return result;
    } else {
        ParsedArgs result;
        result.in_file_path = argv[1];
        result.out_file_path = argv[2];
        int i = 3;
        while (i < argc) {
            std::string filter_name = argv[i];
            ++i;
            std::vector<std::string> filter_params = {};
            char start_of_filter = '-';
            while (true) {
                while (i < argc && char(argv[i][0]) != start_of_filter) {
                    filter_params.emplace_back(argv[i]);
                    ++i;
                }
                try {
                    std::stod(argv[i]);
                } catch (...) {
                    result.filters.push_back(FilterParams(filter_name, filter_params));
                    break;
                }
                filter_params.emplace_back(argv[i]);
                ++i;
            }
        }
        return result;
    }
}
