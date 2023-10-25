//
// Created by admin1 on 19-10-2023.
//
#include <iostream>
#include "../include/CourseClass.h"


CourseClass::CourseClass(const std::string& classId_){
    this->classes.clear();
    this->students.clear();
    this->classId = classId_;
}


const std::string &CourseClass::getClassId() const {
    return this->classId;
}

int CourseClass::getStudentCount() const {
    return this->students.size();
}

int CourseClass::getClassesPerWeek() const {
    return this->classes.size();
}


bool CourseClass::addPeriod(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_) {
    std::shared_ptr<Period> currentPeriod = std::make_shared<Period>(weekDay_, startHour_, duration_, type_);
    this->classes.push_back(currentPeriod);
    return true;
}

bool CourseClass::addStudent(int studentCode_){
    this->students.push_back(studentCode_);
    return true;
}


const std::vector<std::shared_ptr<Period>>& CourseClass::getClasses() {
    return this->classes;
}

const std::vector<int> &CourseClass::getStudents() {
    return this->students;
}
