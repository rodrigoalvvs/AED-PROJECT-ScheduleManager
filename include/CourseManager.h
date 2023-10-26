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
#include "Request.h"


class CourseManager {
private:
    // Field for the courses {UcCode : CourseUnit}
    std::unordered_map<std::string, std::shared_ptr<CourseUnit>> units;

    // Field for the students {studentID : Student}
    std::unordered_map<int, std::shared_ptr<Student>> students;

    std::queue<Request> requests;
public:

    // Constructors and destructors
    CourseManager();

    // Member functions
    void getClasses();
    void getStudentsClasses();
    void getClassesPerUc();

    // Schedule handle
    void showStudentSchedule(int id);
    void showClassSchedule(const std::string& ucId, const std::string& classId);
    void printSchedule(std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule);

    // Student list handler
    void showStudentListInCourse(const std::string& courstseUnit, int firstN = -1);
    void showStudentListInClass(const std::string &courseUnit, const std::string& classId);
    void showStudentListInYear(int year, int firstN = -1);
    void showUnitCoursesWithMostStudents(int firstN = 5);

    // Student count
    void showStudentCountOnNUnits(int n);

};


#endif //AED_PROJ_COURSEMANAGER_H
