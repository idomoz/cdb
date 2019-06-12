cmake_minimum_required(VERSION 3.14)
project(cdb C)

set(CMAKE_C_STANDARD 11)

add_executable(cdb main.c dict.c dict.h bucket.c bucket.h item_node.c item_node.h array.c array.h murmur3.c murmur3.h cdb_types.h)