//
// Created by admin1 on 14-10-2023.
//

#ifndef AED_PROJ_COURSEMANAGER_H
#define AED_PROJ_COURSEMANAGER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include "Student.h"


class CourseManager {
private:
    std::unordered_map<int, Student> students;
public:
    CourseManager();
};


#endif //AED_PROJ_COURSEMANAGER_H
