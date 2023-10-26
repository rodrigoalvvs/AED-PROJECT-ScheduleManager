#include <iostream>
#include <limits>
#include "../include/CourseManager.h"


void waitForEnter();

void showLists(std::shared_ptr<CourseManager> sharedPtr, int i);

void showSchedules(const std::shared_ptr<CourseManager>& courseManager) {
    bool running = true;
    int scheduleOption;
    int studentId;
    std::string ucId;
    std::string classId;

    while (running) {
        std::cout << "\nSelect an option:\n"
                     "[1] Consult student schedule\n"
                     "[2] Consult class schedule\n"
                     "[0] Return to main menu\nYour option:";
        std::cin >> scheduleOption;


        switch (scheduleOption) {
            case 0:
                return; // Exit the function to return to the main menu
            case 1:
                std::cout << "Provide the student id: ";
                std::cin >> studentId;
                courseManager->showStudentSchedule(studentId);
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
                running = false;
                break;
            case 2:
                std::cout << "Provide the uc id (L.EICXXX): ";
                std::cin >> ucId;
                std::cout << "Provide the class id (XLEICXX): ";
                std::cin >> classId;
                courseManager->showClassSchedule(ucId, classId);
                //waitForEnter();
                running = false;
                break;
            default:
                std::cout << "Invalid option, try again!\n";
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


int main() {
    CourseManager informatica;
    bool running = true;

    while(running){
        std::cout << "\nSelect an option:\n"
                     "[1] Consult schedule\n"
                     "[2] Consult lists\n"
                     "[3] Make a request\nYour option:";
        int option;
        std::cin >> option;

        switch (option) {
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
                courseManager->showStudentListInYear(year, firstN);
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
                running = false;
                break;
            case 2:
                std::cout << "\nHow many students would you like to display (-1 to show all): ";
                std::cin >> firstN;
                std::cout << "\nWhat uc would you like to consult (L.EICXXX): ";
                std::cin >> uc;
                courseManager->showStudentListInCourse(uc, firstN);
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
                courseManager->showStudentListInClass(uc, class_, firstN);
                std::cout << "Press Enter to return to main menu.";
                //waitForEnter();
                running = false;

            default:
                std::cout << "Invalid option, try again!\n";
        }
    }
    return;
}
