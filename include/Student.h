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
/**
 * @class Student
 * @brief Represents a student with associated course registrations.
 */
class Student {
private:
    std::string name; ///< The name of the student.
    int identifier;  ///< The unique identifier (ID) of the student.
    std::unordered_map<std::string, std::string> classesRegistered; ///< A map of unit course IDs to class IDs.


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
    bool addClass(const std::string& ucCode, const std::string& classCode);
    std::vector<std::string> getUnitCourses();
    const std::string& getClass(const std::string& unitCourse);
    void removeClass(const std::string& ucId);
    std::shared_ptr<std::unordered_map<std::string, std::string>> getClasses();
    bool checkEnrollment(const std::string& ucId) const;
};


#endif //AED_PROJ_STUDENT_H
