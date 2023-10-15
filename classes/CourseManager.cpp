//
// Created by admin1 on 14-10-2023.
//

#include "../headers/CourseManager.h"

CourseManager::CourseManager() {
    std::ifstream in("../src/students_classes.csv");
    std::string line;

    std::getline(in, line);

    while(std::getline(in, line)){
        if(line.find(',') == std::string::npos) continue;

        int studentCode = std::stoi(line.substr(0, line.find(',')));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string studentName = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string ucCode = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1, line.length() - line.find(',') - 1);

        std::string classCode = line.substr(0, line.find(','));

        if(this->students.count(studentCode) == 0){
            // Add student, uc and class
            Student currentStudent(studentName, studentCode);
            this->students.insert(std::make_pair(studentCode, currentStudent));
        }
        else{
            // add uc and class
            std::cout << "Already in students";
        }
    }
    std::cout << students.size();
}
