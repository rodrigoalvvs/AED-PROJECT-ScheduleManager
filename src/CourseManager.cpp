//
// Created by admin1 on 14-10-2023.
//

#include <memory>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "../include/CourseManager.h"

/**
 * This is the constructor that handles all information on the system.
 */

CourseManager::CourseManager() {
    this->getClassesPerUc();
    this->getClasses();
    this->getStudentsClasses();
    //this->showStudentSchedule(202028717);
    //this->showStudentListInCourse("L.EIC001");
    //this->showClassSchedule("L.EIC001", "1LEIC01");
    //this->showStudentListInClass("L.EIC001", "1LEIC01");
    this->showStudentCountOnNUnits(3);
    this->showStudentCountOnNUnits(7);
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
    std::unordered_map<std::string, std::shared_ptr<Period>> schedule;

    // Get student object
    if(this->students.count(id) == 0){
        std::cout << "Student Not Found, Invalid identifier\n";
        return;
    }
    std::shared_ptr<Student> currentStudent = this->students[id];

    std::cout << "Student for student " << currentStudent->getName() << " with student ID: " << id << std::endl;

    // Get units which the student is enrolled
    std::vector<std::string> units = currentStudent->getUnitCourses();

    for(std::string unitId: units){
        // Get classId that the student is registered in each unit
        std::string classId = currentStudent->getClass(unitId);

        // Fetch class object
        std::shared_ptr<CourseClass> classPtr = this->units[unitId]->getClass(classId);
        for(std::shared_ptr<Period> period: classPtr->getClasses()){
            schedule.insert(std::make_pair(unitId + "/" + classPtr->getClassId(), period));
        }
    }

    this->printSchedule(schedule);

}


void CourseManager::showClassSchedule(const std::string &ucId, const std::string &classId) {
    std::unordered_map<std::string, std::shared_ptr<Period>> schedule;

    if(this->units.count(ucId) == 0){
        std::cout << "The class id is not valid!";
        return;
    }
    for(std::shared_ptr<Period> period: this->units[ucId]->getClasses(classId)){
        schedule.insert(std::make_pair(ucId + "/" + classId, period));
    }

    std::cout << "\nUnit: " << ucId << "/" << "Class: " << classId<< std::endl;
    this->printSchedule(schedule);
}




bool cmp(const std::pair<std::string,std::shared_ptr<Period>>& a, const std::pair<std::string,std::shared_ptr<Period>>& b){
    return a.second->getStartHour() < b.second->getStartHour();
}

void CourseManager::printSchedule(std::unordered_map<std::string, std::shared_ptr<Period>> schedule) {
    std::vector<std::string> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for(std::string dayOfWeek: weekDays){
        std::cout << dayOfWeek << std::endl;

        std::vector<std::pair<std::string, std::shared_ptr<Period>>> dailySchedule;

        for(std::pair<std::string,std::shared_ptr<Period>> period: schedule){
            if(period.second->getWeekDay() == dayOfWeek){
                dailySchedule.push_back(std::make_pair(period.first, period.second));
            }
        }

        std::sort(dailySchedule.begin(), dailySchedule.end(), cmp);

        for(std::pair<std::string, std::shared_ptr<Period>> period: dailySchedule){
            int startHour = period.second->getStartHour();
            int startMinute = (period.second->getStartHour() - startHour) * 60;

            int endHour = period.second->getStartHour() + period.second->getDuration();
            int endMinute = (period.second->getStartHour() + period.second->getDuration() - endHour) * 60;

            std::cout << period.first << " - " << std::fixed << std::setw(2) << std::setfill('0') << startHour << "h"  << std::setw(2) << std::setfill('0') << startMinute << " " << std::setw(2) << std::setfill('0') << endHour << "h" << std::setw(2)<< endMinute << " " << period.second->getClassType() << std::endl;
        }
        dailySchedule.clear();
    }
}


void CourseManager::showStudentListInCourse(const std::string &courseUnit) {
    if(this->units.count(courseUnit) == 0){
        std::cout << "Course Unit does not exist!\n";
        return;
    }
    std::cout << "Student list for unit " << courseUnit << std::endl;
    std::shared_ptr<std::list<int>> studentsId = this->units[courseUnit]->getStudentList();
    for(int studentId: *studentsId){
        std::cout << students[studentId]->getName() << " - up" << studentId <<  std::endl;
    }
}


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

void CourseManager::showStudentCountOnNUnits(int n) {
    int result = 0;
    for(std::pair<int, std::shared_ptr<Student>> student: this->students){
        if(student.second->getNumberOfClassesRegistered() >= n){
            result += 1;
        }
    }
    std::cout << result << " students are registered in atleast " << n << " UC's\n";
}



