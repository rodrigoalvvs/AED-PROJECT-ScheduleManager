//
// Created by admin1 on 14-10-2023.
//

#include <iostream>
#include "../include/Student.h"

/**
 * @brief Construct a new Student object.
 *
 * This constructor initializes a new Student object with the provided name and identifier.
 *
 * @param name_ The name of the student.
 * @param id_ The unique identifier of the student.
 */
Student::Student(const std::string& name_, int id_) {
    this->name = name_;
    this->identifier = id_;
}

/**
 * @brief Register the student in a class within a specific course unit.
 *
 * This method registers the student in a class of a course unit specified by the provided
 * UC code and class code. The student can be registered in multiple course units, but
 * cannot register in the same course unit more than once.
 *
 * @param ucCode The code of the course unit to register in (e.g., L.EICXXX).
 * @param classCode The code of the class to register in (e.g., XLEICXX).
 * @return True if the registration was successful, false if the student is already registered in the unit.
 */
bool Student::addClass(const std::string& ucCode, const std::string& classCode) {
    if(this->classesRegistered.count(ucCode) != 0){
        std::cout << "Student is already registered in this unit.";
        return false;
    }
    this->classesRegistered.insert(std::make_pair(ucCode, classCode));
    return true;
}

/**
 * @brief Get the name of the student.
 *
 * This method returns the name of the student.
 *
 * @return The name of the student.
 */
const std::string& Student::getName() const{
    return this->name;
}

/**
 * @brief Get the class code of the student in a specific unit course.
 *
 * This method returns the class code in which the student is enrolled for a specific unit course.
 *
 * @param unitCourse The code of the unit course (e.g., "L.EICXXX").
 * @return The class code in which the student is enrolled for the specified unit course.
 */
const std::string &Student::getClass(const std::string &unitCourse) {
    return this->classesRegistered[unitCourse];
}

/**
 * @brief Get a list of unit course codes in which the student is enrolled.
 *
 * This method returns a vector of unit course codes (e.g., "L.EICXXX") in which the student is enrolled.
 *
 * @return A vector of unit course codes in which the student is enrolled.
 */
std::vector<std::string> Student::getUnitCourses() {
    std::vector<std::string> result;
    result.reserve(classesRegistered.size());
    for(std::pair<std::string, std::string> pair: this->classesRegistered){
        result.push_back(pair.first);
    }
    return result;
}

/**
 * @brief Get the unique identifier (ID) of the student.
 *
 * This method returns the unique identifier (ID) of the student.
 *
 * @return The unique identifier (ID) of the student.
 */
int Student::getId() const {
    return this->identifier;
}

/**
 * @brief Get the number of classes (unit courses) registered by the student.
 *
 * This method returns the number of classes (unit courses) in which the student is registered.
 *
 * @return The number of classes (unit courses) registered by the student.
 */
int Student::getNumberOfClassesRegistered() const {
    return this->classesRegistered.size();
}

/**
 * @brief Set the name of the student.
 *
 * This method sets the name of the student to the provided name.
 *
 * @param name_ The new name of the student.
 */
void Student::setStudentName(const std::string& name_) {
    this->name = name_;
}

/**
 * @brief Set the ID of the student.
 *
 * This method sets the identifier (ID) of the student to the provided ID.
 *
 * @param id The new identifier (ID) of the student.
 */
void Student::setStudentId(int id) {
    this->identifier = id;
}

/**
 * @brief Remove a unit course from the student's registered courses.
 *
 * This method removes a specific unit course from the student's list of registered courses.
 *
 * @param ucId The identifier (ID) of the unit course to be removed.
 */
void Student::removeClass(const std::string &ucId) {

    this->classesRegistered.erase(ucId);
}

/**
 * @brief Get a shared pointer to the list of unit courses and their associated classes.
 *
 * This method returns a shared pointer to an unordered map containing the unit courses (UCs)
 * and their associated classes in which the student is registered.
 *
 * @return A shared pointer to an unordered map with unit courses (keys) and class codes (values).
 */
std::shared_ptr<std::unordered_map<std::string, std::string>> Student::getClasses(){
    return std::make_shared<std::unordered_map<std::string, std::string>>(this->classesRegistered);
}

/**
 * @brief Check if the student is enrolled in a specific unit course (UC).
 *
 * This method checks if the student is enrolled in the specified unit course (UC).
 *
 * @param ucId The identifier of the unit course (e.g., "L.EICXXX").
 * @return True if the student is enrolled in the UC, false otherwise.
 */
bool Student::checkEnrollment(const std::string &ucId) const {
    return this->classesRegistered.find(ucId) != this->classesRegistered.end();
}





