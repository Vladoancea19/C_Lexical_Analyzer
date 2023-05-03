cmake_minimum_required(VERSION 3.20)
project(C_Lexical_Analyzer)

set(CMAKE_CXX_STANDARD 23)

add_executable(C_Lexical_Analyzer main.cpp Token.cpp Token.h Transition.cpp Transition.h TokenValueMap.cpp TokenValueMap.h LexicalAnalyzer.cpp LexicalAnalyzer.h)
