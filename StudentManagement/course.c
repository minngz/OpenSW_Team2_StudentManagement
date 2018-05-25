#include <stdio.h>
#include <stdlib.h>
//#include "management.h"
#include "course.h"

#define MAX_ASSIGNMENT 5
#define MAX_NOTICE 10

/*
*   COURSE **course - the array of structure which want to print
*   int *coursecount - the number of course
*
*   PrintCourseList prints the name list of COURSE structure array
*/
void PrintCourseList(COURSE **course, int *courseCount)
{
	int i;

	printf("\n\n\n\n\n\n\n\n");
	for (i = 0; i < *courseCount; i++)
	{
		printf("       %d.   %15s\n", i + 1, (*course)[i].name);
	}
}

/*
*   COURSE **course - the array of structure that user want to select.
*   int *coursecount - the number of course
*   int index - the input of user that is used for selecting function.
*
*   SelectCourse prints the list of course and receives input(inex) from the user. Then it calls
*   management menu with the one component of COURSE array that user selected.
*/
void SelectCourse(COURSE **course, int *courseCount)
{
	int index;

	// If there is no course, It doesn't work.
	if (*courseCount > 0)
	{
		PrintSelectCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");

		scanf("%d", &index);
		getchar();
		index--;

		ManagementMenu(&((*course)[index]));
	}
	else
	{
		system("cls");
		printf("\n\n   There is no course to select.\n");
		printf("   It will return to course menu 3 seconds later\n");
		Sleep(3000);
	}
}

/*
*   COURSE *course - the component of array of COURSE structre which want to initialize
*
*   InitCourse function initialize data of COURSE structure as null string.
*   The data are assignment(char[]), notice(char[]), studentCount(int)
*/
void InitCourse(COURSE *course)
{
	int i;

	for (i = 0; i < MAX_ASSIGNMENT; i++)
	{
		strcpy((*course).assignment[i], "");
	}

	for (i = 0; i < MAX_NOTICE; i++)
	{
		strcpy((*course).notice[i], "");
	}

	(*course).studentCount = 0;
}

/*
*   COURSE **course - the array of structure that new course would be addded.
*   int *coursecount - the number of course
*   int courseName[40] - the temporary variable which receive the string of course name from user.
*
*   1) RegisterCourse receive the name of new course from user.
*
*   2-1) If there is no component in COURSE array,
*   it allocate the array dynamically which size is one COURSE.
*
*   2-2) If there are components in COURSE array,
*   it allocate new array dynamically which size is courseCount+1.
*   It copy the existing array to new array and copy the receiving name to new component of array.
*   Then, add this new component to new array. Finally, it free the existing array.
*/
void RegisterCourse(COURSE **course, int *courseCount)
{
	int i;
	char courseName[40];

	PrintRegisterCourse();
	fgets(courseName, sizeof(courseName), stdin);
	courseName[strlen(courseName) - 1] = '\0';

	if (*courseCount == 0)
	{
		*course = (COURSE*)malloc(sizeof(COURSE));
	}
	else
	{
		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*courseCount + 1));

		for (i = 0; i < *courseCount; i++)
		{
			temp[i] = (*course)[i];
		}

		free(*course);
		*course = temp;
	}

	InitCourse(&((*course)[*courseCount]));

	strcpy((*course)[*courseCount].name, courseName);
	*courseCount += 1;

	system("cls");
	printf("\n\n   [ %s ] course is successfully registed!\n\n", (*course)[*courseCount - 1].name);
	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/*
*   COURSE **course - the array of structure that user would change.
*   int *coursecount - the number of course
*   int newName[40] - the temporary variable which receive the string of course name from user.
*
*   1) If there is course in **course, it prints the list of course. Then It receives the index of what
*   the user want to modify and also receives the new name of course. Finally, it changes the course's
*   name that user selected.
*
*   2) If not, it notify user that there is no course and would not modify anything.
*/
void ModifyCourse(COURSE **course, int *courseCount)
{
	int index;
	char newName[40];

	if (*courseCount > 0)
	{
		PrintModifyCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");
		scanf("%d", &index);

		index--;
		getchar(); // Using getchar() for excluding enter key when using fgets below.

		PrintModifyCourseName();
		fgets(newName, sizeof(newName), stdin);
		newName[strlen(newName) - 1] = '\0'; // Because fgets receive \n(Enter), it needs to exclude it.

		strcpy((*course)[index].name, newName);

		system("cls");
		printf("\n\n   course is successfully modified!\n");
	}
	else
	{
		system("cls");
		printf("\n\n   There is nothing to modify.\n");
	}

	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/*
*	COURSE **course - the array of structure that user would delete.
*	int *coursecount - the number of course
*	int deleteIndex - the index of components in COURSE array which user want to delete.
*	int countIndex - this variable is used for counting index of new array
*					 because it should copy existing array excluding selected index to new array.
*
*	1-1) If there is course in **course, it prints the list of course.
*	Then It receives the index of what the user want to delete.
*	1-2) Then, it allocates new array dynamically which size is (existing array size -1 )
*	because this function delete on component in array.
*	1-3) And it copies existing array to new array excluding selected components.
*	1-4) Finally, it free existing array of COURSE structure.
*
*	2) If not, it notify user that there is no course and would not delete anything.
*/
void DeleteCourse(COURSE **course, int *courseCount)
{
	int i;
	int deleteIndex;
	int countIndex;

	if (*courseCount == 0)
	{
		system("cls");
		printf("\n\n   There is nothing to delete\n");
	}
	else
	{
		PrintDeleteCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");
		scanf("%d", &deleteIndex);

		getchar();
		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*courseCount - 1));

		countIndex = 0;
		deleteIndex--;

		for (i = 0; i < *courseCount; i++)
		{
			if (i != deleteIndex)
			{
				temp[countIndex] = (*course)[i];
				countIndex++;
			}
		}

		free(*course);
		*course = temp;

		*courseCount -= 1;

		system("cls");
		printf("\n\n   course is successfully deleted!\n\n");
	}

	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);

}

