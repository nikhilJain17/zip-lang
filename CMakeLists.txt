cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(zip main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Codegen.cpp Codegen.h)