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
 * @brief Read and parse class data from a CSV file and add class periods to CourseClass objects.
 *
 * This function reads class data from a CSV file, parses the data, and associates class periods with CourseClass objects.
 *
 * @note The CSV file is expected to have the following format:
 *       classId, unitId, weekDay, startHour, duration, type
 *       where:
 *       - classId is the unique identifier of the class.
 *       - unitId is the unique identifier of the course unit to which the class belongs.
 *       - weekDay is the day of the week on which the class period occurs.
 *       - startHour is the start hour of the class period.
 *       - duration is the duration of the class period.
 *       - type is the type of the class period (e.g., T, TP, PL).
 *
 * @note The function assumes that the CSV file is properly formatted, with comma-separated values for each class.
 *       Lines that are not comma-separated or contain additional literals are ignored.
 *
 * @return None.
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
 * @brief Read and parse class-per-course-unit data from a CSV file and create CourseUnits with associated classes.
 *
 * This function reads data from a CSV file containing class-per-course-unit information, parses the data, and creates CourseUnit objects with associated classes.

 * @note The CSV file is expected to have the following format:
 *       unitId, classId
 *       where:
 *       - unitId is the unique identifier of the course unit.
 *       - classId is the unique identifier of the class associated with the course unit.

 * @note The function assumes that the CSV file is properly formatted with comma-separated values for each entry. Lines that are not comma-separated or contain additional literals are ignored.

 * @return None.
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
 * @brief Read and parse student-class enrollment data from a CSV file and associate students with their enrolled classes.
 *
 * This function reads data from a CSV file containing student-class enrollment information, parses the data, and associates students with their enrolled classes.

 * @note The CSV file is expected to have the following format:
 *       studentId, studentName, unitId, classId
 *       where:
 *       - studentId is the unique identifier of the student.
 *       - studentName is the name of the student.
 *       - unitId is the unique identifier of the course unit to which the student is enrolled.
 *       - classId is the unique identifier of the class in which the student is enrolled.

 * @note The function assumes that the CSV file is properly formatted with comma-separated values for each entry. Lines that are not comma-separated or contain additional literals are ignored.

 * @return None.
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

/**
 * @brief Display the class schedule for a specific student.
 *
 * This function displays the class schedule for a specific student with the given student ID. It compiles the schedule by collecting class periods from the course units and classes in which the student is enrolled.
 * @param id The unique identifier of the student for whom the schedule is to be displayed.
 * @return None.
 */
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

    // Get units_ which the student is enrolled
    std::vector<std::string> units_ = currentStudent->getUnitCourses();

    for(const std::string& unitId: units_){
        // Get classId that the student is registered in each unit
        std::string classId = currentStudent->getClass(unitId);

        // Fetch class object
        std::shared_ptr<CourseClass> classPtr = this->units[unitId]->getClass(classId);
        for(const std::shared_ptr<Period>& period: classPtr->getClasses()){
            std::string key = unitId + "/" + classPtr->getClassId();
            schedule[key].push_back(period);

        }
    }

    printSchedule(schedule);

}


/**
 * @brief Display the class schedule for a specific course unit and class.
 *
 * This function displays the class schedule for a specific course unit and class, identified by their unique identifiers (ucId and classId).

 * @param ucId The unique identifier of the course unit for which the class schedule is to be displayed.
 * @param classId The unique identifier of the class for which the schedule is to be displayed.
 * @return None.
 */
