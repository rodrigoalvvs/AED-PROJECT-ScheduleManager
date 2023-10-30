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
#include <queue>
#include "Student.h"
#include "CourseUnit.h"
struct Request{
    short requestType; // 1 for add class, 2 for remove class, 3 for change uc, 4 for change class
    int studentId;
    std::pair<std::string, std::string> adding;
    std::pair<std::string, std::string> removing;

    Request(short requestType_,int studentId_, const std::pair<std::string, std::string>& adding_, const std::pair<std::string, std::string>& removing_);
};



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
    static void printSchedule(std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule);

    // Student list handler
    void showStudentListInCourse(const std::string& courseUnit, int orderType, int firstN = -1);
    void showStudentListInClass(const std::string &courseUnit, const std::string& classId, int orderType,int firstN = -1);
    void showStudentListInYear(int year, int orderType, int firstN = -1);
    void showUnitCoursesWithMostStudents(int firstN = 5);

    // Student count
    void showStudentCountOnNUnits(int n);

    bool removeStudentFromUc(const std::string& ucId, int studentId);
    bool addStudentToUc(const std::string& ucId, const std::string& classId, int studentId, bool isChange = false);
    std::vector<std::shared_ptr<Period>> getStudentSchedule(int studentId);

    void orderList(std::shared_ptr<std::vector<int>> studentsId, int orderType);
    bool switchUc(int studentId, const std::string& ucIdRegistered, const std::string& ucIdToRegister);
    bool switchClass(int studentId, const std::string& ucIdRegistered, const std::string& classRegistered, const std::string& classToRegister);
    bool doStudentClassesOverlap(const std::vector<std::shared_ptr<Period>>& newClasses, const std::vector<std::shared_ptr<Period>>& classesEnrolled);

    void handleRequest();
    bool addRequest(short requestType,int studentId_, const std::pair<std::string, std::string>& adding, const std::pair<std::string, std::string>& removing);

    void saveToDatabase(int studentId, const std::string& studentName, const std::string& ucId, const std::string& classId);
    void removeFromDatabase(int studentId, const std::string& ucId);
    static bool checkOverlap(const std::vector<std::shared_ptr<Period>>& classesA, const std::vector<std::shared_ptr<Period>>& classesB);


    bool showClassOccupancy(int);
    bool showYearOccupancy(int);
    bool showUcOccupancy(int);

    std::vector<int> getStudentListInYear(int year, int orderType);
};

#endif //AED_PROJ_COURSEMANAGER_H
