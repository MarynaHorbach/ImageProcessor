#include "io.h"
#include "arg_parser.h"
#include "image.h"
#include "filters/filter_creator.h"
#include "controller.h"

int main(int argc, const char *argv[]) {
    std::string path = "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp";
    auto reader = Reader(path);
    auto image = reader.Read();
    ArgParser parser = ArgParser();
    auto parsed_args = parser.Parse(argc, argv);
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    FilterFactory filter_factory = FilterFactory();
    auto filters = filter_factory.CreateFilterSeq(parsed_args.filters);
    controller.Apply(filters);
    std::string path2 = "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp";
    auto writer = Writer(path2);
    writer.Write(image);
    return 0;
}
