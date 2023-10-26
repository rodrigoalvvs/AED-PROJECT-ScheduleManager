//
// Created by admin1 on 14-10-2023.
//

#include <memory>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <set>
#include "../include/CourseManager.h"

/**
 * This is the constructor that handles all information on the system.
 */

CourseManager::CourseManager() {
    this->getClassesPerUc();
    this->getClasses();
    this->getStudentsClasses();
}



/**
 * This is a function that gets information about course classes from a file.
 * @return void.
 */

void CourseManager::getClasses() {
    std::ifstream in_class("../data/classes.csv");
    std::string line;
    std::getline(in_class, line);

    while(std::getline(in_class, line)){
        // Ignore line if it not comma separated
        if(line.find(',') == std::string::npos) continue;
        // Remove additional literals
        if(line.find('\r') != std::string::npos) line.pop_back();
        
        // Get classID
        std::string classId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);
        
        // Get unitId
        std::string unitId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);
        
        // Get classes's weekDay, startHour, duration and type
        std::string weekDay = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        float startHour = std::stof(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        float duration = std::stof(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string type = line.substr(0, line.find(','));
        
        // Get current class and add a period to it
        std::shared_ptr<CourseClass> courseClass = this->units[unitId]->getClass(classId);
        courseClass->addPeriod(weekDay, startHour, duration, type);

    }
}


/**
 * This is a function that gets the list of classes per course unit.
 * @return void.
 */
void CourseManager::getClassesPerUc() {
    std::ifstream in_uc("../data/classes_per_uc.csv");
    std::string line;
    std::getline(in_uc, line);

    while(std::getline(in_uc, line)){
        // If line is not comma separated then it should be avoided
        if(line.find(',') == std::string::npos) continue;
        // If line has non-important literals then it should be removed
        if(line.find('\r') != std::string::npos) line.pop_back();

        // Get unit id
        std::string unitId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);
        
        // Get class id
        std::string classId = line.substr(0, line.size());

        // Try to find the unit
        auto itr = this->units.find(unitId);
        
        // Course Unit doesn't exist, so it must be created
        if(itr == this->units.end()){
            // Create the Course Unit and insert it into the units
            std::shared_ptr<CourseUnit> currentUnit = std::make_shared<CourseUnit>(CourseUnit());
            this->units.insert(std::make_pair(unitId, currentUnit));
            
            // Add class to unit
            currentUnit->addClass(classId);
        }
        // Course Unit exists
        else{
            // Add class to unit
            this->units[unitId]->addClass(classId);
        }
    }
}



/**
 * This is a function that gets information about the student's classes.
 * @return void.
 */
void CourseManager::getStudentsClasses() {
    std::ifstream in("../data/students_classes.csv");
    std::string line;
    std::getline(in, line);

    while(std::getline(in, line)){
        // Ignore if its not comma separated
        if(line.find(',') == std::string::npos) continue;
        // Remove additional literals
        if(line.find('\r') != std::string::npos) line.pop_back();

        // Get student ID
        int studentId = std::stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        // Get student name
        std::string studentName = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        // Get unit that student enrolled
        std::string unitId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        // Get class that student enrolled
        std::string classId = line.substr(0, line.find(','));

        // [Add reference to student in class] Add student to class
        this->units[unitId]->addStudent(classId, studentId);


        // [Add student object] If the student is not in students already, add it
        if(this->students.count(studentId) == 0){
            // Create a student
            std::shared_ptr<Student> currentStudent = std::make_shared<Student>(Student(studentName, studentId));

            // Add class which student is registered
            currentStudent->addClass(unitId, classId);

            // Add student to local map
            students.insert(std::make_pair(studentId, currentStudent));
        }
        else{
            // Just add class to student already registered
            students[studentId]->addClass(unitId, classId);
        }
    }
}



