//
// Created by admin1 on 19-10-2023.
//

#ifndef AED_PROJ_COURSEUNIT_H
#define AED_PROJ_COURSEUNIT_H

#include <unordered_map>
#include <string>
#include <memory>
#include <list>
#include "CourseClass.h"
class CourseClass;
/**
 * @class CourseUnit
 * @brief Represents a unit course that contains classes and enrolled students.
 */
class CourseUnit{
private:
    std::unordered_map<std::string, std::shared_ptr<CourseClass>> classes; ///< Map of class IDs to class objects.
    std::vector<int> allStudents; ///< Vector of student IDs enrolled in the unit course.
    int currentOrderOfStudents; ///< The current order of students.
    int studentCount; ///< The total count of students enrolled in the unit course.

public:
    // Constructors and destructors
    CourseUnit();

    // Class getters and setters

    int getNumberOfClasses() const;
    int getCurrentOrder() const;
    int getUnitYear() const;

    void setCurrentOrder(int orderType);
    std::list<std::shared_ptr<CourseClass>> getClasses();


    // Class member functions
    // classes handle functions
    bool addClass(const std::string& classId);
    int getStudentCountOnClass(const std::string& classId);
    std::shared_ptr<CourseClass> getClass(const std::string& classId);
    const std::vector<std::shared_ptr<Period>>& getClassPeriods( const std::string& classId);
    std::shared_ptr<std::vector<int>> getStudentListOnClass(const std::string& classId);

    // Student handle functions
    bool addStudent(const std::string& classId, int studentId);
    int getStudentCount() const;
    std::shared_ptr<std::vector<int>> getStudentList();

    bool removeStudentFromClass(const std::string& classId, int studentId);
    std::string getClassWithVacancy() const;

    int getClassOccupancy(const std::string& classId) const;

    int getOccupancy() const;


};

#endif //AED_PROJ_COURSEUNIT_H
