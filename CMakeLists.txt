cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(image_processor)

set(CMAKE_CXX_STANDARD 17)

add_executable(image_processor
        image_processor.cpp
        constants.h
        parser_com_str.cpp
        read_file.cpp
        image.cpp
        color.cpp
        write_file.cpp
        filters.cpp
        filter_control.cpp)

add_catch(image_processor_parser_test
        parser_tests.cpp
        parser_com_str.cpp
        parser_com_str.h
        )

add_catch(image_processor_filter_test
        parser_com_str.cpp
        constants.h
        filter_control.cpp
        read_file.cpp
        filters_tests.cpp
        filters.cpp
        image.cpp
        color.cpp
        )

add_catch(image_processor_read_tests
        read_tests.cpp
        read_file.cpp
        image.cpp
        color.cpp
        )
