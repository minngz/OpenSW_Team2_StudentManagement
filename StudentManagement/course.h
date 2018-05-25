#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED
#define ESC 27

#include "menu.h"

void InitCourse(COURSE *course);
void PrintCourseList(COURSE **course, int *courseCount);
void RegisterCourse(COURSE **course, int *courseCount);
void ModifyCourse(COURSE **course, int *courseCount);
void DeleteCourse(COURSE **course, int *courseCount);
void SelectCourse(COURSE **course, int *courseCount);


#endif // STUDENT_H_INCLUDED