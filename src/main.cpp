#include <iostream>
#include "../include/CourseManager.h"
int main() {
    CourseManager course;
    course.showStudentListInYear(1, 10);
    course.showClassSchedule("L.EIC001", "1LEIC01");
    course.showStudentSchedule(202024212);
    return 0;
}
