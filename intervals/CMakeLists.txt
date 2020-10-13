cmake_minimum_required(VERSION 3.14)
project(Intervals C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(Intervals
        headers/enums.h
        headers/interval.h
        headers/structs.h
        src/difference.c
        src/initialize_interval.c
        src/interface.c
        src/intersection.c
        src/list_of_intervals.c
        src/main.c
        src/print_error.c
        src/union.c)