void CourseManager::showStudentSchedule(int id) {
    // Init schedule
    // Unordered_map containing as keys <"ucId/classId", Period>
    std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule;

    // Get student object
    if(this->students.count(id) == 0){
        std::cout << "Student Not Found, Invalid identifier\n";
        return;
    }
    std::shared_ptr<Student> currentStudent = this->students[id];

    std::cout << "Schedule for student " << currentStudent->getName() << " with student ID: " << id << std::endl;

    // Get units which the student is enrolled
    std::vector<std::string> units = currentStudent->getUnitCourses();

    for(std::string unitId: units){
        // Get classId that the student is registered in each unit
        std::string classId = currentStudent->getClass(unitId);

        // Fetch class object
        std::shared_ptr<CourseClass> classPtr = this->units[unitId]->getClass(classId);
        for(std::shared_ptr<Period> period: classPtr->getClasses()){
            std::string key = unitId + "/" + classPtr->getClassId();
            schedule[key].push_back(period);

        }
    }

    this->printSchedule(schedule);

}


/**
 * @brief Display the schedule for a specific class in a course unit.
 *
 * This function displays the schedule for a specific class in a course unit identified by 'ucId' and 'classId'.
 *
 * @param ucId The unique identifier of the course unit.
 * @param classId The unique identifier of the class within the course unit.
 */

void CourseManager::showClassSchedule(const std::string &ucId, const std::string &classId) {
    std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule;

    if(this->units.count(ucId) == 0){
        std::cout << "The class id is not valid!";
        return;
    }



    for(std::shared_ptr<Period> period: this->units[ucId]->getClassPeriods(classId)){
        std::string key = ucId;
        key.append("/");
        key.append(classId);
        schedule[key].push_back(period);
    }

    std::cout << "\nUnit: " << ucId << "/" << "Class: " << classId<< std::endl;
    this->printSchedule(schedule);
}



/**
 * @brief Compare two pairs of <string, shared_ptr<Period>> by their start hours.
 *
 * This function is a custom comparison function for sorting pairs of <string, shared_ptr<Period>> by
 * their start hours in ascending order.
 *
 * @param a The first pair to compare.
 * @param b The second pair to compare.
 * @return true if the start hour of 'a' is less than the start hour of 'b', false otherwise.
 */
bool cmpHours(const std::pair<std::string,std::shared_ptr<Period>>& a, const std::pair<std::string,std::shared_ptr<Period>>& b){
    if(a.second->getStartTime().hour == b.second->getStartTime().hour){
        return a.second->getStartTime().minute < b.second->getStartTime().minute;
    }
    return a.second->getStartTime().hour < b.second->getStartTime().hour;
}

/**
 * @brief Print the schedule of course periods for each weekday.
 *
 * This function prints the schedule of course periods for each weekday. It takes an unordered_map
 * containing course periods, organizes them by weekday, and then sorts and displays the schedule
 * for each weekday.
 *
 * @param schedule An unordered_map containing course periods with keys as "<ucId/classId>" and values as shared_ptr<Period>.
 */

void CourseManager::printSchedule(std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule) {
    std::vector<std::string> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for(const std::string& dayOfWeek: weekDays){
        std::cout << dayOfWeek << std::endl;

        std::vector<std::pair<std::string, std::shared_ptr<Period>>> dailySchedule;

        for(std::pair<std::string, std::vector<std::shared_ptr<Period>>> periodList: schedule){
            for(const std::shared_ptr<Period>& period: periodList.second){
                if(period->getWeekDay() == dayOfWeek){
                    dailySchedule.emplace_back(periodList.first, period);
                }
            }
        }

        std::sort(dailySchedule.begin(), dailySchedule.end(), cmpHours);

        for(const std::pair<std::string, std::shared_ptr<Period>>& period: dailySchedule){

            std::cout << period.first << " - " << std::fixed << std::setw(2) << std::setfill('0') << period.second->getStartTime().hour << "h"  << std::setw(2) << std::setfill('0') << period.second->getStartTime().minute << " " << std::setw(2) << std::setfill('0') << period.second->getEndTime().hour << "h" << std::setw(2)<< period.second->getEndTime().minute << " " << period.second->getPeriodType() << std::endl;
        }
        dailySchedule.clear();
    }
}


/**
 * @brief Show a list of students registered in a specific course unit.
 *
 * This function displays a list of students who are registered in the specified course unit.
 * It first checks if the course unit exists, and if it does, it lists the students along
 * with their names and student IDs. You can limit the number of students displayed by
 * providing the 'firstN' parameter.
 *
 * @param courseUnit The ID of the course unit for which you want to list registered students.
 * @param firstN The maximum number of students to display (use -1 to display all).
 */

