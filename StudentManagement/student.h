#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
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

int CompareID(const void *elem1, const void *elem2);
int SearchID(COURSE* course);
void SystemSet();
void WriteFile(COURSE *course);
void ReadFile(COURSE *course);
void SystemSet();
void PrintCourseMenu();
void PrintManagementMenu();
void PrintScoreMenu();
void PrintAssignmentMenu();
void PrintStudentMenu();
void PrintNoticeMenu();
void InitCourse(COURSE *course);
void PrintCourseList(COURSE **course, int *courseCount);
void CourseMenu(COURSE **course, int *courseCount);
void RegisterCourse(COURSE **course, int *courseCount);
void ModifyCourse(COURSE **course, int *courseCount);
void DeleteCourse(COURSE **course, int *courseCount);
void SelectCourse(COURSE **course, int *courseCount);
void ManagementMenu(COURSE *course);
void ScoreMenu(COURSE *course);
void RegisterScore(COURSE *course);
void ModifyScore(COURSE *course);
void DeleteScore(COURSE *course);
void PrintScore(COURSE *course, int printType, int studentIndex);
void AverageCourseScore(COURSE *course);
void AssignmentMenu(COURSE *course);
void RegisterAssignment(COURSE *course);
void ModifyAssignment(COURSE *course);
void DeleteAssignment(COURSE *course);
void PrintAssignment(COURSE *course);
void StudentMenu(COURSE *course);
void RegisterStudent(COURSE *course);
void ModifyStudent(COURSE *course);
void DeleteStudent(COURSE *course);
void PrintStudent(COURSE *course);
void NoticeMenu(COURSE *course);
void RegisterNotice(COURSE *course);
void ModifyNotice(COURSE *course);
void DeleteNotice(COURSE *course);
void PrintNotice(COURSE *course);
void PrintToRegisterCourse();
void PrintToModifyCourse();
void PrintToModifyNameOfCourse();
void PrintToDeleteCourse();
void PrintSelectCourse();
void PrintIDToRegisterScore();
void PrintMidtermScoreToRegisterScore();
void PrintFinalScoreToRegisterScore();
void PrintIDToModifyScore();
void PrintMidtermScoreToModifyScore();
void PrintFinalScoreToModifyScore();
void PrintIDToDeleteScore();
void PrintAssignmentToRegister();
void PrintAssignmentToModify();
void PrintCommentsOfAssignmentToModify();
void PrintAssignmentToDelete();
void PrintStudentToRegister();
void PrintStudentToRegister();
void PrintNameOfStudentToRegister();
void PrintNameOfStudentToModify();
void PrintStudentToDelete();
void PrintNoticeToRegister();

#endif // STUDENT_H_INCLUDED
