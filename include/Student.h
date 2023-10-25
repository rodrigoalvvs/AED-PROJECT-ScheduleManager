//
// Created by admin1 on 14-10-2023.
//

#ifndef AED_PROJ_STUDENT_H
#define AED_PROJ_STUDENT_H

#include <string>
#include <unordered_map>
#include <memory>
#include "CourseClass.h"
#include "CourseUnit.h"

class CourseClass;

class Student {
private:

    // Student name
    std::string name;

    // Student id
    int identifier;

    // unordered_map with <"ucID", "classId">
    std::unordered_map<std::string, std::string> classesRegistered;

public:
    // Constructors and destructors
    Student(const std::string& name_, int id_);

    // Class accessers and getters

    const std::string& getName() const;
    int getId() const;
    int getNumberOfClassesRegistered() const;

    void setStudentName(const std::string& name_);
    void setStudentId(int id);


    // Class methods
    void addClass(const std::string& ucCode, const std::string& classCode);
    std::vector<std::string> getUnitCourses();
    const std::string& getClass(const std::string& unitCourse);
};


#endif //AED_PROJ_STUDENT_H
