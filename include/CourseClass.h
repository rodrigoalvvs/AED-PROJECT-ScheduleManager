//
// Created by admin1 on 14-10-2023.
//

#ifndef AED_PROJ_COURSECLASS_H
#define AED_PROJ_COURSECLASS_H


#include <vector>
#include <memory>
#include <list>
#include "Period.h"
#include "Student.h"



/**
 * @class CourseClass
 * @brief Represents a class within a course unit.
 */
class CourseClass {
private:
    std::string classId;                  ///< The identifier for the class.
    std::vector<std::shared_ptr<Period>> classes;  ///< A list of time periods for the class.
    std::vector<int> students;            ///< A list of student IDs enrolled in the class.
    int currentOrderOfStudents;          ///< The current order of students in the class.
    int classLimitOccupancy = 30;        ///< The maximum occupancy limit for the class.

public:
    // Constructors and destructors
    CourseClass(const std::string& classId_);

    // Class getters and setters
    const std::string& getClassId() const;
    int getStudentCount() const;
    int getClassesCountPerWeek() const;
    int getCurrentOrder() const;
    int getClassLimit() const;

    void setCurrentOrder(int orderType);



    // Class member functions
    bool addPeriod(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_);
    bool addStudent(int studentCode);
    const std::vector<std::shared_ptr<Period>>& getClasses();
    std::shared_ptr<std::vector<int>> getStudents();
    bool removeStudent(int studentId);


};


#endif //AED_PROJ_COURSECLASS_H
