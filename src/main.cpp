#include <iostream>
#include "../include/CourseManager.h"
int main() {
    CourseManager informatica;
    informatica.showStudentListInYear(1, 10);
    informatica.showClassSchedule("L.EIC001", "1LEIC01");
    informatica.showStudentSchedule(202024212);
    informatica.showUnitCoursesWithMostStudents(10);
    return 0;
}
