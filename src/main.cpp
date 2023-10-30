#include <iostream>
#include <limits>
#include "../include/CourseManager.h"


void waitForEnter();
bool validStudentId(const std::string& id);
void showOccupancies(CourseManager*, int);

void showLists(CourseManager* courseManager, int orderType);

int getStudentId(const std::string& message = "Provide the student id: "){
    std::string studentId;
    do {
        std::cout << message;
        std::cin >> studentId;
    }
    while(!validStudentId(studentId));
    return std::stoi(studentId);
}

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
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
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
    return;
}

/* TO BE IMPLEMENTEDDD
void waitForEnter() {
    std::cout << "Press Enter to continue...";
    for (std::string line = ""; line[0] != '\n';) {
        std::getline(std::cin, line);
        continue;
    }
}
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

bool showRequestMenu(CourseManager* course){
    char option;
    std::string studentId;
    std::string succesfullSentRequest = "Request submitted, will be handled shortly!\n";
    std::string failedSentRequest = "Request couldn't be submitted!\n";


    while(true){
        std::cout << "\nWhat request would you like to make:\n"
                     "[1] Add a student to a class\n"
                     "[2] Remove a student from a class\n"
                     "[3] Request a class change\n"
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

int main() {
    CourseManager* informatica = new CourseManager;
    bool running = true;
    while(running){
        std::cout << "\nSelect an option:\n"
                     "[1] Consult schedule\n"
                     "[2] Consult lists\n"
                     "[3] Consult occupancies\n"
                     "[4] Make a request\n"
                     "[5] Handle requests\nYour option:";
        char option;
        int orderType;
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
                std::cout << "\nIn wich order would you like to consult the listings:\n"
                             "[1] Order by student ID\n"
                             "[2] Order alphabetically\n"
                             "[0] Return to main menu\nYour option: ";
                std::cin >> orderType;
                if(orderType == 0) break;
                showLists(informatica, orderType);
                break;
            case 3:
                std::cout << "\nIn wich order would you like to consult the occupancies:\n"
                             "[1] Ascending order\n"
                             "[2] Descending order\n"
                             "[0] Return to main menu\nYour option: ";
                std::cin >> orderType;
                showOccupancies(informatica, orderType);
                break;
            case 4:
                showRequestMenu(informatica);
                break;
            case 5:
                std::cout << "Handling oldest request!\n";
                informatica->handleRequest();
                break;
            default:
                std::cout << "Invalid option, try again!\n";
                continue;
        }


    }

    delete informatica;
    return 0;
}

void showLists(CourseManager* courseManager, int orderType) {
    bool running = true;
    int scheduleOption;
    int year;
    int firstN;
    std::string class_;
    std::string uc;
    while (running) {
        std::cout << "\nSelect an option:\n"
                     "[1] Consult students in year\n"
                     "[2] Consult students in uc\n"
                     "[3] Consult students in class\n"
                     "[0] Return to main menu\nYour option:";
        std::cin >> scheduleOption;


        switch (scheduleOption) {
            case 0:
                return; // Exit the function to return to the main menu
            case 1:

                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat year would you like to consult: ";
                std::cin >> year;
                courseManager->showStudentListInYear(year, orderType,firstN);
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
                running = false;
                break;
            case 2:
                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat uc would you like to consult (L.EICXXX): ";
                std::cin >> uc;
                courseManager->showStudentListInCourse(uc, orderType, firstN);
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
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
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
                running = false;

            default:
                std::cout << "Invalid option, try again!\n";
        }
    }
    return;
}


void showOccupancies(CourseManager* course, int orderType){
    bool running = true;
    char option;
    while(running){
        std::cout << "What occupancy would you like to consult:\n"
                     "[1] Class occupancy\n"
                     "[2] Year occupancy\n"
                     "[3] UC occupancy\n"
                     "[0] Return to main menu\nYour option:";
        std::cin >> option;
        if(!std::isdigit(option)){
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
            case 0:
                return;
            default:
                std::cout << "Enter a valid option!\n";
                continue;
        }
    }
}


/*
 *
 * TO DO
 * Save changes to file (changes.csv) - (Add class/UC, Remove class/UC, Switch class)
 * Save changes to database (students_classes.csv) - (Add class/UC, Remove class/UC, Switch class)
 *
 */
