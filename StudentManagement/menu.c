#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

#define PRINTTYPE_ALL 3

void SystemSet()
{
	system("title  Student Management");
}

/*
*   COURSE **course - the array of structure which want to manage in course menu.
*   int *courseCount - the number of course
*   char menuinput - the input of user that is used for selecting function
*
*   CourseMenu receive one character from user and use it to select the menu of course.
*/
void CourseMenu(COURSE **course, int *courseCount)
{
	char menuInput;

	for (;;)
	{
		PrintCourseMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterCourse(course, courseCount);
			break;

		case '2':
			ModifyCourse(course, courseCount);
			break;

		case '3':
			DeleteCourse(course, courseCount);
			break;

		case '4':
			SelectCourse(course, courseCount);
			break;

		case '5':
			exit(1);
			break;

		default:
			break;
		}
	}
}

/*
*	COURSE *course - the course that user want to manage in array of course.
*	char menuinput - the input of user that is used for selecting function
*
*	ManagementMenu receive one character from user and use it to select the function of management.
*/
void ManagementMenu(COURSE *course)
{
	char menuInput;

	for (;;)
	{
		PrintManagementMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			ScoreMenu(course);
			break;

		case '2':
			AssignmentMenu(course);
			break;

		case '3':
			StudentMenu(course);
			break;

		case '4':
			NoticeMenu(course);
			break;

		case '5':
			ReadFile(course);
			break;

		case '6':
			WriteFile(course);
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}

/* 4.Manage -> 1.Score */
void ScoreMenu(COURSE *course)
{
	char menuInput;

	for (;;)
	{
		PrintScoreMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterScore(course);
			break;

		case '2':
			ModifyScore(course);
			break;

		case '3':
			DeleteScore(course);
			break;

		case '4':
			PrintScore(course, PRINTTYPE_ALL, 0);
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}



/* 4.Manage -> 2.Assignment */
void AssignmentMenu(COURSE *course)
{
	char menuInput;

	for (;;)
	{
		PrintAssignmentMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterAssignment(course);
			break;

		case '2':
			ModifyAssignment(course);
			break;

		case '3':
			DeleteAssignment(course);
			break;

		case '4':
			PrintAssignment(course);
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}



/* 4.Manage -> 3.Student */
void StudentMenu(COURSE *course)
{
	char menuInput;

	for (;;)
	{
		PrintStudentMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterStudent(course);
			break;

		case '2':
			ModifyStudent(course);
			break;

		case '3':
			DeleteStudent(course);
			break;

		case '4':
			PrintStudent(course);
			system("pause"); //Press any key to continue..
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}

/* 4.Manage -> 4.Notice */
void NoticeMenu(COURSE *course)
{
	char menuInput;

	for (;;)
	{
		PrintNoticeMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterNotice(course);
			break;

		case '2':
			ModifyNotice(course);
			break;

		case '3':
			DeleteNotice(course);
			break;

		case '4':
			PrintNotice(course);
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}