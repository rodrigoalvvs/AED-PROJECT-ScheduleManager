#include <iostream>
#include <limits>
#include "../include/CourseManager.h"


void waitForEnter();
bool validStudentId(const std::string& id);

void showLists(std::shared_ptr<CourseManager> sharedPtr, int i);

int getStudentId(){
    std::string studentId;
    do {
        std::cout << "Provide the student id: ";
        std::cin >> studentId;
    }
    while(!validStudentId(studentId));
    return std::stoi(studentId);
}

std::string getClassId(){
    std::string classId;
    do {
        std::cout << "Provide the class id (XLEICXX): ";
        std::cin >> classId;
        if(classId.size() != 7) std::cout << "Invalid input.\n";
    }
    while(classId.size() != 7);
    return classId;
}

std::string getUcId(){
    std::string ucId;
    do{
        std::cout << "Provide the uc id (L.EICXXX): ";
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

void showSchedules(const std::shared_ptr<CourseManager>& courseManager) {
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

void showRequestMenu(std::shared_ptr<CourseManager> course){
    char option;
    std::string studentId;
    while(true){
        std::cout << "\nWhat request would you like to make:\n"
                     "[1] Add a student to a class"
                     "[2] Remove a student from a class"
                     "[3] Request a class change"
                     "[0] Return to main menu\nYour option: ";
        std::cin >> option;
        if(!std::isdigit(option)){
            std::cout << "Enter a valid option.\n";
            continue;
        }
        switch (option - '0') {
            case 1:
                // ADD OVERLAP SCHEDULE FUNCTIONALITY [IMPORTANT]
                course->addStudentToUc(getUcId(), getClassId(), getStudentId());
                return;
            case 2:
                course->removeStudentFromUc(getUcId(), getStudentId());
                return;
            case 3:
                break;
            default:
                std::cout << "Enter a valid option.\n";
                continue;
        }

    }

}

int main() {
    CourseManager informatica;
    bool running = true;

    while(running){
        std::cout << "\nSelect an option:\n"
                     "[1] Consult schedule\n"
                     "[2] Consult lists\n"
                     "[3] Make a request\nYour option:";
        char option;
        std::cin >> option;
        if(!std::isdigit(option)){
            std::cout << "Enter a valid digit.\n";
            continue;
        }

        switch (option - '0') {
            case 1:
                showSchedules(std::make_shared<CourseManager>(informatica));
                break;
            case 2:
                std::cout << "\nIn wich order would you like to consult the listings:\n"
                             "[1] Order by student ID\n"
                             "[2] Order alphabetically\n"
                             "[0] Return to main menu\nYour option: ";
                int orderType;
                std::cin >> orderType;
                if(orderType == 0) break;
                showLists(std::make_shared<CourseManager>(informatica), orderType);
                break;
            case 3:
                showRequestMenu(std::make_shared<CourseManager>(informatica));
                break;
            default:
                std::cout << "Invalid option, try again!\n";
                continue;
        }


    }


    return 0;
}

void showLists(std::shared_ptr<CourseManager> courseManager, int orderType) {
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
