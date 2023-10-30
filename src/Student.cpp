//
// Created by admin1 on 14-10-2023.
//

#include <iostream>
#include "../include/Student.h"


Student::Student(const std::string& name_, int id_) {
    this->name = name_;
    this->identifier = id_;
}

bool Student::addClass(const std::string& ucCode, const std::string& classCode) {
    if(this->classesRegistered.count(ucCode) != 0){
        std::cout << "Student is already registered in this unit.";
        return false;
    }
    this->classesRegistered.insert(std::make_pair(ucCode, classCode));
    return true;
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

void Student::removeClass(const std::string &ucId) {

    this->classesRegistered.erase(ucId);
}

std::shared_ptr<std::unordered_map<std::string, std::string>> Student::getClasses(){
    return std::make_shared<std::unordered_map<std::string, std::string>>(this->classesRegistered);
}

bool Student::checkEnrollment(const std::string &ucId) const {
    return this->classesRegistered.find(ucId) != this->classesRegistered.end();
}





