#ifndef NOTICE_H_INCLUDED
#define NOTICE_H_INCLUDED
#define ESC 27

#include <stdlib.h>
#include<stdio.h>
#include<string.h>

/*
*	examScore : scores of midterm and final exam
*	assignmentScore : assign five times
*/
typedef struct student
{
	char id[10];
	char name[20];
	double examScore[2];
	double assignmentScore[5];
}STUDENT;

/*
*	student : array of students in a course
*	studentCount : the number of students in a course
*/
typedef struct course
{
	STUDENT student[100];
	int studentCount;
	char name[40];
	char notice[10][50];
	char assignment[5][50];
}COURSE;

void RegisterNotice(COURSE *course);
void ModifyNotice(COURSE *course);
void DeleteNotice(COURSE *course);
void PrintNotice(COURSE *course);


#endif // STUDENT_H_INCLUDED