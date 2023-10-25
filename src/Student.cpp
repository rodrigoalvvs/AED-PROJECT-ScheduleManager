//
// Created by admin1 on 14-10-2023.
//

#include "../include/Student.h"


Student::Student(const std::string& name_, int id_) {
    this->name = name_;
    this->identifier = id_;
}

void Student::addClass(const std::string& ucCode, const std::string& classCode) {
    this->classesRegistered.insert(std::make_pair(ucCode, classCode));
}

const std::string& Student::getName() const{
    return this->name;
}


const std::string &Student::getClass(const std::string &unitCourse) {
    return this->classesRegistered[unitCourse];
}

std::vector<std::string> Student::getUnitCourses() {
    std::vector<std::string> result;
    result.reserve(classesRegistered.size());
    for(std::pair<std::string, std::string> pair: this->classesRegistered){
        result.push_back(pair.first);
    }
    return result;
}

int Student::getId() const {
    return this->identifier;
}

int Student::getNumberOfClassesRegistered() const {
    return this->classesRegistered.size();
}

void Student::setStudentName(const std::string& name_) {
    this->name = name_;
}

void Student::setStudentId(int id) {
    this->identifier = id;
}




