//
// Created by admin1 on 26-10-2023.
//

#include "../include/Request.h"

Request::Request(int requestType_, int studentId_, const std::pair<std::string, std::string>& ucInfo_) {
    this->requestType = requestType_;
    this->studentId = studentId_;
    this->ucInfo = ucInfo_;
}
/*
void Request::handleRequest(const std::shared_ptr<CourseManager>& courseManager) {
    switch (this->requestType) {
        case 1:
            // Add uc to student
            if(courseManager->addStudentToUc(this->ucInfo.first, this->ucInfo.second, studentId)){
                std::cout << "Student was added succesfully to the unit!\n";
            }
            else{
                std::cout << "Student couldn't be added to the unit!\n";
            }
            break;
        case 2:
            // Remove student from uc
            if(courseManager->removeStudentFromUc(this->ucInfo.first, studentId)){
                std::cout << "Student was removed succesfully from the unit!\n";
            }
            else{
                std::cout << "Student couldn't be removed from the unit!\n";
            }
            break;
        default:
            std::cout << "Invalid request type!\n";
    }
}

 */



