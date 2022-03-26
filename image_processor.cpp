#include "io.h"
#include "arg_parser.h"
#include "image.h"
#include "filters/filter_creator.h"
#include "controller.h"
#include "exception.cpp"
#include <fstream>

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        try {
            std::ifstream in("/home/maryna/cpp-base-hse-2022/projects/image_processor/help.txt");
            std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            std::cout << str;
        } catch (...) {
            throw WrongArgumentsException(
                "No arguments were given. Unfortunately, It's smth wrong with help file? so try to pass some "
                "arguments.");
        }
    } else {
        auto parsed_args = ArgParser::Parse(argc, argv);
        auto reader = Reader(parsed_args.in_file_path);
        auto image = reader.Read();
        Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
        Controller controller = Controller(&new_image);
        auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
        controller.Apply(filters);
        auto writer = Writer(parsed_args.out_file_path);
        writer.Write(image);
    }
    return 0;
}
