/**
 * @file Request.h
 * @brief Definition of the Request class.
 */

#ifndef AED_PROJ_REQUEST_H
#define AED_PROJ_REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a request for class or course changes by a student.
 */
class Request {
public:
    int requestId; ///< The unique identifier for the request.
    short requestType; ///< The type of request (1 for remove class, 2 for add class, 3 for change UC, 4 for change class).
    int studentId; ///< The ID of the student associated with the request.
    std::pair<std::string, std::string> adding; ///< The addition details (e.g., UC and class to add).
    std::pair<std::string, std::string> removing; ///< The removal details (e.g., UC and class to remove).

    Request(short requestType_, int studentId_, const std::pair<std::string, std::string>& adding_,
            const std::pair<std::string, std::string>& removing_, int requestId_ = 1);
    std::string to_string() const;
};

#endif // AED_PROJ_REQUEST_H