void CourseManager::showClassSchedule(const std::string &ucId, const std::string &classId) {
    std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule;

    if(this->units.count(ucId) == 0){
        std::cout << "The class id is not valid!";
        return;
    }



    for(const std::shared_ptr<Period>& period: this->units[ucId]->getClassPeriods(classId)){
        std::string key = ucId;
        key.append("/");
        key.append(classId);
        schedule[key].push_back(period);
    }

    std::cout << "\nUnit: " << ucId << "/" << "Class: " << classId<< std::endl;
    printSchedule(schedule);
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
 * @brief Display the class schedule for a specific day of the week.
 *
 * This function displays the class schedule for a specific day of the week by sorting and formatting the provided schedule data.

 * @param schedule An unordered_map containing keys in the format "<unitId/classId>" and values as vectors of shared_ptr<Period> objects, representing the schedule for various classes.
 * @return None.
 */
void CourseManager::printSchedule(std::unordered_map<std::string, std::vector<std::shared_ptr<Period>>> schedule) {
    std::vector<std::string> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    for(const std::string& dayOfWeek: weekDays){


        std::vector<std::pair<std::string, std::shared_ptr<Period>>> dailySchedule;

        for(std::pair<std::string, std::vector<std::shared_ptr<Period>>> periodList: schedule){
            for(const std::shared_ptr<Period>& period: periodList.second){
                if(period->getWeekDay() == dayOfWeek){
                    dailySchedule.emplace_back(periodList.first, period);
                }
            }
        }

        std::sort(dailySchedule.begin(), dailySchedule.end(), cmpHours);
        if(dailySchedule.empty()) continue;
        std::cout << "\t" << dayOfWeek << std::endl;
        for(const std::pair<std::string, std::shared_ptr<Period>>& period: dailySchedule){

            std::cout << period.first << " - " << std::fixed << std::setw(2) << std::setfill('0') << period.second->getStartTime().hour << "h"  << std::setw(2) << std::setfill('0') << period.second->getStartTime().minute << " " << std::setw(2) << std::setfill('0') << period.second->getEndTime().hour << "h" << std::setw(2)<< period.second->getEndTime().minute << " " << period.second->getPeriodType() << std::endl;
        }
        dailySchedule.clear();
    }
}

/**
 * @brief Order a vector of student IDs based on the specified order type.
 *
 * This function orders a vector of student IDs either by their ID or alphabetically by their names
 * based on the specified order type.
 *
 * @param studentsId A shared pointer to a vector of student IDs to be ordered.
 * @param orderType An integer representing the order type:
 *                  - 1 for ordering by student ID.
 *                  - 2 for ordering alphabetically by student name.
 */
void CourseManager::orderStudentsVector(std::shared_ptr<std::vector<int>> studentsId, int orderType) {
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
        this->orderStudentsVector(studentsId, orderType);
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
        this->orderStudentsVector(studentsVect, orderType);
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

/**
 * @brief Get a list of student IDs enrolled in units of a specific year.
 *
 * This function retrieves a list of student IDs who are enrolled in course units of a specified year.
 * The list can be ordered either by student ID or alphabetically by student name based on the order type.
 *
 * @param year The year for which to retrieve the student list.
 * @param orderType An integer representing the order type:
 *                  - 1 for ordering by student ID.
 *                  - 2 for ordering alphabetically by student name.
 *
 * @return A vector of student IDs in the specified year.
 */
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

    std::cout << "The top uc's with the most students are: " << std::endl;
    std::sort(count.begin(), count.end(), [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) -> bool{
        return a.second <= b.second;
    });

    for(int i = 1; i <= firstN || (firstN == -1 && i < count.size()); i++){
        std::cout << "Position "  << i <<  " - " << count.at(count.size() - i).first << " with " << count.at(count.size() - i).second << " students" << std::endl;
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
        return false;
    }
    std::vector<std::shared_ptr<Period>> newClasses = this->units[ucId]->getClass(classId)->getClasses();

    // Get classes that student is enrolled
    std::vector<std::shared_ptr<Period>> classesEnrolled = this->getStudentSchedule(studentId);

    if(checkScheduleOverlap(newClasses, classesEnrolled)){
        std::cout << "Classes overlap with student schedule! Couldn't make the change";
        return false;
    }


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
bool CourseManager::checkPeriodOverlap(const std::vector<std::shared_ptr<Period>>& classesA,
                                       const std::vector<std::shared_ptr<Period>>& classesB) {
    for(std::shared_ptr<Period> classA: classesA){
        for(std::shared_ptr<Period> classB: classesB){
            bool classA_mandatory = classA->getPeriodType() == "PL" || classA->getPeriodType() == "TP";
            bool classB_mandatory = classB->getPeriodType() == "PL" || classB->getPeriodType() == "TP";
            if(classA->overlaps(classB) && classA_mandatory && classB_mandatory) return true;
        }
    }
    return false;
}

/**
 * @brief Switch a student's enrollment from one UC to another.
 *
 * This function allows a student to switch their enrollment from one UC to another within the system.
 *
 * @param studentId The ID of the student who wants to switch enrollment.
 * @param ucIdRegistered The UC in which the student is currently enrolled.
 * @param ucIdToRegister The target UC to which the student wants to switch enrollment.
 * @param saveToChanges Set to true to save the operation to the change log; false to skip saving.
 * @return True if the switch was successful, or false if the operation failed.
 */
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

    if(this->checkScheduleOverlap(this->units[ucIdToRegister]->getClass(classIdWithVacancy)->getClasses(),this->getStudentSchedule(studentId))){
        std::cout << "Classes schedules overlap.\n";
        this->addStudentToUc(ucIdRegistered, classIdRegistered,studentId, false, false);
        return false;
    }

    this->addStudentToUc(ucIdToRegister, classIdWithVacancy, studentId, true, false);
    this->removeFromDatabase(studentId, ucIdRegistered);
    if(saveToChanges) this->saveToChanges(studentId, 3, {ucIdToRegister, classIdWithVacancy}, {ucIdRegistered, classIdRegistered});
    return true;
}


/**
 * @brief Check for schedule overlap between new and enrolled classes.
 *
 * This function checks if there is a schedule overlap between a student's newly requested classes
 * (newClasses) and their already enrolled classes (classesEnrolled).
 *
 * @param newClasses A vector of newly requested class periods.
 * @param classesEnrolled A vector of class periods in which the student is already enrolled.
 * @return True if there is a schedule overlap, indicating that the student cannot be added to the new classes; otherwise, false.
 */
bool CourseManager::checkScheduleOverlap(const std::vector<std::shared_ptr<Period>>& newClasses, const std::vector<std::shared_ptr<Period>>& classesEnrolled) {

    // Check if overlap occurs
    if(checkPeriodOverlap(newClasses, classesEnrolled)){
        std::cout << "Overlaping hours. Couldn't add student to uc!\n";
        return true;
    }
    return false;
}

/**
 * @brief Switch a student's class within the same UC.
 *
 * This function allows a student to switch from one class (classRegistered) to another class (classToRegister) within the same UC (ucIdRegistered). It performs several checks to ensure that the switch is valid, including class capacity, class balance, and schedule overlap.
 *
 * @param studentId The ID of the student requesting the class switch.
 * @param ucIdRegistered The UC in which the student is currently enrolled (L.EICXXX).
 * @param classRegistered The class from which the student wants to switch (XLEICXX).
 * @param classToRegister The class to which the student wants to switch (XLEICXX).
 * @param saveToChanges Indicates whether to save this switch request to the changes log.
 * @return True if the class switch is successful, false otherwise.
 */
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
    if(this->checkScheduleOverlap(this->units[ucIdRegistered]->getClassPeriods(classRegistered),this->getStudentSchedule(studentId))){

        std::cout << "Classes overlap with student schedule.\n";
        this->addStudentToUc(ucIdRegistered,classRegistered, studentId, true, false);
        return false;
    }

    this->removeFromDatabase(studentId, ucIdRegistered);
    this->addStudentToUc(ucIdRegistered, classToRegister, studentId, true, false);
    if(saveToChanges) this->saveToChanges(studentId, 4, {ucIdRegistered, classToRegister} , {ucIdRegistered, classRegistered});
    return true;
}


