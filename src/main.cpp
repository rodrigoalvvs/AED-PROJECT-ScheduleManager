#include <iostream>
#include "../include/CourseManager.h"


bool validStudentId(const std::string& id);
void showOccupancies(CourseManager*, int);
void showLists(CourseManager* courseManager, int orderType);


/**
 * @brief Prompts the user to provide a student ID and validates it.
 *
 * This function prompts the user to enter a student ID and validates it.
 * It will keep prompting until a valid student ID is provided.
 *
 * @param message The message to display when prompting for the student ID (default is "Provide the student ID: ").
 *
 * @return The valid student ID provided by the user.
 */
int getStudentId(const std::string& message = "Provide the student id: "){
    std::string studentId;
    do {
        std::cout << message;
        std::cin >> studentId;
    }
    while(!validStudentId(studentId));
    return std::stoi(studentId);
}


/**
 * @brief Prompts the user to provide a class ID (XLEICXX) and validates it.
 *
 * This function prompts the user to enter a class ID in the format "XLEICXX" and validates it.
 * It will keep prompting until a valid class ID is provided.
 *
 * @param message The message to display when prompting for the class ID (default is "Provide the class ID (XLEICXX): ").
 *
 * @return The valid class ID provided by the user in the format "XLEICXX".
 */
std::string getClassId(const std::string& message = "Provide the class id (XLEICXX): "){
    std::string classId;
    do {
        std::cout << message;
        std::cin >> classId;
        if(classId.size() != 7) std::cout << "Invalid input.\n";
    }
    while(classId.size() != 7);
    return classId;
}


/**
 * @brief Prompts the user to provide a UC ID (L.EICXXX) and validates it.
 *
 * This function prompts the user to enter a UC ID in the format "L.EICXXX" and validates it.
 * It will keep prompting until a valid UC ID is provided.
 *
 * @param message The message to display when prompting for the UC ID (default is "Provide the UC ID (L.EICXXX): ").
 *
 * @return The valid UC ID provided by the user in the format "L.EICXXX".
 */
std::string getUcId(const std::string& message = "Provide the uc id (L.EICXXX): "){
    std::string ucId;
    do{
        std::cout << message;
        std::cin >> ucId;
        if(ucId.size() != 8) std::cout << "Invalid input.\n";
    }
    while(ucId.size() != 8);
    return ucId;
}


/**
 * @brief Validates a student ID (9-digit numeric format).
 *
 * This function validates a student ID provided as a string by checking if it has
 * the correct length (9 characters) and if it can be converted to an integer.
 *
 * @param id The student ID to validate.
 *
 * @return true if the student ID is valid; false otherwise.
 */
bool validStudentId(const std::string& id){
    if(id.size() != 9){
        std::cout << "Invalid student id\n";
        return false;
    }
    try{
        int studentId = std::stoi(id);
        return true;
    }
    catch (const std::invalid_argument e){
        std::cout << "Invalid student id\n";
        return false;
    }
}

void showSchedules(CourseManager* courseManager) {
    bool running = true;
    char scheduleOption;

    while (running) {
        std::cout << "\nSelect an option:\n"
                     "[1] Consult student schedule\n"
                     "[2] Consult class schedule\n"
                     "[0] Return to main menu\nYour option:";
        std::cin >> scheduleOption;

        if(!std::isdigit(scheduleOption)){
            std::cout << "Enter a valid digit.\n";
            continue;
        }


        switch (scheduleOption - '0') {
            case 0:
                return; // Exit the function to return to the main menu
            case 1:
                courseManager->showStudentSchedule(getStudentId());
                running = false;
                break;
            case 2:

                courseManager->showClassSchedule(getUcId(), getClassId());
                //waitForEnter();
                running = false;
                break;
            default:
                std::cout << "Invalid option, try again!\n";
                continue;
        }
    }
}

/**
 * @brief Display a menu to make requests for UC or class changes.
 *
 * This function displays a menu to make requests for UC or class changes for a specific student.
 * The user is prompted to select the type of change (UC or class) and provide the necessary details.
 *
 * @param course A pointer to the CourseManager instance.
 *
 * @return true if a request is successfully made; false if the user chooses to return to the previous menu.
 */
