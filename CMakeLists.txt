cmake_minimum_required(VERSION 3.20)
project(lzw)

set(CMAKE_CXX_STANDARD 20)

add_executable(lzw main.cpp BitsOutputStream.cpp BitsOutputStream.h BitsInputStream.cpp BitsInputStream.h LZWInputStream.cpp LZWInputStream.h LZWOutputStream.cpp LZWOutputStream.h LZW.cpp LZW.h)
