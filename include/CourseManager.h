//
// Created by admin1 on 14-10-2023.
//

#ifndef AED_PROJ_COURSEMANAGER_H
#define AED_PROJ_COURSEMANAGER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "Student.h"
#include "CourseUnit.h"


class CourseManager {
private:
    // Field for the courses {UcCode : CourseUnit}
    std::unordered_map<std::string, std::shared_ptr<CourseUnit>> units;

    // Field for the students {studentID : Student}
    std::unordered_map<int, std::shared_ptr<Student>> students;
public:

    // Constructors and destructors
    CourseManager();

    // Member functions
    void getClasses();
    void getStudentsClasses();
    void getClassesPerUc();

    void showStudentSchedule(int id);
    void showClassSchedule(const std::string& ucId, const std::string& classId);
    static void printSchedule(std::unordered_map<std::string, std::shared_ptr<Period>> schedule);
    void showStudentListInCourse(const std::string& courstseUnit);
    void showStudentListInClass(const std::string &courseUnit, const std::string& classId);
    void showStudentCountOnNUnits(int n);
};


#endif //AED_PROJ_COURSEMANAGER_H
