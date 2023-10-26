cmake_minimum_required(VERSION 3.26)
project(AED_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_PROJ
        src/main.cpp
        src/Student.cpp
        include/Student.h
        src/CourseManager.cpp
        include/CourseManager.h
        src/CourseManager.cpp
        include/Period.h
        include/CourseUnit.h
        src/CourseUnit.cpp
        src/Period.cpp
        include/CourseClass.h
        src/CourseClass.cpp
        src/Request.cpp
        include/Request.h
)
