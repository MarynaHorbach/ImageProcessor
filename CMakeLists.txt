cmake_minimum_required(VERSION 3.16)
project(projects/image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp filters/base_filter.cpp
        filters/crop.cpp
        filters/filter_creator.cpp arg_parser.cpp
        bmp.cpp controller.cpp image.cpp io.cpp
        filters/grayscale.cpp filters/negative.cpp filters/sharpening.cpp
        filters/edge_detection.cpp filters/blur.cpp filters/pixelize.cpp
        exception.cpp)

add_catch(test_image_processor
        filters/base_filter.cpp
        filters/crop.cpp
        filters/filter_creator.cpp arg_parser.cpp
        bmp.cpp controller.cpp image.cpp io.cpp
        filters/grayscale.cpp filters/negative.cpp filters/sharpening.cpp
        filters/edge_detection.cpp filters/blur.cpp filters/pixelize.cpp
        exception.cpp test.cpp
        )