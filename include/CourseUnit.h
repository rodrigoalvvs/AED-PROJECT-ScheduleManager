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

class CourseUnit{
private:
    std::unordered_map<std::string, std::shared_ptr<CourseClass>> classes;

    std::vector<int> allStudents;
    int currentOrderOfStudents;
    int studentCount;
public:
    // Constructors and destructors
    CourseUnit();

    // Class getters and setters

    int getNumberOfClasses() const;
    int getCurrentOrder() const;
    int getUnitYear() const;

    void setCurrentOrder(int orderType);


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
};

#endif //AED_PROJ_COURSEUNIT_H
