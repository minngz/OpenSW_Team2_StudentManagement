#include <stdio.h>
#include <stdlib.h>
//#include "management.h"
#include "assignment.h"

/*
*	If user wants to register assignment of course, this RegisterAssignment function will be performed.
*
*	1) Getting input comments of an assignment from user
*	2) Comments of an assignment will be stored in 'assignment' array in course structure
*/
void RegisterAssignment(COURSE *course)
{
	int i;
	char assignmentComment[50];

	PrintRegisterAssignment();

	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';

	for (i = 0; i < 5; i++)
	{
		if (strlen(course->assignment[i]) == 0)
		{
			strcpy((*course).assignment[i], assignmentComment);
			break;
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully registed!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

/*
*	If user wants to modify assignment of course, this ModifyAssignment function will be performed.
*
*	1) Getting input number of an assignment which wants to modify from user
*	2) Getting input comments of assignment to modify.
*	3) New comments of an assignment will be stored in 'assignment' array in course structure
*/
void ModifyAssignment(COURSE *course)
{
	int assignmentNumber = 0;
	int i = 0;
	char assignmentComment[50];

	PrintAssignment(course);
	printf("\n\n\n\n\n\n\n\n");
	PrintModifyAssignment();
	printf("\033[11;13H:  ");

	scanf("%d", &assignmentNumber);
	getchar();

	assignmentNumber--;

	PrintModifyAssignmentComments();

	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';

	for (i = 0; i < 5; i++)
	{
		if (i == assignmentNumber)
		{
			strcpy((*course).assignment[i], assignmentComment);
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully modified!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

/*
*	If user wants to delete assignment of course, this DeleteAssignment function will be performed.
*
*	1) Getting input number of an assignment which wants to delete from user
*	2) Comments of an assignment will be deleted in 'assignment' array in course structure
*/
void DeleteAssignment(COURSE *course)
{
	int i = 0, j = 0;
	int assignmentNumber = 0;

	for (j = 0; j < 5; j++)
	{
		if (!(strlen(course->assignment[j]) == 0))
		{
			break;
		}
		else if (j == 4 && strlen(course->assignment[j]) == 0)
		{
			system("cls");
			printf("\n\n   There is no assignments. Please register an assignment first.\n\n");
			printf("   It will return to assignment menu 3 seconds later");
			Sleep(3000);
			return;
		}
	}

	PrintAssignment(course);
	PrintDeleteAssignment();

	scanf("%d", &assignmentNumber);
	assignmentNumber--;

	for (i = 0; i < 5; i++)
	{
		if (i == assignmentNumber)
		{
			strcpy((*course).assignment[i], "");
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully deleted!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

/*
*	If user wants to print assignment of course, this PrintAssignment function will be performed.
*	Print a list of assignments for 3 seconds.
*/
void PrintAssignment(COURSE *course)
{
	int i = 0;
	int assignmentNumber = 0;

	for (i = 0; i < 5; i++)
	{
		assignmentNumber = i + 1;
		printf("\n\n   %d %s\n", assignmentNumber, (*course).assignment[i]);
	}
	printf("\n\n   It will return to assignment menu 3 seconds later\n");
	Sleep(3000);
}