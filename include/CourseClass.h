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


class CourseClass {
private:
    std::string classId;
    std::vector<std::shared_ptr<Period>> classes;
    std::vector<int> students;
    int currentOrderOfStudents;
    int classLimitOccupancy = 30;

public:
    // Constructors and destructors
    CourseClass(const std::string& classId_);

    // Class getters and setters
    const std::string& getClassId() const;
    int getStudentCount() const;
    int getClassesPerWeek() const;
    int getCurrentOrder() const;

    void setCurrentOrder(int orderType);



    // Class member functions
    bool addPeriod(const std::string& weekDay_, float startHour_, float duration_, const std::string& type_);
    bool addStudent(int studentCode);
    const std::vector<std::shared_ptr<Period>>& getClasses();
    std::shared_ptr<std::vector<int>> getStudents();
    bool removeStudent(int studentId);


};


#endif //AED_PROJ_COURSECLASS_H
