cmake_minimum_required(VERSION 3.27)
project(huffman_compress)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman_compress main.cpp huffman.cpp huffman.h handle_article.cpp handle_article.h)
