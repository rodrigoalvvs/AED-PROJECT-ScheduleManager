//
// Created by admin1 on 19-10-2023.
//

#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include "../include/CourseUnit.h"
/**
 * This is the constructor that handles the creation of a course unit.
 */
CourseUnit::CourseUnit() {
    this->classes.clear();
    this->studentCount = 0;
    this->allStudents.clear();
    this->currentOrderOfStudents = -1;
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
    this->allStudents.push_back(studentId);
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

std::shared_ptr<std::vector<int>> CourseUnit::getStudentListOnClass(const std::string &classId) {
    std::shared_ptr<std::vector<int>> students = this->classes[classId]->getStudents();
    return students;
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

std::shared_ptr<std::vector<int>> CourseUnit::getStudentList() {
    return std::make_shared<std::vector<int>>(this->allStudents);
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

/**
 * @brief Retrieves the count of students currently enrolled in this specific course unit.
 *
 * This function returns an integer value that represents the number of students who are currently enrolled in the course unit.

 * @note This count reflects the current enrollment status and may change over time as students join or leave the unit.

 * @return An integer value indicating the count of students enrolled in the course unit.
 */
int CourseUnit::getStudentCount() const {
    return this->studentCount;
}


/**
 * @brief Removes a student from a specific class within the course unit.
 *
 * This function removes a student from a specific class identified by its unique identifier (classId) within the course unit.
 *
 * @param classId The unique identifier of the class from which the student is to be removed.
 * @param studentId The unique identifier of the student to remove.
 *
 * @return true if the removal operation was successful, false otherwise.
 */

bool CourseUnit::removeStudentFromClass(const std::string &classId, int studentId) {
    bool removalStatus = this->classes[classId]->removeStudent(studentId);
    this->studentCount--;
    return removalStatus;
}


/**
 * @brief Retrieves the current order of students in the course unit.
 *
 * This function returns an integer value indicating the current order of students within the course unit. The order can have different meanings:
 *
 * - 1: Order by studentId.
 * - 2: Order alphabetically.
 *
 * @return An integer value representing the current order of students in the course unit.
 */

int CourseUnit::getCurrentOrder() const {
    return this->currentOrderOfStudents;
}

/**
 * @brief Set the current order of students in the course unit.
 *
 * This function allows setting the current order of students within the course unit. The order can have different meanings:
 *
 * - 1: Order by studentId.
 * - 2: Order alphabetically.
 *
 * @param orderType An integer value indicating the desired order type (1 for studentId, 2 for alphabetical order).
 */

void CourseUnit::setCurrentOrder(int orderType) {
    this->currentOrderOfStudents = orderType;
}

/**
 * @brief Find and return a class with available vacancies.
 *
 * This function iterates through the classes within the course unit and checks if any of them have available vacancies for students.
 *
 * @return The identifier of a class with available vacancies, or an empty string if no class has vacancies.
 */
std::string CourseUnit::getClassWithVacancy() const {
    for(std::pair<std::string, std::shared_ptr<CourseClass>> class_: this->classes){
        if(class_.second->getStudentCount() < class_.second->getClassLimit()){
            return class_.first;
        }
    }
    return "";
}

/**
 * @brief Get the current occupancy of a specific class within the course unit.
 *
 * This function retrieves the current number of students enrolled in a specific class of the course unit.
 *
 * @param classId The identifier of the class to check occupancy for.
 * @return The number of students currently enrolled in the class, or -1 if the class does not exist.
 */
int CourseUnit::getClassOccupancy(const std::string &classId) const {
    if(this->classes.find(classId) == this->classes.end()) return -1;
    return this->classes.find(classId)->second->getStudentCount();
}

/**
 * @brief Get the total occupancy of the course unit.
 *
 * This function calculates and returns the total number of students enrolled in all classes
 * of the course unit.
 *
 * @return The total occupancy of the course unit.
 */
int CourseUnit::getOccupancy() const {
    int result = 0;
    for(std::pair<std::string, std::shared_ptr<CourseClass>> classPair: this->classes){
        result += classPair.second->getStudentCount();
    }
    return result;
}

/**
 * @brief Get a list of all classes in the course unit.
 *
 * This function retrieves a list of all classes within the course unit.
 *
 * @return A list of shared pointers to CourseClass objects representing the classes.
 */
std::list<std::shared_ptr<CourseClass>> CourseUnit::getClasses() {
    std::list<std::shared_ptr<CourseClass>> classes_;
    for(std::pair< std::string, std::shared_ptr<CourseClass>> classPair: this->classes){
        classes_.push_back(classPair.second);
    }
    return classes_;
}
