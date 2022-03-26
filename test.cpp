#include "catch.hpp"
#include "arg_parser.h"
#include "exception.cpp"
#include "io.h"
#include "controller.h"

TEST_CASE("Parser_WrongArgumentExceptions_number_of_parameters") {
    const char* argv[] = {"/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp"};
    REQUIRE_THROWS_AS(ArgParser::Parse(2, argv), WrongArgumentsException);
    const char* argv2[] = {"/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp"};
    REQUIRE_THROWS_AS(ArgParser::Parse(1, argv2), WrongArgumentsException);
    const char* argv3[] = {"/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur"};
    REQUIRE_THROWS_AS(ArgParser::Parse(2, argv3), WrongArgumentsException);
}

TEST_CASE("Reader_FileExceptions") {
    const char* argv[] = {"./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/e.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp"};
    auto parsed_args = ArgParser::Parse(3, argv);
    auto reader = Reader(parsed_args.in_file_path);
    REQUIRE_THROWS_AS(reader.Read(), FileProblemException);
    const char* argv3[] = {"./image_processor",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/for_test.bmp",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.txt", "-blur"};
    parsed_args = ArgParser::Parse(3, argv3);
    reader = Reader(parsed_args.in_file_path);
    REQUIRE_THROWS_AS(reader.Read(), FileProblemException);
    const char* argv4[] = {"./image_processor", "...",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur"};
    parsed_args = ArgParser::Parse(3, argv4);
    reader = Reader(parsed_args.in_file_path);
    REQUIRE_THROWS_AS(reader.Read(), FileProblemException);
}

TEST_CASE("CropRightParameters") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "400",
                          "500"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("CropWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "-3",
                          "500"};
    auto parsed_args2 = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args2.filters), WrongArgumentsException);
}
TEST_CASE("CropWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-crop", "3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("CropWrongParameters3") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "300",
                          "500",
                          "500"};
    auto parsed_args = ArgParser::Parse(7, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("CropWrongParameters4") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "300",
                          "k"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("CropWrongParameters5") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-crop"};
    auto parsed_args = ArgParser::Parse(4, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("BlurRightParameters") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur", "3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("BlurWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur", "-3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("BlurWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-blur",
                          "3",
                          "4"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("BlurWrongParameters3") {
    const char* argv2[] = {"./image_processor",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur"};
    auto parsed_args2 = ArgParser::Parse(4, argv2);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args2.filters), WrongArgumentsException);
}
TEST_CASE("BlurWrongParameters4") {
    const char* argv2[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-blur", "lrfdr"};
    auto parsed_args2 = ArgParser::Parse(5, argv2);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args2.filters), WrongArgumentsException);
}

TEST_CASE("SharpRightParameters") {
    const char* argv1[] = {"./image_processor",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                           "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-sharp"};
    auto parsed_args1 = ArgParser::Parse(4, argv1);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args1.filters));
}
TEST_CASE("SharpWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-sharp",
                          "-3",
                          "500"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("SharpWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-sharp", "3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("SharpWrongParameters3") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-sharp", "l"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("EdgeRightParameters") {
    const char* argv[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-edge", "0.5"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("EdgeWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-edge",
                          "0.3",
                          "500"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("EdgeWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-edge", "-1"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("EdgeWrongParameters3") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-edge"};
    auto parsed_args = ArgParser::Parse(4, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("EdgeWrongParameters4") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-edge", "k"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("GrayRightParameters") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-gs"};
    auto parsed_args = ArgParser::Parse(4, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("GrayWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-gs", "0.3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("GrayWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-gs", "k"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("NegativeRightParameters") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-neg"};
    auto parsed_args = ArgParser::Parse(4, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("NegativeWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-neg", "0.3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("NegativeWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-neg", "k"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("PixRightParameters") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-pix", "4"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_NOTHROW(FilterFactory::CreateFilterSeq(parsed_args.filters));
}
TEST_CASE("PixWrongParameters1") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-pix", "-3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("PixWrongParameters2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-pix",
                          "3",
                          "4"};
    auto parsed_args = ArgParser::Parse(6, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("PixWrongParameters3") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-pix"};
    auto parsed_args = ArgParser::Parse(4, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("PixWrongParameters4") {
    const char* argv[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-pix", "lrfdr"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}
TEST_CASE("PixWrongParameters5") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-pix", "0.3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongArgumentsException);
}

TEST_CASE("WrongFilterNameTest") {
    const char* argv[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-;rugvbw", "0.3"};
    auto parsed_args = ArgParser::Parse(5, argv);
    REQUIRE_THROWS_AS(FilterFactory::CreateFilterSeq(parsed_args.filters), WrongFilterException);
}

// checking application of filters

TEST_CASE("ApplyWithoutExceptions") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "400",
                          "300",
                          "-sharp",
                          "-pix",
                          "4"};
    auto parsed_args = ArgParser::Parse(9, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}
TEST_CASE("ApplyWithoutExceptions2") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "400",
                          "250",
                          "-sharp",
                          "-edge",
                          "0.039"};
    auto parsed_args = ArgParser::Parse(9, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}
TEST_CASE("ApplyWithoutExceptions3") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "400",
                          "300",
                          "-neg",
                          "-pix",
                          "4"};
    auto parsed_args = ArgParser::Parse(9, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}
TEST_CASE("ApplyWithoutExceptions4") {
    const char* argv[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-sharp", "-neg"};
    auto parsed_args = ArgParser::Parse(5, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}
TEST_CASE("ApplyWithoutExceptions5") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "900",
                          "300",
                          "-gs"};
    auto parsed_args = ArgParser::Parse(7, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}
TEST_CASE("ApplyWithoutExceptions6") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp",
                          "-crop",
                          "900",
                          "300",
                          "-blur",
                          "5"};
    auto parsed_args = ArgParser::Parse(8, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    REQUIRE_NOTHROW(controller.Apply(filters));
}

TEST_CASE("R=G=B_afterGrayscale") {
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-gs"};
    auto parsed_args = ArgParser::Parse(4, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    controller.Apply(filters);
    REQUIRE(new_image.pixels[0][0].red == new_image.pixels[0][0].green);
    REQUIRE(new_image.pixels[0][0].red == new_image.pixels[0][0].green);
}

TEST_CASE("OnlyBlack&WhiteAfterEdge") {
    const char* argv[] = {
        "./image_processor", "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
        "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/output.bmp", "-edge", "0.039"};
    auto parsed_args = ArgParser::Parse(5, argv);
    auto filters = FilterFactory::CreateFilterSeq(parsed_args.filters);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    Controller controller = Controller(&new_image);
    controller.Apply(filters);
    for (const auto& row : new_image.pixels) {
        for (const auto& pixel : row) {
            REQUIRE((pixel.red == 255 || pixel.red == 0));
            REQUIRE((pixel.green == 255 || pixel.green == 0));
            REQUIRE((pixel.blue == 255 || pixel.blue == 0));
            REQUIRE(pixel.red == pixel.blue);
            REQUIRE(pixel.red == pixel.green);
        }
    }
}

// Writing

TEST_CASE("WriterFileExceptions") {
    ArgParser parser = ArgParser();
    const char* argv[] = {"./image_processor",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/examples/example.bmp",
                          "/home/maryna/cpp-base-hse-2022/projects/image_processor/mples/....bmp"};
    auto parsed_args = parser.Parse(3, argv);
    auto reader = Reader(parsed_args.in_file_path);
    auto image = reader.Read();
    Image new_image(image.bm_header.bm_width, image.bm_header.bm_height, image.image_array, &image);
    auto writer = Writer(parsed_args.out_file_path);
    REQUIRE_THROWS_AS(writer.Write(image), FileProblemException);
}