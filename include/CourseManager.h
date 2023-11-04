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
#include <stack>
#include <istream>
#include "Student.h"
#include "CourseUnit.h"
#include "Request.h"
class CourseClass;

/**
 * @class CourseManager
 * @brief Manages course units, students, and requests for course changes.
 */
class CourseManager {
private:
    // Field for the courses {UcCode : CourseUnit}
    std::unordered_map<std::string, std::shared_ptr<CourseUnit>> units; ///< Map of unit codes to unit objects.

    // Field for the students {studentID : Student}
    std::unordered_map<int, std::shared_ptr<Student>> students; ///< Map of student IDs to student objects.
    std::queue<Request> requests; ///< Queue for pending course change requests.
    std::stack<Request> history; ///< Stack for storing the history of processed requests.

public:

    // Constructors and destructors
    CourseManager();

    // Member functions
    void getClasses();
    void getStudentsClasses();
    void getClassesPerUc();

    // Schedule handler
    void showStudentSchedule(int id);
    void showClassSchedule(const std::string& ucId, const std::string& classId);
    static bool checkPeriodOverlap(const std::vector<std::shared_ptr<Period>>& classesA, const std::vector<std::shared_ptr<Period>>& classesB);
    static bool checkScheduleOverlap(const std::vector<std::shared_ptr<Period>>& newClasses, const std::vector<std::shared_ptr<Period>>& classesEnrolled);
    static void printSchedule(std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule);
    std::vector<std::shared_ptr<Period>> getStudentSchedule(int studentId);

    // Student list handler
    void showStudentListInCourse(const std::string& courseUnit, int orderType, int firstN = -1);
    void showStudentListInClass(const std::string &courseUnit, const std::string& classId, int orderType,int firstN = -1);
    void showStudentListInYear(int year, int orderType, int firstN = -1);
    void orderStudentsVector(std::shared_ptr<std::vector<int>> studentsId, int orderType);

    std::vector<int> getStudentListInYear(int year, int orderType);

    // Student count
    void showStudentCountOnNUnits(int n);
    void showUnitCoursesWithMostStudents(int firstN = -1);



    // Requests
    void handleRequests();
    bool addRequest(short requestType,int studentId_, const std::pair<std::string, std::string>& adding, const std::pair<std::string, std::string>& removing);
    bool removeStudentFromUc(const std::string& ucId, int studentId, bool saveToChanges = true);
    bool addStudentToUc(const std::string& ucId, const std::string& classId, int studentId, bool isChange = false, bool saveToChanges = true);
    bool switchUc(int studentId, const std::string& ucIdRegistered, const std::string& ucIdToRegister, bool saveToChanges = true);
    bool switchClass(int studentId, const std::string& ucIdRegistered, const std::string& classRegistered, const std::string& classToRegister, bool saveToChanges = true);


    // Updating database
    void saveToDatabase(int studentId, const std::string& studentName, const std::string& ucId, const std::string& classId);
    void removeFromDatabase(int studentId, const std::string& ucId);

    // Occupancy
    bool showClassOccupancy(int);
    bool showYearOccupancy(int);
    bool showUcOccupancy(int);


    // Changes functions
    void saveToChanges(int studentId,int operationType, const std::pair<std::string, std::string>& adding, const std::pair<std::string, std::string>& removing) const;

    void revertChanges();
    bool revertRequest(const Request& currentRequest);

};

#endif //AED_PROJ_COURSEMANAGER_H