bool showSwitchMenu(CourseManager* course){
    char option;
    while(true){
        std::cout << "\nWhat request would you like to make:\n"
                     "[1] UC change\n"
                     "[2] Class change\n"
                     "[0] Return to previous menu.\nYour option:";
        std::cin >> option;
        if(!std::isdigit(option)){
            std::cout << "Enter a valid option.\n";
            continue;
        }
        if(option - '0' == 0) return false;
        int studentId = getStudentId("Provide the student id: ");
        std::string ucRegistered;
        std::string ucToRegister;
        std::string classRegistered;
        std::string classToRegister;

        switch (option - '0') {
            case 1:
                ucRegistered = getUcId("Enter the uc in wich the student is already enrolled (L.EICXXX):");
                ucToRegister = getUcId("Enter the uc that the students wishes to enroll (L.EICXXX):");
                return course->addRequest(3, studentId, {ucToRegister, ""}, {ucRegistered, ""});
            case 2:
                ucRegistered = getUcId("Enter the uc to perform the class change (L.EICXXX): ");
                classRegistered = getClassId("Enter the class that the student is enrolled (XLEICXX): ");
                classToRegister = getClassId("Enter the class that the student wishes to enroll (XLEICXX): ");
                return course->addRequest(4, studentId, {ucRegistered, classToRegister}, {ucRegistered, classRegistered});
            case 0:
                return true;
            default:
                std::cout << "Enter a valid option.\n";
        }
    }
}

/**
 * @brief Display a menu to make student-related requests.
 *
 * This function displays a menu to make various student-related requests, such as adding a student to a class,
 * removing a student from a class, or requesting a change. It prompts the user to select the type of request and
 * provides the necessary details.
 *
 * @param course A pointer to the CourseManager instance.
 *
 * @return true if a request is successfully made, false otherwise.
 */
bool showRequestMenu(CourseManager* course){
    char option;
    std::string studentId;
    std::string succesfullSentRequest = "Request submitted, will be handled shortly!\n";
    std::string failedSentRequest = "Request couldn't be submitted!\n";


    while(true){
        std::cout << "\nWhat request would you like to make:\n"
                     "[1] Add a student to a class\n"
                     "[2] Remove a student from a class\n"
                     "[3] Request a change\n"
                     "[0] Return to main menu\nYour option: ";
        std::cin >> option;
        if(!std::isdigit(option)){
            std::cout << "Enter a valid option.\n";
            continue;
        }
        switch (option - '0') {
            case 1:
                if(course->addRequest(1, getStudentId(), {getUcId(), getClassId()}, {"", ""})){
                    std::cout << succesfullSentRequest;
                    return true;
                }
                std::cout << failedSentRequest;
                return false;
            case 2:
                if(course->addRequest(2, getStudentId(), {"", ""}, {getUcId(), getClassId()})){
                    std::cout << succesfullSentRequest;
                    return true;
                }
                std::cout << failedSentRequest;
                return false;
            case 3:
                if(showSwitchMenu(course)){
                    std::cout << succesfullSentRequest;
                    return true;
                }
                std::cout << failedSentRequest;
                return false;
            case 0:
                return false;
            default:
                std::cout << "Enter a valid option.\n";
                continue;
        }

    }

}


/**
 * @brief Remove a specific line from a log file.
 *
 * This function reads a log file, removes a specific line identified by its line number,
 * and then saves the modified log back to the file.
 *
 * @param lineToRemove The line number to be removed from the log.
 */
void removeLineFromLog(int lineToRemove){
    std::ifstream in("../data/changes.csv");
    std::ofstream out("../data/changes_temp.csv");
    std::string line;
    int lineNum = 0;
    while(std::getline(in,line)){
        if(lineNum++ == lineToRemove) continue;
        out << line << std::endl;
    }

    remove("../data/changes.csv");
    rename("../data/changes_temp.csv", "../data/changes.csv");

}


/**
 * @brief Manage a log of course management operations and allow for reverting specific operations.
 *
 * This function reads a CSV log file containing course management operations and provides the
 * ability to revert specific operations based on the `lineToChange` parameter.
 *
 * @param course A pointer to the CourseManager object.
 * @param lineToChange The line number of the operation to revert (default is -1 to view the log).
 */
