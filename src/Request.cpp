//
// Created by admin1 on 04-11-2023.
//

#include <sstream>
#include "../include/Request.h"


/**
 * @brief Initializes a new request object.
 *
 * This constructor creates a new request object with the specified parameters, including the request type, student ID, items to be added, items to be removed, and a request ID.
 *
 * @param requestType_ The type of the request (1: Add student to class, 2: Remove student from class, 3: Switch UC, 4: Switch class).
 * @param studentId_ The unique identifier of the student associated with the request.
 * @param adding_ A pair representing the items to be added (e.g., UC and class).
 * @param removing_ A pair representing the items to be removed (e.g., UC and class).
 * @param requestId_ The unique identifier of the request.
 */
Request::Request(short requestType_, int studentId_, const std::pair<std::string, std::string> &adding_,const std::pair<std::string, std::string> &removing_, int requestId_) {
    this->requestType = requestType_;
    this->studentId = studentId_;
    this->adding = adding_;
    this->removing = removing_;
    this->requestId = requestId_;
}

/**
 * @brief Converts the Request object to a string representation.
 *
 * This function converts the Request object into a string representation, providing details about the request type and the associated student and items.
 *
 * @return A string representation of the Request object.
 */
std::string Request::to_string() const {
    std::stringstream ss;
    switch (this->requestType) {
        case 1: // Removing a student from a class
            ss << this->requestId << " - Student with ID: " << studentId << " was removed from the UC/Class -> " << this->removing.first << "/" << this->removing.second;
            return ss.str();
        case 2: // Adding a student to a class
            ss << this->requestId << " - Student with ID: " << studentId << " was added from the UC/Class -> " << this->adding.first << "/" << this->adding.second;
            return ss.str();
        case 3: // switching uc
            ss << this->requestId << " - Student with ID: " << studentId << " was switched from UC -> " << this->removing.first << " To UC -> " << this->adding.first;
            return ss.str();
        case 4: // switching class
            ss << this->requestId << " - Student with ID: " << studentId << " was switched from UC/Class -> " << this->removing.first << "/" <<this->removing.second << " To UC/Class -> " << this->adding.first << "/" << this->adding.second;
            return ss.str();
    }
}
