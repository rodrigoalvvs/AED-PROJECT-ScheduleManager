//
// Created by admin1 on 19-10-2023.
//

#include <iostream>
#include <sstream>
#include <list>
#include "../include/CourseUnit.h"
/**
 * This is the constructor that handles the creation of a course unit.
 */
CourseUnit::CourseUnit() {
    this->classes.clear();
    this->studentCount = 0;
}

/**
 * This is a function that gets the numbers of classes in the course unit.
 * @return the number of classes in the course unit.
 */

int CourseUnit::getNumberOfClasses() const {
    return this->classes.size();
}


/**
 * This is a function that attempts to add a class to a course unit.
 * @return boolean value which specifies if the operation was succesfull.
 */
bool CourseUnit::addClass(const std::string& classId) {
    classes.insert(std::make_pair(classId, std::make_shared<CourseClass>(CourseClass(classId))));
    return true;
}

/**
 * Retrieves a reference to a class within the course unit by its ID.
 *
 * @param classId A string representing the ID of the class to retrieve.
 * @return A reference to a class if found; returns nullptr if the class is not found.
 */
std::shared_ptr<CourseClass> CourseUnit::getClass(const std::string& classId) {
    if(this->classes.count(classId) == 0) return nullptr;
    return this->classes[classId];
}

/**
 * Retrieves a boolean value based on the possibility to add a new student.
 *
 * @param classId A string representing the ID of the class to add the student.
 * @param studentId A string representing the ID of the student to add.
 * @return A boolean, true if the student was successfuly added to the class, false otherwise.
 */
bool CourseUnit::addStudent(const std::string &classId, int studentId) {
    this->classes[classId]->addStudent(studentId);
    this->studentCount += 1;
    return true;
}

/**
 * Retrieves the count of students in the course unit.
 *
 * @return An integer representing the count of students.
 */
int CourseUnit::getStudentCountOnClass(const std::string &classId) {
    return this->classes[classId]->getStudentCount();
}


/**
 * Retrieves the list of students in a specific class.
 *
 * @param classId A string representing the ID of the class to get the students from.
 * @return A constant reference to a vector of integers representing the students in the class.
 */

const std::vector<int>& CourseUnit::getStudentListOnClass(const std::string &classId) {
    return this->classes[classId]->getStudents();
}

/**
 * Retrieves the list of weekly periods in a specific class.
 * @param classId A string representing the ID of the class to get the periods from.
 * @return A constant reference to a vector of shared pointers of Periods in the class.
 */
const std::vector<std::shared_ptr<Period>> &CourseUnit::getClassPeriods(const std::string &classId) {
    return this->classes[classId]->getClasses();
}


/**
 * Retrieves a list of students in the course unit.
 *
 * @return A shared pointer to a list of integer values containing the student IDs.
 */

std::shared_ptr<std::list<int>> CourseUnit::getStudentList() {
    std::list<int> students;
    for(std::pair<std::string, std::shared_ptr<CourseClass>> class_: classes){

        for(int studentId : class_.second->getStudents()){
            students.push_back(studentId);
        }
    }
    return std::make_shared<std::list<int>>(students);
}

/**
 * Retrieves the academic year in which this course unit is taught.
 *
 * @return An integer value representing the academic year, or -1 if no classes are found.
 */
int CourseUnit::getUnitYear() const {
    for(std::pair<std::string, std::shared_ptr<CourseClass>> class_: this->classes){
        return std::stoi(class_.second->getClassId().substr(0, 1));
    }
    return -1;
}

int CourseUnit::getStudentCount() {
    return this->studentCount;
}