/**
 * @brief Get the schedule of a specific student.
 *
 * This function retrieves and returns the class schedule for a specific student based on their enrolled UCs and classes. It compiles all the class periods associated with the student's enrolled classes.
 *
 * @param studentId The ID of the student for whom to retrieve the schedule.
 * @return A vector of shared pointers to the class periods in the student's schedule.
 */
std::vector<std::shared_ptr<Period>> CourseManager::getStudentSchedule(int studentId) {
    std::vector<std::shared_ptr<Period>> result;
    result.reserve(this->students[studentId]->getNumberOfClassesRegistered());
    // Pair uc/class
    auto studentClasses = this->students[studentId]->getClasses();

    for(std::pair<std::string, std::string> classPair: *studentClasses){
        for(const std::shared_ptr<Period>& period: this->units[classPair.first]->getClassPeriods(classPair.second)){
            result.push_back(period);
        }
    }
    return result;
}

/**
 * @brief Add a request to the queue for processing.
 *
 * This function adds a request to the queue for processing. Requests are used to change a student's enrollment status in UCs and classes. Each request includes the student's ID, the type of request, and details about the changes to their enrollment.
 *
 * @param requestType The type of the request (1 for add class, 2 for remove class, 3 for change UC, 4 for change class).
 * @param studentId_ The ID of the student for whom the request is made.
 * @param adding A pair specifying the UC and class to add (format: {UC ID, Class ID}).
 * @param removing A pair specifying the UC and class to remove (format: {UC ID, Class ID}).
 * @return True if the request was successfully added to the queue; false otherwise.
 */