void CourseManager::showStudentListInCourse(const std::string &courseUnit, int firstN) {
    if(this->units.count(courseUnit) == 0){
        std::cout << "Course Unit does not exist!\n";
        return;
    }
    std::cout << "Student list for unit " << courseUnit << std::endl;
    std::shared_ptr<std::list<int>> studentsId = this->units[courseUnit]->getStudentList();
    int i = 0;
    for(auto studentIdPtr = studentsId->begin(); studentIdPtr != studentsId->end() &&  (firstN == -1 || i < firstN); studentIdPtr++){
        i++;
        std::cout << students[*studentIdPtr]->getName() << " - up" << *studentIdPtr <<  std::endl;
    }
}



/**
 * @brief Show a list of students registered in a specific class of a course unit.
 *
 * This function displays a list of students who are registered in a specific class
 * of the given course unit. It first checks if the course unit and class exist, and
 * if they do, it lists the students along with their names and student IDs.
 *
 * @param courseUnit The ID of the course unit to query.
 * @param classId The ID of the specific class within the course unit.
 */

void CourseManager::showStudentListInClass(const std::string &courseUnit, const std::string& classId) {
    if(this->units.count(courseUnit) == 0){
        std::cout << "Course Unit does not exist!\n";
        return;
    }
    if(this->units[courseUnit]->getClass(classId) == nullptr){
        std::cout << "Class does not exist!\n";
        return;
    }


    for(int studentId: this->units[courseUnit]->getClass(classId)->getStudents()){
        std::cout << students[studentId]->getName() << " - up" << studentId <<  std::endl;
    }
}




/**
 * @brief Show a list of students registered in a specific year.
 *
 * This function displays a list of students who are registered in the specified year.
 *
 * @param year The year for which you want to list registered students.
 * @param firstN The maximum number of students to display. Use -1 to display all students.
 *
 * @note The students are sorted in ascending order of their IDs.
 */

void CourseManager::showStudentListInYear(int year, int firstN){
    std::set<int> studentsId;

    for(std::pair<std::string, std::shared_ptr<CourseUnit>> unitPair: this->units){
        std::shared_ptr<CourseUnit> currentUnit = unitPair.second;
        if(year == currentUnit->getUnitYear()){
            std::shared_ptr<std::list<int>> studentsEnrolled = currentUnit->getStudentList();
            for(int student: *studentsEnrolled){
                studentsId.insert(student);
            }
        }
    }

    std::cout << "The following students are registered in year " << year << " ";
    if(firstN != -1) std::cout << "(Showing the first " << firstN << " students)";
    std::cout << std::endl;

    int i = 0;
    for(auto studentPtr = studentsId.begin(); studentPtr != studentsId.end() && (i < firstN || firstN == -1) ; studentPtr++){
        i++;
        std::cout << students[*studentPtr]->getName() << " - up" << *studentPtr <<  std::endl;
    }
}





/**
 * @brief Count the number of students registered in at least a specified number of course units.
 *
 * This function calculates and displays the count of students who are registered in at least
 * the specified number of course units. It iterates through the list of students and checks
 * if each student is registered in the required number of course units (or more).
 *
 * @param n The minimum number of course units a student must be registered in to be counted.
 */

void CourseManager::showStudentCountOnNUnits(int n) {
    int result = 0;

    for(std::pair<int, std::shared_ptr<Student>> student: this->students){
        if(student.second->getNumberOfClassesRegistered() >= n){
            result += 1;
        }
    }
    std::cout << result << " students are registered in atleast " << n << " UC's\n";
}


void CourseManager::showUnitCoursesWithMostStudents(int firstN){
    std::unordered_map<std::string, int> count;
    for(std::pair<std::string, std::shared_ptr<CourseUnit>> unit: this->units){
        count[unit.first] = unit.second->getStudentCount();
    }

    for(int i = 1; i <= firstN; i++){
        std::max_element(count.begin(), count.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {

        });
    }

    
}