void manageLog(CourseManager* course, int lineToChange = -1){
    std::ifstream in("../data/changes.csv");
    std::string line;

    int lineNum = 1;
    std::getline(in, line); // SKIP FIRST LINE
    while(std::getline(in, line)){
        if(line.find('\r') != std::string::npos) line.pop_back();
        int studentId = std::stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        int operationType = std::stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string addingUc = line.substr(0, line.find('/'));
        line = line.substr(line.find('/') + 1, line.length() - line.find('/') - 1);
        std::string addingClass = line.substr(0, line.find(','));

        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);
        std::string removingUc = line.substr(0, line.find('/'));
        line = line.substr(line.find('/') + 1, line.length() - line.find('/') - 1);
        std::string removingClass = line.substr(0, line.find(','));

        Request currentRequest(operationType, studentId, {addingUc, addingClass}, {removingUc, removingClass}, lineNum++);

        // If current operation has operation id matching the one to handle
        if(currentRequest.requestId == lineNum - 1 && lineToChange != -1){
            course->revertRequest(currentRequest);
            removeLineFromLog(lineToChange);
            return;
        }
        std::cout << currentRequest.to_string() << std::endl;
    }

    if(lineNum == 1){
        std::cout << "No entries to show, history is clean.\n";
        return;
    }
    std::cout << "Enter the id of the operation to revert (-1 to return to main menu):";
    int option;
    std::cin >> option;
    if(option > lineNum){
        std::cout << "Invalid option\n";
        return;
    }
    if(option == -1) return;
    else manageLog(course, option);
}

/**
 * @brief Display a menu to consult various student listings based on order and criteria.
 *
 * This function displays a menu that allows the user to select the order and criteria for consulting student listings.
 * The user can choose to order by student ID or alphabetically, and then select from options such as
 * consulting students in a specific year, UC, class, or displaying UCs with the most students.
 *
 * @param courseManager A pointer to the CourseManager instance.
 */
void showLists(CourseManager* courseManager) {
    bool running = true;
    int scheduleOption;
    int year;
    int firstN;
    std::string class_;
    std::string uc;
    char orderType;

    while (running) {
        std::cout << "\nIn wich order would you like to consult the listings:\n"
                     "[1] Order by student ID\n"
                     "[2] Order alphabetically\n"
                     "[0] Return to main menu\nYour option: ";
        std::cin >> orderType;
        if(orderType - '0' == 0) return;
        if(orderType - '0' > 2 || orderType - '0' < 1 || !std::isdigit(orderType)){
            std::cout << "Enter a valid option!\n";
            continue;
        }
        std::cout << "\nSelect an option:\n"
                     "[1] Consult students in year\n"
                     "[2] Consult students in uc\n"
                     "[3] Consult students in class\n"
                     "[4] Consult UC's with most students\n"
                     "[0] Return to order menu\nYour option:";
        std::cin >> scheduleOption;
        if(orderType - '0' > 2 || orderType - '0' < 1 || !std::isdigit(orderType)){
            std::cout << "Enter a valid option!\n";
            continue;
        }


        switch (scheduleOption) {
            case 0:
                continue; // Go back to order menu
            case 1:

                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat year would you like to consult: ";
                std::cin >> year;
                courseManager->showStudentListInYear(year, orderType,firstN);
                running = false;
                break;
            case 2:
                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat uc would you like to consult (L.EICXXX): ";
                std::cin >> uc;
                courseManager->showStudentListInCourse(uc, orderType, firstN);
                running = false;
                break;
            case 3:
                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat uc would you like to consult (L.EICXXX): ";
                std::cin >> uc;
                std::cout << "\nWhat class would you like to consult (XLEICXX): ";
                std::cin >> class_;
                courseManager->showStudentListInClass(uc, class_, orderType, firstN);
                running = false;
            case 4:
                std::cout << "How many units would you like to display (-1 to show all): ";
                std::cin >> firstN;
                courseManager->showUnitCoursesWithMostStudents(firstN);
                running = false;
                break;
            default:
                std::cout << "Invalid option, try again!\n";
        }
    }
}

/**
 * @brief Display a menu to consult various occupancies based on order and criteria.
 *
 * This function displays a menu that allows the user to select the order and criteria for consulting occupancies.
 * The user can choose to order in ascending or descending order and then select from options such as
 * class occupancy, year occupancy, UC occupancy, or displaying student count on a specific number of units.
 *
 * @param course A pointer to the CourseManager instance.
 */