bool CourseManager::addRequest(short requestType,int studentId_, const std::pair<std::string, std::string>& adding, const std::pair<std::string, std::string>& removing) {
    this->requests.emplace(requestType, studentId_, adding, removing);
    return true;
}


/**
 * @brief Handle pending requests for student enrollment changes.
 *
 * This function processes pending requests for student enrollment changes. Requests can include adding or removing a student from a class or switching their enrollment between UCs or classes. Each request is processed in the order it was received.
 */
void CourseManager::handleRequests() {
    if(this->requests.empty()){
        std::cout << "There are no request to handle!\n";
        return;
    }
    Request requestToHandle = this->requests.front();
    this->history.push(requestToHandle);
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
    if(!this->requests.empty()) this->handleRequests();
}

/**
 * @brief Save student enrollment information to the database.
 *
 * This function adds a line to the database with student enrollment information, including their student ID, name, UC ID, and class ID.
 *
 * @param studentId The ID of the student to be enrolled.
 * @param studentName The name of the student.
 * @param ucId The UC ID to which the student is enrolled.
 * @param classId The class ID within the UC to which the student is enrolled.
 */
void CourseManager::saveToDatabase(int studentId, const std::string &studentName, const std::string &ucId, const std::string &classId) {
    // FUNCTION TO ADD A LINE TO THE DATABASE
    std::ofstream out("../data/students_classes.csv", std::ios::app);
    out << studentId << "," << studentName << "," << ucId << "," << classId << std::endl;
}


/**
 * @brief Remove student enrollment information from the database.
 *
 * This function removes a line from the database containing student enrollment information based on the student's ID and UC ID.
 *
 * @param studentId The ID of the student to be unenrolled.
 * @param ucId The UC ID from which the student is unenrolled.
 */
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

/**
 * @brief Display class occupancy information.
 *
 * This function displays information about the occupancy of classes within each UC, sorted in ascending or descending order
 * based on the orderType. The output includes the number of students in each class.
 *
 * @param orderType An integer specifying the order in which to display the class occupancy:
 *                  - 1 for ascending order (low to high occupancy).
 *                  - 2 for descending order (high to low occupancy).
 * @return Always returns false since it's a display function.
 */

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

/**
 * @brief Display year-based student occupancy information.
 *
 * This function displays information about the number of students in each academic year (unit year) within the course.
 * The output can be sorted in either ascending or descending order based on the orderType.
 *
 * @param orderType An integer specifying the order in which to display the year-based occupancy:
 *                  - 1 for ascending order (low to high student count).
 *                  - 2 for descending order (high to low student count).
 * @return Always returns false since it's a display function.
 */
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

