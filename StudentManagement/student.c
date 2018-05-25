#include <stdio.h>
#include <stdlib.h>
#include "student.h"

/*
*	 The function defines the order of the elements by returning.
*	 Taking two pointers as arguments (both converted to const void *).
*
*	 return value < 0 : student1<student2
*	 return value = 0 : student1=student2
*	 return value > 0 : student1>student2
*/
int CompareID(const void *elem1, const void *elem2)
{
	STUDENT *student1 = (STUDENT*)elem1;
	STUDENT *student2 = (STUDENT*)elem2;
	return strcmp((student1->id), (student2->id));
}

/*
*	This function searchs for a student by student ID
*	return valuse(searchStudent) : index of the student selected in student array.
*								   It is found through repetitive statement.
*/
int SearchID(COURSE* course)
{
	int searchStudent = -1;
	char selectID[10];

	printf("\n   Enter ID of student to select : ");
	scanf("%s", selectID);

	for (int i = 0; i < course->studentCount; i++)
	{
		if (strcmp(course->student[i].id, selectID) == 0)
		{
			searchStudent = i;
			break;
		}
	}
	return searchStudent;
}

/*
*	int currentStudentCnt : current the number of student in this course
*	int checkRegister : check if registration is possible to avoid duplicate student ID in a course
*
*	If ID of new student is not duplicated (checkRegister!=0), enter the name of the student you want to add.
*	The name and ID entered (addID, addName) are inserted into current index of the student array,
*	and the number of students in this course increases.
*/
void RegisterStudent(COURSE *course)
{
	int currentStudentCnt;
	int checkRegister;
	char addID[10];
	char addName[20];

	PrintRegisterStudent();
	scanf("%s", addID);

	for (int i = 0; i < course->studentCount; i++)
	{
		if (strcmp(course->student[i].id, addID) == 0)
		{
			checkRegister = 0;
			break;
		}
	}

	if (checkRegister == 0)
	{
		system("cls");
		printf("\n\n   student [%s] already exists in this course..", addID);
	}
	else
	{
		PrintRegisterStudentName();
		scanf("%s", addName);

		currentStudentCnt = course->studentCount;
		strcpy(course->student[currentStudentCnt].id, addID);
		strcpy(course->student[currentStudentCnt].name, addName);
		course->studentCount++;

		system("cls");
		printf("\n\n   ** Student has successfully been registered! **");
	}

	printf("\n   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/*
*	int searchStudent : index of the student you want to modify. (return value of SearchID function)
*
*	If the student you want to modify is in student array (searchStudent!=1), you can change name of the student (newName).
*/
void ModifyStudent(COURSE *course)
{
	int searchStudent; //index
	char newName[20];

	PrintStudent(course);

	searchStudent = SearchID(course);

	if (searchStudent == -1)
	{
		system("cls");
		printf("\n\n   No student ID found..");
	}
	else
	{
		PrintModifyStudentName();
		scanf("%s", newName);

		strcpy(course->student[searchStudent].name, newName);

		system("cls");
		printf("\n\n   ** Student has successfully been modified! **\n");
	}

	printf("\n   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/*
*	char checkDelete : a variable used to input whether to delete or not.
*
*	Find students to delete by using SearchID function.
*	If the checkDelete is 'y'/'Y', the next student of student to delete will be covered with data, and the array is pulling forwards.
*	Then, the number of students in this course decreases.
*/
void DeleteStudent(COURSE *course)
{
	int searchStudent;
	char checkDelete;

	PrintStudent(course);

	searchStudent = SearchID(course);

	if (searchStudent == -1)
	{
		system("cls");
		printf("\n\n   No student ID found..");
	}
	else
	{
		PrintDeleteStudent();

		checkDelete = getche();

		if (checkDelete == 'y' || checkDelete == 'Y')
		{
			for (int i = 0; i < course->studentCount - 1; i++)
			{
				course->student[i] = course->student[i + 1];
			}
			course->studentCount--;
			system("cls");
			printf("\n\n   ** Student has successfully been deleted! **");
		}
		else if (checkDelete == 'n' || checkDelete == 'N')
		{
		}
		else
		{
			system("cls");
			printf("\n\n   Wrong input..");
		}
	}
	printf("\n   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/*
*	If a student exists in this course, the print function will be performed.
*
*	qsort() - This function arranges the list of students in ascending order by student ID
*	1) course->student : Point of start the target array
*	2) course->studentCount : Array size for the element
*	3) sizeof(STUDENT) : Element size in bytes
*	4) CompareID : Pointer to a function that compares two elements. This function is called repeatedly by qsort to compare two elements
*/
void PrintStudent(COURSE *course)
{
	if (course->studentCount == 0)
	{
		printf("\n\n   There are no students in this class..\n");
	}
	else
	{
		printf("\n\t\t<< Student List >> \n\n");
		printf("\t  ID		Name		\n");
		printf("	===================================\n");

		qsort(course->student, course->studentCount, sizeof(STUDENT), CompareID);

		for (int i = 0; i < course->studentCount; i++)
		{
			printf("	  %s	%s	\n", course->student[i].id, course->student[i].name);
		}
		printf("\n\n");
	}
}