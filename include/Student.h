//
// Created by admin1 on 14-10-2023.
//

#ifndef AED_PROJ_STUDENT_H
#define AED_PROJ_STUDENT_H

#include <string>
#include <unordered_map>
#include "Uc.h"
#include "Class.h"

class Student {
private:
    std::string name;
    int identifier;
    //std::unordered_map<Uc, Class> classes;
public:
    Student(std::string name_, int id_);
};


#endif //AED_PROJ_STUDENT_H
