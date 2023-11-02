//
// Created by admin1 on 14-10-2023.
//

#include <memory>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <set>
#include <queue>
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
        // Ignore if it's not comma separated
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


        // Find the student in the set with the same id
        auto studentsItr = std::find_if(this->students.begin(), this->students.end(), [studentId](const std::pair<int, std::shared_ptr<Student>>& studentRegistered) -> bool {
            return studentRegistered.first == studentId;
        });

        // [Add student object] If the student is not in students already, add it
        if(studentsItr == this->students.end()){
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
    // Unordered_map containing as keys <"ucId/classId", Period>
    std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule;

    // Get student object
    if(this->students.count(id) == 0){
        std::cout << "Student Not Found.\n";
        return;
    }
    std::shared_ptr<Student> currentStudent = this->students[id];

    std::cout << "Schedule for student " << currentStudent->getName() << " with student ID: " << id << std::endl;

    // Get units which the student is enrolled
    std::vector<std::string> units = currentStudent->getUnitCourses();

    for(const std::string& unitId: units){
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


void CourseManager::orderList(std::shared_ptr<std::vector<int>> studentsId, int orderType) {
    if(orderType == 1){
        // Sort the students by id
        std::sort(studentsId->begin(), studentsId->end());
    }
    else if(orderType == 2){
        std::sort(studentsId->begin(), studentsId->end(),[this](int a, int b) -> bool {
            return this->students[a]->getName() < this->students[b]->getName();
        });
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

void CourseManager::showStudentListInCourse(const std::string &courseUnit, int orderType,int firstN) {
    if(this->units.count(courseUnit) == 0){
        std::cout << "Course Unit does not exist!\n";
        return;
    }

    std::cout << "Student list for unit " << courseUnit << std::endl;
    std::shared_ptr<std::vector<int>> studentsId = this->units[courseUnit]->getStudentList();


    if(this->units[courseUnit]->getCurrentOrder() != orderType){
        this->orderList(studentsId, orderType);
        this->units[courseUnit]->setCurrentOrder(orderType);
    }

    int i = 0;
    for(auto studentIdPtr = studentsId->begin(); studentIdPtr != studentsId->end() &&  (firstN == -1 || i < firstN); studentIdPtr++){
        i++;
        std::cout << students[*studentIdPtr]->getName() << " - up" << *studentIdPtr <<  std::endl;
    }
}




/**
 * @brief Show a list of students in a specific class of a course unit.
 *
 * This function displays a list of students who are enrolled in a particular class of a course unit.
 *
 * @param courseUnit The name of the course unit.
 * @param classId The ID of the class for which you want to list students.
 * @param orderType The sorting order for the list (1 for by student ID, 2 for by student name).
 * @param firstN The maximum number of students to display. Use -1 to display all students.
 *
 * @note The students are sorted based on the specified sorting order and then displayed.
 * @note If the course unit or class does not exist, appropriate error messages are displayed.
 *
 * */

void CourseManager::showStudentListInClass(const std::string &courseUnit, const std::string& classId, int orderType,int firstN) {

    // Error handling
    if(this->units.count(courseUnit) == 0){
        std::cout << "Course Unit does not exist!\n";
        return;
    }
    if(this->units[courseUnit]->getClass(classId) == nullptr){
        std::cout << "Class does not exist!\n";
        return;
    }

    // Get students vector
    std::shared_ptr<std::vector<int>> studentsVect = this->units[courseUnit]->getStudentListOnClass(classId);


    if(this->units[courseUnit]->getCurrentOrder() != orderType){
        this->orderList(studentsVect, orderType);
        this->units[courseUnit]->setCurrentOrder(orderType);
    }

    std::cout << "Students in uc " << courseUnit << " class " << classId << " ";
    if(firstN != -1) std::cout << "(Showing the first " << firstN << " students)";
    std::cout << std::endl;

    // Print students
    int i = 0;
    for(auto studentsItr = studentsVect->begin(); studentsItr != studentsVect->end() && (i < firstN || firstN == -1); studentsItr++){
        std::cout << this->students[*studentsItr]->getName() << " - up" << *studentsItr <<  std::endl;
    }
}


std::vector<int> CourseManager::getStudentListInYear(int year, int orderType) {
    std::vector<int> studentsId;
    std::set<int> studentTracker;

    for(std::pair<std::string, std::shared_ptr<CourseUnit>> unitPair: this->units){
        std::shared_ptr<CourseUnit> currentUnit = unitPair.second;
        if(year == currentUnit->getUnitYear()){
            std::shared_ptr<std::vector<int>> studentsEnrolled = currentUnit->getStudentList();
            for(int student: *studentsEnrolled){
                if(studentTracker.insert(student).second){
                    studentsId.push_back(student);
                }

            }
        }
    }

    if(orderType == 1){
        std::sort(studentsId.begin(), studentsId.end());
    }
    else if (orderType == 2) {
        std::sort(studentsId.begin(), studentsId.end(), [this](int a, int b) -> bool{
            return this->students[a]->getName() < this->students[b]->getName();
        });
    }
    return studentsId;
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

void CourseManager::showStudentListInYear(int year, int orderType,int firstN){
    std::vector<int> studentsId = this->getStudentListInYear(year, orderType);

    std::cout << "The following students are registered in year " << year << " ";
    if(firstN != -1) std::cout << "(Showing the first " << firstN << " students)";
    std::cout << std::endl;


    int i = 0;
    for(auto studentPtr = studentsId.begin(); studentPtr != studentsId.end() && (i < firstN || firstN == -1) ; studentPtr++){
        i++;
        std::cout << this->students[*studentPtr]->getName() << " - up" << *studentPtr <<  std::endl;
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



/**
 * @brief Display a list of Unit Courses with the most students.
 *
 * This function retrieves the student count for each Unit Course,
 * identifies the top N Unit Courses with the most students, and displays their information.
 *
 * @param firstN The number of top Unit Courses to display. The default value is 5.
 */

void CourseManager::showUnitCoursesWithMostStudents(int firstN){
    std::vector<std::pair<std::string, int>> count;

    for(std::pair<std::string, std::shared_ptr<CourseUnit>> unit: this->units){
        count.emplace_back(unit.first, unit.second->getStudentCount());
    }

    std::cout << "The top " << firstN << " uc's with the most students are: " << std::endl;
    std::sort(count.begin(), count.end(), [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) -> bool{
        return a.second < b.second;
    });

    for(int i = 1; i <= firstN; i++){
        std::cout << "Position "  << i <<  "/ UC " << count.at(count.size() - i).first << " with " << count.at(count.size() - i).second << " students" << std::endl;
    }
}


/**
 * @brief Removes a student from a specific unit course.
 *
 * This function removes a student from a unit course, provided that the student is currently enrolled in the specified unit course.
 *
 * @param ucId The unique identifier of the unit course.
 * @param studentId The unique identifier of the student to remove.
 *
 * @return true if the student was successfully removed from the unit course, false otherwise.
 */
bool CourseManager::removeStudentFromUc(const std::string &ucId, int studentId, bool saveToChanges) {
    if(!this->students[studentId]->checkEnrollment(ucId)){
        std::cout << "Student is not enrolled in this unit!\n";
        return false;
    }
    std::string formerClass = this->students[studentId]->getClass(ucId);
    if(this->units[ucId]->removeStudentFromClass(this->students[studentId]->getClass(ucId), studentId)){
        this->students[studentId]->removeClass(ucId);
        this->removeFromDatabase(studentId, ucId);
        if(saveToChanges) this->saveToChanges(studentId, 1, {"", ""}, {ucId, formerClass});
        return true;
    }
    return false;
}




/**
 * @brief Adds a student to a specific unit course and class.
 *
 * This function adds a student to a unit course and class, provided that the student is not already enrolled in the unit course
 * and there is no time overlap between the new class and the student's existing classes.
 *
 * @param ucId The unique identifier of the unit course.
 * @param classId The unique identifier of the class.
 * @param studentId The unique identifier of the student.
 *
 * @return true if the student was successfully added to the unit course and class, false otherwise.
 */
bool CourseManager::addStudentToUc(const std::string &ucId, const std::string &classId, int studentId, bool isChange, bool saveToChanges) {
    if(this->students[studentId]->checkEnrollment(ucId) && !isChange){
        std::cout << "Student already registered in this unit!\n";
        return false;
    }

    if(this->students[studentId]->getClasses()->size() == 7){
        std::cout << "Student already registered in 7 UC'S.\n";
        return false;
    }


    // Get new classes
    if(this->units.find(ucId) == this->units.end()){
        std::cout << "Uc does not exist!\n";
        return false;
    }
    std::vector<std::shared_ptr<Period>> newClasses = this->units[ucId]->getClass(classId)->getClasses();

    // Get classes that student is enrolled
    std::shared_ptr<std::unordered_map<std::string, std::string>> classesEnrolled = this->students[studentId]->getClasses();
    this->students[studentId]->addClass(ucId, classId);
    this->units[ucId]->addStudent(classId, studentId);

    // studentId, studentName, UcCode, ClassCode (Adding e removing - operation types (1 for adding, 2 for removing))
    this->saveToDatabase(studentId, this->students[studentId]->getName(), ucId, classId);
    if(saveToChanges) this->saveToChanges(studentId, 2, {ucId, classId},{"", ""});
    return true;
}


/**
 * @brief Checks for time overlap between two sets of class periods.
 *
 * This function checks for time overlap between two sets of class periods (classesA and classesB).
 *
 * @param classesA A vector of shared pointers to class periods from the first set.
 * @param classesB A vector of shared pointers to class periods from the second set.
 *
 * @return true if there is a time overlap between the two sets of class periods, false otherwise.
 */
bool CourseManager::checkOverlap(const std::vector<std::shared_ptr<Period>>& classesA,
                                 const std::vector<std::shared_ptr<Period>>& classesB) {
    for(std::shared_ptr<Period> classA: classesA){
        for(std::shared_ptr<Period> classB: classesB){
            if(classA->overlaps(classB) && (((classA->getPeriodType() == "TP" || classA->getPeriodType() == "PL") && classB->getPeriodType() == "TP" || classB->getPeriodType() == "PL"))) return true;
        }
    }
    return false;
}

bool CourseManager::switchUc(int studentId, const std::string &ucIdRegistered, const std::string &ucIdToRegister, bool saveToChanges) {
    // Check if student is enrolled in the uc given
    if(!this->students[studentId]->checkEnrollment(ucIdRegistered)){
        std::cout << "Student is not enrolled in the given uc!\n";
        return false;
    }

    // Student cannot be in more than 7 ucs
    if(this->students[studentId]->getNumberOfClassesRegistered() == 7){
        std::cout << "Student is already registered in 7 UC's\n";
        return false;
    }

    // There must be a vacancy in a class in the new UC, find first available
    std::string classIdWithVacancy = this->units[ucIdToRegister]->getClassWithVacancy();

    if(classIdWithVacancy.empty()){
        std::cout << "The given Uc has no vacancy.\n";
        return false;
    }

    std::string classIdRegistered = this->students[studentId]->getClass(ucIdRegistered);
    this->removeStudentFromUc(ucIdRegistered, studentId, false);

    if(this->doStudentClassesOverlap(this->units[ucIdToRegister]->getClass(classIdWithVacancy)->getClasses(),this->getStudentSchedule(studentId))){
        std::cout << "Classes schedules overlap.\n";
        this->addStudentToUc(ucIdRegistered, classIdRegistered,studentId, false, false);
        return false;
    }

    this->addStudentToUc(ucIdToRegister, classIdWithVacancy, studentId, true, false);
    this->removeFromDatabase(studentId, ucIdRegistered);
    if(saveToChanges) this->saveToChanges(studentId, 3, {ucIdToRegister, classIdWithVacancy}, {ucIdRegistered, classIdRegistered});
    return true;
}


// BUG WITH CLASS OVERLAP (10h30 - 12h30; 10h30 - 12h00)
bool CourseManager::doStudentClassesOverlap(const std::vector<std::shared_ptr<Period>>& newClasses, const std::vector<std::shared_ptr<Period>>& classesEnrolled) {

    // Check if overlap occurs
    if(this->checkOverlap(newClasses, classesEnrolled)){
        std::cout << "Overlaping hours. Couldn't add student to uc!\n";
        return true;
    }
    return false;
}

bool CourseManager::switchClass(int studentId, const std::string &ucIdRegistered, const std::string &classRegistered, const std::string &classToRegister, bool saveToChanges) {

    // Check for class cap

    if(this->units[ucIdRegistered]->getClass(classToRegister)->getStudentCount() == this->units[ucIdRegistered]->getClass(classToRegister)->getClassLimit()){
        std::cout << "Class is already full!\n";
        return false;
    }


    // Check class balance
    if(std::abs(this->units[ucIdRegistered]->getClassOccupancy(classToRegister) -
                this->units[ucIdRegistered]->getClassOccupancy(classRegistered)) > 4){
        std::cout << "A class change will unbalance the class occupation!\n";
        return false;
    }

    // Check schedule overlap
    this->removeStudentFromUc(ucIdRegistered, studentId, false);
    if(this->doStudentClassesOverlap(this->units[ucIdRegistered]->getClassPeriods(classRegistered), this->getStudentSchedule(studentId))){

        std::cout << "Classes overlap with student schedule.\n";
        this->addStudentToUc(ucIdRegistered,classRegistered, studentId, true, false);
        return false;
    }

    this->removeFromDatabase(studentId, ucIdRegistered);
    this->addStudentToUc(ucIdRegistered, classToRegister, studentId, true, false);
    if(saveToChanges) this->saveToChanges(studentId, 4, {ucIdRegistered, classToRegister} , {ucIdRegistered, classRegistered});
    return true;
}

std::vector<std::shared_ptr<Period>> CourseManager::getStudentSchedule(int studentId) {
    std::vector<std::shared_ptr<Period>> result;
    result.reserve(this->students[studentId]->getNumberOfClassesRegistered());
    // Pair uc/class
    for(std::pair<std::string, std::string> classPair: *this->students[studentId]->getClasses()){
        for(const std::shared_ptr<Period>& period: this->units[classPair.first]->getClassPeriods(classPair.second)){
            result.push_back(period);
        }
    }
    return result;
}

bool CourseManager::addRequest(short requestType,int studentId_, const std::pair<std::string, std::string>& adding, const std::pair<std::string, std::string>& removing) {
    this->requests.emplace(requestType, studentId_, adding, removing);
    return true;
}

// This function handles oldest request
void CourseManager::handleRequest() {
    if(this->requests.empty()){
        std::cout << "There are no request to handle!\n";
        return;
    }

    Request requestToHandle = this->requests.front();
    switch(requestToHandle.requestType){
        case 1:
            this->addStudentToUc(requestToHandle.adding.first, requestToHandle.adding.second, requestToHandle.studentId);
            break;
        case 2:
            this->removeStudentFromUc(requestToHandle.removing.first, requestToHandle.studentId);
            break;
        case 3:
            this->switchUc(requestToHandle.studentId, requestToHandle.removing.first, requestToHandle.adding.first);
            break;
        case 4:
            this->switchClass(requestToHandle.studentId, requestToHandle.removing.first, requestToHandle.removing.second, requestToHandle.adding.second);
            break;
        default:
            std::cout << "Invalid request type!\n";
            return;
    }
    this->requests.pop();
}

void CourseManager::saveToDatabase(int studentId, const std::string &studentName, const std::string &ucId, const std::string &classId) {
    // FUNCTION TO ADD A LINE TO THE DATABASE
    std::ofstream out("../data/students_classes.csv", std::ios::app);
    out << studentId << "," << studentName << "," << ucId << "," << classId << std::endl;
}

void CourseManager::removeFromDatabase(int studentId, const std::string &ucId) {
    std::ifstream in("../data/students_classes.csv");
    std::ofstream out("../data/students_classes_temp.csv");
    std::string line;

    while(std::getline(in, line)){
        std::string currentStudentId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string studentName = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string unitId = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string classCode = line.substr(0, line.find(','));

        if(!(std::to_string(studentId) == currentStudentId && unitId == ucId)){
            out << currentStudentId << "," << studentName << "," << unitId << "," << classCode << std::endl;
        }
    }

    remove("../data/students_classes.csv");
    rename("../data/students_classes_temp.csv", "../data/students_classes.csv");

}

bool CourseManager::showClassOccupancy(int orderType) {
    auto cmp = [orderType](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) -> bool{
        if(orderType == 1) return a.first <= b.first;
        else return a.first >= b.first;
    };

    std::set<std::pair<int, std::string>, decltype(cmp)> classes_(cmp);

    for(std::pair<std::string, std::shared_ptr<CourseUnit>> ucPair: this->units){
        for(const std::shared_ptr<CourseClass>& class_: ucPair.second->getClasses()){
            classes_.emplace(class_->getStudentCount(), ucPair.first + "/" + class_->getClassId());
        }
    }
    for(const std::pair<int, std::string>& pair: classes_){
        std::cout << pair.second << " - " << pair.first << " students\n";
    }

    return false;
}

bool CourseManager::showYearOccupancy(int orderType) {
    // pair<COUNT, YEAR> and specific lambda function to sort
    auto cmp = [orderType](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool{
        if(orderType == 1) return a.first <= b.first;
        else return a.first >= b.first;
    };
    std::set<std::pair<int, int>, decltype(cmp)> yearlyCount(cmp);


    for(std::pair<std::string, std::shared_ptr<CourseUnit>> unitPair: this->units){
        bool yearAccountFor = false;
        for(std::pair<int,int> countYearPair: yearlyCount){
            if(countYearPair.second == unitPair.second->getUnitYear())
                yearAccountFor = true;
        }
        if(!yearAccountFor){
            yearlyCount.emplace(this->getStudentListInYear(unitPair.second->getUnitYear(), 1).size(), unitPair.second->getUnitYear());
        }
    }

    for(std::pair<int, int> yearPair: yearlyCount){
        std::cout << "Year "<< yearPair.second << " has a total of " << yearPair.first << " students.\n";
    }
    return false;
}

bool CourseManager::showUcOccupancy(int orderType) {
    auto cmp = [orderType](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) -> bool{
        if(orderType == 1) return a.first <= b.first;
        else return a.first >= b.first;
    };
    std::set<std::pair<int, std::string>, decltype(cmp)> ucCount(cmp);

    for(std::pair<std::string, std::shared_ptr<CourseUnit>> ucPair: this->units){
        ucCount.emplace(ucPair.second->getStudentCount(), ucPair.first);
    }
    for(const std::pair<int, std::string>& ucCount_: ucCount){
        std::cout << "Uc " << ucCount_.second << " has a total of " << ucCount_.first << " students\n";
    }

    return false;
}

void CourseManager::saveToChanges(int studentId, int operationType, const std::pair<std::string, std::string>& adding,const std::pair<std::string, std::string>& removing) const {
    std::ofstream out("../data/changes.csv", std::ios::app);
    out << studentId << "," << operationType << "," << adding.first << "/" << adding.second << "," << removing.first << "/" << removing.second << std::endl;
}



Request::Request(short requestType_, int studentId_, const std::pair<std::string, std::string> &adding_,const std::pair<std::string, std::string> &removing_) {
    this->requestType = requestType_;
    this->studentId = studentId_;
    this->adding = adding_;
    this->removing = removing_;
}