/**
 * @brief Display unit-based student occupancy information.
 *
 * This function displays information about the number of students in each academic unit (course unit) within the course.
 * The output can be sorted in either ascending or descending order based on the orderType.
 *
 * @param orderType An integer specifying the order in which to display the unit-based occupancy:
 *                  - 1 for ascending order (low to high student count).
 *                  - 2 for descending order (high to low student count).
 * @return Always returns false since it's a display function.
 */
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

/**
 * @brief Save course changes to the changes log.
 *
 * This function is responsible for recording course changes in the changes log file. It appends information about
 * student-related operations, such as adding, removing, or switching academic units or classes, to the log file.
 *
 * @param studentId An integer representing the unique identifier of the student involved in the operation.
 * @param operationType An integer specifying the type of operation:
 *                     - 1 for removing a student to an academic unit or class.
 *                     - 2 for adding a student from an academic unit or class.
 *                     - 3 for switching to a different academic unit.
 *                     - 4 for switching to a different class within the same academic unit.
 * @param adding A pair representing the academic unit or class being added, formatted as "unitID/classID".
 * @param removing A pair representing the academic unit or class being removed, formatted as "unitID/classID".
 */
void CourseManager::saveToChanges(int studentId, int operationType, const std::pair<std::string, std::string>& adding,const std::pair<std::string, std::string>& removing) const {
    std::ofstream out("../data/changes.csv", std::ios::app);
    out << studentId << "," << operationType << "," << adding.first << "/" << adding.second << "," << removing.first << "/" << removing.second << std::endl;
}

/**
 * @brief Revert a previously handled course change request.
 *
 * This function allows reverting a previously handled course change request by undoing the corresponding operation.
 *
 * @param currentRequest The course change request to be reverted.
 * @return `true` if the request is successfully reverted, `false` otherwise.
 */
bool CourseManager::revertRequest(const Request& currentRequest){
    switch (currentRequest.requestType) {
        case 2: // Removing a student from a class
            if(this->addStudentToUc(currentRequest.removing.first, currentRequest.removing.second, currentRequest.studentId, false, false)){
                std::cout << "Operation succesfull!\n";
                return true;
            }
            std::cout << "Couldn't revert operation!\n";
            return false;
        case 1: // Adding a student to a class
            if(this->removeStudentFromUc(currentRequest.adding.first, currentRequest.studentId, false)){
                std::cout << "Operation succesfull!\n";
                return true;
            }
            std::cout << "Couldn't revert operation!\n";
            return false;
        case 3: // switching uc
            if(this->switchUc(currentRequest.studentId, currentRequest.adding.first, currentRequest.removing.first, false)){
                std::cout << "Operation succesfull!\n";
                return true;
            }
            std::cout << "Couldn't revert operation!\n";
            return false;
        case 4: // switching class
            if(this->switchClass(currentRequest.studentId, currentRequest.adding.first, currentRequest.adding.second, currentRequest.removing.second, false)){
                std::cout << "Operation succesfull!\n";
                return true;
            }
            std::cout << "Couldn't revert operation!\n";
            return false;
    }
}

/**
 * @brief Revert all changes made to the course according to the change history.
 *
 * This function reverts all changes made to the course based on the change history. It iterates through the history of handled requests, reverts each one, and removes it from the change log.
 */
void CourseManager::revertChanges() {
    while(!this->history.empty()){
        Request currentRequest = this->history.top();
        this->history.pop();
        if(this->revertRequest(currentRequest)){
            std::ifstream in("../data/changes.csv");
            std::ofstream out("../data/changes_temp.csv");
            std::string line;
            int lineNum = 0;
            while(std::getline(in,line)){
                if(lineNum++ == currentRequest.requestId) continue;
                out << line << std::endl;
            }

            remove("../data/changes.csv");
            rename("../data/changes_temp.csv", "../data/changes.csv");

        }
    }
}
