cmake_minimum_required(VERSION 3.26)
project(AED_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_PROJ
        src/main.cpp
        src/Class.cpp
        include/Class.h
        src/Student.cpp
        include/Student.h
        src/Uc.cpp
        include/Uc.h
        src/CourseManager.cpp
        include/CourseManager.h
        src/CourseManager.cpp
        )
