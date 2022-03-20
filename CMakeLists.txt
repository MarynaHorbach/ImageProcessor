cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        test.cpp filters/base_filter.cpp
        filters/crop.cpp
        filters/filter_creator.cpp arg_parser.cpp
        bmp.cpp controller.cpp image.cpp io.cpp
        filters/grayscale.cpp filters/negative.cpp filters/sharpening.cpp filters/edge_detection.cpp filters/blur.cpp)
