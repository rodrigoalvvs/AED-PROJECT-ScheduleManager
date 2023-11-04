//
// Created by admin1 on 19-10-2023.
//
#include <iostream>
#include "../include/CourseClass.h"

/**
 * @brief Constructs a CourseClass object with the given class identifier.
 *
 * This constructor initializes a CourseClass object with the specified class identifier (classId). It clears the internal data structures
 * for classes and students and sets the current order of students to -1 (unordered).

 * @param classId_ The unique identifier for the CourseClass.
 *
 */
CourseClass::CourseClass(const std::string& classId_){
    this->students.reserve(this->classLimitOccupancy);
    this->classes.clear();
    this->students.clear();
    this->classId = classId_;
    this->currentOrderOfStudents = -1;
}



/**
 * @brief Retrieves the count of students enrolled in this course class.
 *
 * This function returns an integer value indicating the count of students who are currently enrolled in this course class.
 * @note Complexity O(1)

 * @return An integer value representing the count of enrolled students.
 */
int CourseClass::getStudentCount() const {
    return this->students.size();
}

/**
 * @brief Adds a student to this course class, if class capacity allows.
 *
 * This function adds a student to the course class, identified by their student code, if the class has not reached its capacity.

 * @param studentCode_ The unique student code of the student to add.
 * @note Complexity O(1)
 * @return true if the student was successfully added to the course class, false if the class is at its capacity.
 */
bool CourseClass::addStudent(int studentCode_){
    if(this->students.size() < classLimitOccupancy){
        this->students.push_back(studentCode_);
        return true;
    }
    std::cout << "Class capacity reached!\n";
    return false;
}

/**
 * @brief Retrieves a list of students currently enrolled in this course class.
 *
 * This function returns a shared pointer to a vector of student codes, representing the students who are currently enrolled in this course class.

   @note Complexity O(1)
 * @return A shared pointer to a vector of student codes.
 */
std::shared_ptr<std::vector<int>> CourseClass::getStudents() {
    return std::make_shared<std::vector<int>>(this->students);
}

/**
 * @brief Removes a student from this course class.
 *
 * This function removes a student with the specified student ID from the course class if the student is currently enrolled.

 * @param studentId The unique student ID of the student to remove.
 * @note Complexity O(N)
 * @return true if the student was successfully removed from the course class, false if the student is not enrolled.
 */
bool CourseClass::removeStudent(int studentId){
    for(auto itr= this->students.begin(); itr != this->students.end() ; itr++){
        if(*itr == studentId){
            this->students.erase(itr);
            return true;
        }
    }
    return false;
}

/**
 * @brief Retrieves the classes associated with this course class.
 *
 * This function returns a reference to a vector of shared pointers to class periods, representing the classes associated with this course class.
 * @note Complexity O(1)

 * @return A reference to a vector of shared pointers to class periods.
 */

const std::vector<std::shared_ptr<Period>>& CourseClass::getClasses() {
    return this->classes;
}

/**
 * @brief Retrieves the unique identifier of this course class.
 *
 * This function returns a constant reference to the unique identifier (classId) of this course class.
 * @note Complexity O(1)
 * @return A constant reference to the unique identifier of the course class.
 */
const std::string &CourseClass::getClassId() const {
    return this->classId;
}
/**
 * @brief Retrieves the number of classes held per week for this course class.
 *
 * This function returns an integer value representing the number of classes held per week for this course class.
 * @note Complexity O(1)
 * @return An integer value indicating the number of classes per week for the course class.
 */
int CourseClass::getClassesCountPerWeek() const {
    return this->classes.size();
}


/**
 * @brief Adds a class period to this course class.
 *
 * This function adds a class period to the course class, specifying the day of the week (weekDay_), start hour (startHour_),
 * duration (duration_), and type (type_) of the class period.

 * @param weekDay_ The day of the week on which the class period occurs.
 * @param startHour_ The start hour of the class period.
 * @param duration_ The duration of the class period.
 * @param type_ The type of the class period (e.g., T, TP, PL).
 * @note Complexity O(1)
 * @return true if the class period was successfully added to the course class.
 */
bool CourseClass::addPeriod(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_) {
    std::shared_ptr<Period> currentPeriod = std::make_shared<Period>(weekDay_, startHour_, duration_, type_);
    this->classes.push_back(currentPeriod);
    return true;
}

/**
 * @brief Retrieves the current order type for students within this course class.
 *
 * This function returns an integer value indicating the current order type for students within the course class:
 *
 * - 1: Order by student ID.
 * - 2: Order alphabetically.
 * @note Complexity O(1)
 *
 * @return An integer value representing the current order type for students within the course class.
 */
int CourseClass::getCurrentOrder() const {
    return this->currentOrderOfStudents;
}

/**
 * @brief Set the current order type for students within this course class.
 *
 * This function allows setting the current order type for students within the course class. The order type can be:
 *
 * - 1: Order by student ID.
 * - 2: Order alphabetically.
 * @note Complexity O(1)
 *
 * @param orderType An integer value indicating the desired order type (1 for student ID, 2 for alphabetical order).
 */
void CourseClass::setCurrentOrder(int orderType) {
    this->currentOrderOfStudents = orderType;
}

/**
 * Get the maximum occupancy limit for this class.
 *
 * This method returns the maximum number of students that can be enrolled in this class.
 * @note Complexity O(1)
 *
 * @return The maximum occupancy limit of the class.
 */
int CourseClass::getClassLimit() const {
    return this->classLimitOccupancy;
}