void showOccupancies(CourseManager* course){
    bool running = true;
    char option;
    char orderType;
    while(running){
        // Get input for type of order
        std::cout << "\nIn wich order would you like to consult the occupancies:\n"
                     "[1] Ascending order\n"
                     "[2] Descending order\n"
                     "[0] Return to main menu\nYour option: ";
        std::cin >> orderType;
        if(orderType - '0' == 0) return;
        if(orderType -'0' > 2 || orderType - '0' < 1 || !std::isdigit(orderType)){
            std::cout << "Enter a valid option!\n";
            continue;
        }


        // Select which occupancy list to show
        std::cout << "What occupancy would you like to consult:\n"
                     "[1] Class occupancy\n"
                     "[2] Year occupancy\n"
                     "[3] UC occupancy\n"
                     "[4] Student Count on N units\n"
                     "[0] Return to order menu\nYour option:";
        std::cin >> option;
        if(!std::isdigit(option) || option - '0' > 4 || option - '0' < 0){
            std::cout << "Enter a valid option!\n";
            continue;
        }


        switch (option - '0') {
            case 1:
                course->showClassOccupancy(orderType);
                break;
            case 2:
                course->showYearOccupancy(orderType);
                break;
            case 3:
                course->showUcOccupancy(orderType);
                break;
            case 4:
                std::cout << "How many units, would you like to filter the student count:";
                int n;
                std::cin >> n;
                course->showStudentCountOnNUnits(n);
            case 0:
                continue;
            default:
                std::cout << "Enter a valid option!\n";
                continue;
        }
    }
}

/**
 * @brief Clear the log file by preserving the header line.
 *
 * This function clears the log file, preserving the header line that defines the format of the log entries.
 * It removes all log entries while keeping the header line intact.
 */
void clearLog(){
    std::ifstream in("../data/changes.csv");
    std::ofstream out("../data/changes_temp.csv");
    std::string line;
    std::getline(in, line);
    out << line << std::endl;
    remove("../data/changes.csv");
    rename("../data/changes_temp.csv", "../data/changes.csv");
}


/**
 * @brief Display an exit menu and handle user options.
 *
 * This function displays an exit menu that allows the user to choose between several options:
 *  - Returning to the main menu.
 *  - Reverting all changes made during the session.
 *  - Clearing the log file.
 *  - Exiting the program.
 *
 * @param course A pointer to the CourseManager instance.
 * @return True if the user chooses to return to the main menu, false for other options (revert, clear log, or exit).
 */
bool showExitMenu(CourseManager* course){
    char option;
    std::cout << "Enter a option:\n"
                "[1] Revert all changes\n"
                "[2] Clear log\n"
                "[3] Exit\n"
                "[0] Return to main menu\nYour option:";
    std::cin >> option;
    if(!isdigit(option) || option - '0' < 0 || option - '0' > 3){
        std::cout << "Enter a valid option\n";
        showExitMenu(course);
    }
    switch (option - '0') {
        case 0:
            return true;
        case 1:
            course->revertChanges();
            return false;
        case 2:
            clearLog();
            return false;
        case 3:
            return false;
    }
}

/**
 * @brief Main function to run the Student Manager System.
 *
 * This function presents a menu of options to the user and allows them to interact
 * with the Student Manager System. The user can consult schedules, lists, occupancies,
 * make requests, handle requests, manage the system log, and exit the system.
 *
 * @return Returns 0 upon successful execution.
 */
int main() {
    CourseManager* informatica = new CourseManager;
    bool running = true;
    while(running){
        std::cout << "\nSelect an option:\n"
                     "[1] Consult schedule\n"
                     "[2] Consult lists\n"
                     "[3] Consult occupancies\n"
                     "[4] Make a request\n"
                     "[5] Handle requests\n"
                     "[6] Consult system log\n"
                     "[7] Exit System\nYour option:";
        char option;
        std::cin >> option;
        if(!std::isdigit(option)){
            std::cout << "Enter a valid digit.\n";
            continue;
        }
        switch (option - '0') {
            case 1:
                showSchedules(informatica);
                break;
            case 2:
                showLists(informatica);
                break;
            case 3:
                showOccupancies(informatica);
                break;
            case 4:
                showRequestMenu(informatica);
                break;
            case 5:
                std::cout << "Handling all requests!\n";
                informatica->handleRequests();
                break;
            case 6:
                manageLog(informatica);
                break;
            case 7:
                running = showExitMenu(informatica);
                break;
            default:
                std::cout << "Invalid option, try again!\n";
                continue;
        }
    }
    delete informatica;
    return 0;
}
