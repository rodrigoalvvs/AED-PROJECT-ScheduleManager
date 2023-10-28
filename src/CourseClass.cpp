//
// Created by admin1 on 19-10-2023.
//
#include <iostream>
#include "../include/CourseClass.h"

// Constructor
CourseClass::CourseClass(const std::string& classId_){
    this->classes.clear();
    this->students.clear();
    this->classId = classId_;
    this->currentOrderOfStudents = -1;
}


// Student handle functions


int CourseClass::getStudentCount() const {
    return this->students.size();
}


bool CourseClass::addStudent(int studentCode_){
    this->students.push_back(studentCode_);
    return true;
}


std::shared_ptr<std::vector<int>> CourseClass::getStudents() {
    return std::make_shared<std::vector<int>>(this->students);
}

bool CourseClass::removeStudent(int studentId){
    for(auto itr= this->students.begin(); itr != this->students.end() ; itr++){
        if(*itr == studentId){
            this->students.erase(itr);
            return true;
        }
    }
    return false;
}

// Classes handle functions

const std::vector<std::shared_ptr<Period>>& CourseClass::getClasses() {
    return this->classes;
}

const std::string &CourseClass::getClassId() const {
    return this->classId;
}

int CourseClass::getClassesPerWeek() const {
    return this->classes.size();
}


bool CourseClass::addPeriod(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_) {
    std::shared_ptr<Period> currentPeriod = std::make_shared<Period>(weekDay_, startHour_, duration_, type_);
    this->classes.push_back(currentPeriod);
    return true;
}


int CourseClass::getCurrentOrder() const {
    return this->currentOrderOfStudents;
}

void CourseClass::setCurrentOrder(int orderType) {
    this->currentOrderOfStudents = orderType;
}
