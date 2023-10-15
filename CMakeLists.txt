cmake_minimum_required(VERSION 3.26)
project(AED_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_PROJ
        classes/main.cpp
        classes/Class.cpp
        headers/Class.h
        classes/Student.cpp
        headers/Student.h
        classes/Uc.cpp
        headers/Uc.h
        classes/CourseManager.cpp
        headers/CourseManager.h
        classes/CourseManager.cpp
        )
