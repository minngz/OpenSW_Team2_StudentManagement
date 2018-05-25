#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#define ESC 27

#include "menu.h"

int CompareID(const void *elem1, const void *elem2);
int SearchID(COURSE* course);
void RegisterStudent(COURSE *course);
void ModifyStudent(COURSE *course);
void DeleteStudent(COURSE *course);
void PrintStudent(COURSE *course);


#endif // STUDENT_H_INCLUDED