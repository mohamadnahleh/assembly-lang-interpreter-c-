cmake_minimum_required(VERSION 3.27)
project(cs474_project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(cs474_project4 main.cpp
        AssemblyLangInterpreter.h
        Instruction.h
        AssemblyLangInterpreter.cpp
        Instruction.cpp
)
