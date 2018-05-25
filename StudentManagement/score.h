#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#define ESC 27

#include "menu.h"

void RegisterScore(COURSE *course);
void ModifyScore(COURSE *course);
void DeleteScore(COURSE *course);
void PrintScore(COURSE *course, int printType, int studentIndex);
void AverageCourseScore(COURSE *course);


#endif // STUDENT_H_INCLUDED