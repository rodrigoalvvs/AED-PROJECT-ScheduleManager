//
// Created by admin1 on 19-10-2023.
//

#ifndef AED_PROJ_COURSEUNIT_H
#define AED_PROJ_COURSEUNIT_H

#include <unordered_map>
#include <string>
#include <memory>
#include <list>
#include "CourseClass.h"

class CourseClass;

class CourseUnit{
private:
    std::unordered_map<std::string, std::shared_ptr<CourseClass>> classes;
public:
    // Constructors and destructors
    CourseUnit();

    // Class getters and setters

    int getNumberOfClasses() const;


    // Class member functions
    bool addClass(const std::string& classId);
    bool addStudent(const std::string& classId, int studentId);
    int getStudentCount();
    std::shared_ptr<std::list<int>> getStudentList();
    int getStudentCountOnClass(const std::string& classId);
    const std::vector<int>& getStudentListOnClass(const std::string& classId);
    std::shared_ptr<CourseClass> getClass(const std::string& id);
    const std::vector<std::shared_ptr<Period>>& getClasses( const std::string& classId);
};

#endif //AED_PROJ_COURSEUNIT_H
