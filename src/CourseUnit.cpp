//
// Created by admin1 on 19-10-2023.
//

#include <iostream>
#include <sstream>
#include <list>
#include "../include/CourseUnit.h"

CourseUnit::CourseUnit() {
    classes.clear();
}

int CourseUnit::getNumberOfClasses() const {
    return this->classes.size();
}


bool CourseUnit::addClass(const std::string& classId) {
    classes.insert(std::make_pair(classId, std::make_shared<CourseClass>(CourseClass(classId))));
    return true;
}

std::shared_ptr<CourseClass> CourseUnit::getClass(const std::string& id) {
    if(this->classes.count(id) == 0) return nullptr;
    return this->classes[id];
}

bool CourseUnit::addStudent(const std::string &classId, int studentId) {
    this->classes[classId]->addStudent(studentId);
    return true;
}

int CourseUnit::getStudentCount() {
    int studentCount = 0;
    for(std::pair<std::string, std::shared_ptr<CourseClass>> pair: classes){
        studentCount += pair.second->getStudentCount();
    }
    return studentCount;
}

int CourseUnit::getStudentCountOnClass(const std::string &classId) {
    return this->classes[classId]->getStudentCount();
}

const std::vector<int>& CourseUnit::getStudentListOnClass(const std::string &classId) {
    return this->classes[classId]->getStudents();
}

const std::vector<std::shared_ptr<Period>> &CourseUnit::getClasses(const std::string &classId) {
    return this->classes[classId]->getClasses();
}

std::shared_ptr<std::list<int>> CourseUnit::getStudentList() {
    std::list<int> students;
    for(std::pair<std::string, std::shared_ptr<CourseClass>> class_: classes){

        for(int studentId : class_.second->getStudents()){
            students.push_back(studentId);
        }
    }
    return std::make_shared<std::list<int>>(students);
}

