//
// Created by admin1 on 26-10-2023.
//

#ifndef AED_PROJ_REQUEST_H
#define AED_PROJ_REQUEST_H

#include <utility>
#include <string>
#include "CourseManager.h"

class Request {
private:
    short requestType;
    int studentId;
    // <ucId, classId>
    std::pair<std::string, std::string> ucInfo;
public:
    // Constructor
    Request(int requestType_, int studentId_, const std::pair<std::string, std::string> & ucInfo_);

    //void handleRequest(const std::shared_ptr<CourseManager>& courseManager);

};


#endif //AED_PROJ_REQUEST_H
