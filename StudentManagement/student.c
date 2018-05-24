#include <stdio.h>
#include <stdlib.h>
#include "student.h"

#define PRINTTYPE_EDIT 1
#define PRINTTYPE_DELETE 2
#define PRINTTYPE_ALL 3

void SystemSet()
{
	system("title  Student Management");
}

/*********************************************************************************
	 The function defines the order of the elements by returning.
	 Taking two pointers as arguments (both converted to const void *).

	 return value < 0 : student1<student2
	 return value = 0 : student1=student2
	 return value > 0 : student1>student2
**********************************************************************************/
int CompareID(const void *elem1, const void *elem2)
{
	STUDENT *student1 = (STUDENT*)elem1;
	STUDENT *student2 = (STUDENT*)elem2;
	return strcmp((student1->id), (student2->id));
}

/*********************************************************************************
	This function searchs for a student by student ID 
	return valuse(searchStudent) : index of the student selected in student array.
								   It is found through repetitive statement.
**********************************************************************************/
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

void WriteFile(COURSE *course)
{
	FILE *file;        // file variables to open, write, and close the txt file
	int i, j;           // int variables for "for statement"
	int noticeCount;
	int assignmentCount;
	system("cls");
	file = fopen("sample_course.txt", "w");									 

	if (file == NULL)
	{
		printf("\n\n   Cannot open the file\n");
		exit(0);
	} // "sample_course.txt" doesnt' exist
	else
	{
		fprintf(file, "%d\n", (*course).studentCount);  
														
		for (i = 0; i <  (*course).studentCount; i++)
		{
			fprintf(file, "%s %s ", (*course).student[i].id, (*course).student[i].name);

			for (j = 0; j < 2; j++)
			{
				fprintf(file, "%-8.2f", (*course).student[i].examScore[j]);
			}

			for (j = 0; j < 5; j++)
			{
				fprintf(file, "%-8.2f", (*course).student[i].assignmentScore[j]);
			}

			fprintf(file, "\n");
		}

		noticeCount = 0;

		for (i = 0; i < 10; i++)
		{
			if (strlen((*course).notice[i]) != 0)
			{
				noticeCount++;
			}
		}

		fprintf(file, "%d\n", noticeCount);

		for (i = 0; i < noticeCount; i++)
		{
			fprintf(file, "%s\n", (*course).notice[i]);
		}

		assignmentCount = 0;

		for (i = 0; i < 5; i++)
		{
			if (strlen((*course).assignment[i]) != 0)
			{
				assignmentCount++;
			}
		}

		fprintf(file, "%d\n", assignmentCount);

		for (i = 0; i <assignmentCount; i++)
		{
			fprintf(file, "%s\n", (*course).assignment[i]);
		}

	} // "sample_course.txt" exist

	fclose(file);   // close the file
	printf("\n\n   Write data is successfully done!\n\n");
	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);
}

void ReadFile(COURSE *course)
{
	int i, j;        
	int studentCount;
	int existNoticeCount;
	int existAssignmentCount;
	int newNoticeCount;
	int newAssignmentCount;
	system("cls");
	FILE *file;         // file variables to open, write, and close the txt file
	file = fopen("sample_course.txt", "r"); // open "sample_course.txt" file by "read" mode. 

	if (file == NULL)
	{
		printf("\n\n   Cannot open the file\n");
		exit(0);
	} // "sample_course.txt" doesnt' exist
	else
	{
		fscanf(file, "%d", &studentCount);   
		fscanf(file, "\n");

		// Read all information of student array on the next row.
		for (i = course->studentCount; i < course->studentCount+studentCount; i++)
		{
			fscanf(file, "%s%s%",(*course).student[i].id, (*course).student[i].name);
			fscanf(file, "%lf%lf", (*course).student[i].examScore, (*course).student[i].examScore+1);		

			for (j = 0; j < 5; j++)
			{
				fscanf(file, "%lf", (*course).student[i].assignmentScore+j);
			}
			fscanf(file, "\n");
		}

		(*course).studentCount += studentCount;

		fscanf(file, "%d", &newNoticeCount);
		fscanf(file, "\n");

		existNoticeCount = 0;

		for (i = 0; i < 10; i++)
		{
			if (strlen((*course).notice[i]) != 0)
			{
				existNoticeCount++;
			}
		}

		for (i = 0; i < newNoticeCount; i++)
		{
			fgets((*course).notice[existNoticeCount + i], sizeof((*course).notice[existNoticeCount + i]),file);
			(*course).notice[existNoticeCount + i][strlen((*course).notice[existNoticeCount + i]) - 1] = '\0';
		}

		fscanf(file, "%d", &newAssignmentCount);
		fscanf(file, "\n");

		existAssignmentCount = 0;

		for (i = 0; i < 5; i++)
		{
			if (strlen((*course).assignment[i]) != 0)
			{
				existAssignmentCount++;
			}
		}

		for (i = 0; i < newAssignmentCount; i++)
		{
			fgets((*course).assignment[existAssignmentCount + i], sizeof((*course).assignment[existAssignmentCount + i]), file);
			(*course).assignment[existAssignmentCount + i][strlen((*course).assignment[existAssignmentCount + i]) - 1] = '\0';
		}

		printf("\n\n   File data is successfully loaded!\n\n");
		printf("\n   It will return to course menu 3 seconds later");
		Sleep(3000);

	} // "sample_course.txt" exist

	fclose(file);  // close the file
}


void PrintCourseMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                       [ Course ]                       弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Register                        弛\n");
	printf("  弛                 2.     Modifiy                         弛\n");
	printf("  弛                 3      Delete                          弛\n");
	printf("  弛                 4.     Manage                          弛\n");
	printf("  弛                 5.     Exit                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");

}

void PrintManagementMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                    [ Management ]                      弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Score                           弛\n");
	printf("  弛                 2.     Assignment                      弛\n");
	printf("  弛                 3      Student                         弛\n");
	printf("  弛                 4.     Notice                          弛\n");
	printf("  弛                 5.     Read File                       弛\n");
	printf("  弛                 6.     Write File                      弛\n");
	printf("  弛                 ESC.   Back                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");
}

void PrintScoreMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                       [ Score ]                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Register                        弛\n");
	printf("  弛                 2.     Modifiy                         弛\n");
	printf("  弛                 3      Delete                          弛\n");
	printf("  弛                 4.     Print                           弛\n");
	printf("  弛                 ESC.   Back                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");
}

void PrintAssignmentMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                     [ Assignment ]                     弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Register                        弛\n");
	printf("  弛                 2.     Modifiy                         弛\n");
	printf("  弛                 3      Delete                          弛\n");
	printf("  弛                 4.     Print                           弛\n");
	printf("  弛                 ESC.   Back                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");
}

void PrintStudentMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                      [ Student ]                       弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Register                        弛\n");
	printf("  弛                 2.     Modifiy                         弛\n");
	printf("  弛                 3      Delete                          弛\n");
	printf("  弛                 4.     Print                           弛\n");
	printf("  弛                 ESC.   Back                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");
}

void PrintNoticeMenu()
{
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                      [ Notice ]                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                 1.     Register                        弛\n");
	printf("  弛                 2.     Modifiy                         弛\n");
	printf("  弛                 3      Delete                          弛\n");
	printf("  弛                 4.     Print                           弛\n");
	printf("  弛                 ESC.   Back                            弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("                               Select number to execute : ");
}

void PrintCourseList(COURSE **course, int *courseCount)
{
	int i;

	printf("\n\n\n\n\n\n\n\n");
	for (i = 0; i < *courseCount; i++)
	{
		printf("       %d.   %15s\n", i+1, (*course)[i].name);
	}
}

void CourseMenu(COURSE **course, int *courseCount)
{
	char menuInput;

	while (1)
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

void SelectCourse(COURSE **course, int *courseCount)
{
	int index;

	if (*courseCount > 0)
	{
		PrintSelectCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");
		scanf("%d", &index);
		index--;
		getchar();

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

void PrintSelectCourse() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease select number of a course to manage");
}

void RegisterCourse(COURSE **course, int *courseCount)
{
	int i;
	char courseName[40];

	PrintToRegisterCourse();
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


	(*course)[*courseCount].studentCount = 0;

	InitAssignment(&((*course)[*courseCount]));
	InitNotice(&((*course)[*courseCount]));


	strcpy((*course)[*courseCount].name, courseName);
	*courseCount += 1;

	system("cls");
	printf("\n\n   [ %s ] course is successfully registed!\n\n", (*course)[*courseCount - 1].name);
	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);
}

void InitAssignment(COURSE *course){
	int i;

	for (i = 0; i < 5; i++)
	{
		strcpy((*course).assignment[i], "");
	}
}

void PrintToRegisterCourse() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease insert name of new subject");
	printf("\033[11;13H:  ");
}

void InitNotice(COURSE *course)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		strcpy((*course).notice[i], "");
	}
}

void ModifyCourse(COURSE **course, int *courseCount)
{
	int index;
	char newName[20];

	if (*courseCount > 0)
	{
		PrintToModifyCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");
		scanf("%d", &index);
		index--;
		getchar();

		PrintToModifyNameOfCourse();
		fgets(newName, sizeof(newName), stdin);
		newName[strlen(newName) - 1] = '\0';
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

void PrintToModifyCourse() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease insert number what you want to modify");
	printf("\033[11;13H:  ");
}

void PrintToModifyNameOfCourse() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease enter the new name of course");
	printf("\033[11;13H:  ");
}

void DeleteCourse(COURSE **course, int *courseCount)
{
	int i, j;
	int index;
	int newIndex;

	if (*courseCount == 0)
	{
		system("cls");
		printf("\n\n   There is nothing to delete\n");
	}
	else
	{
		PrintToDeleteCourse();
		PrintCourseList(course, courseCount);
		printf("\033[11;13H:  ");
		scanf("%d", &index);
		getchar();
		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*courseCount - 1));

		newIndex = 0;
		index--;

		for (i = 0; i < *courseCount; i++)
		{
			if (i != index)
			{
				temp[newIndex] = (*course)[i];
				newIndex++;
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

void PrintToDeleteCourse() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease insert number what you want to delete");
	printf("\033[11;13H:  ");
}

void ManagementMenu(COURSE *course)
{
	char menuInput;

	while (1)
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

void ScoreMenu(COURSE *course)
{
	char menuInput;

	while (1)
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

/***************************************************************************************************************************************************
	If user wants to register score of student, this RegisterScore function will be performed.

	1) Getting input studentID from user
	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
	2-2) If studentId exists, user has to input midterm-score and final-score to register.
	3) Informations about scores will be stored in 'examScore' array which index of 0 means midterm-score and index of 1 means final-score.
		(You have to input score from 0 to 100. Because deleted score will be treated as 300)
	4)After this process, the score will be registered in student's examScore variable who user input.
***************************************************************************************************************************************************/

void RegisterScore(COURSE *course)
{
	
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;
	void PrintIDToRegisterScore();
	scanf("%s", studentID);
	printf("\n");

	//studentCount means number of students in selected course
	for (int i = 0; i < course->studentCount; i++)
	{
		if (strcmp(course->student[i].id, studentID) == 0)
		{
			studentIndex = i;
			break;
		}
	}

	if (studentIndex == -1) // -1 means unregistered student.
	{
		system("cls");
		printf("\n\n   There is no student who you entered\n");
		printf("   It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		return;
	}

	PrintMidtermScoreToRegisterScore();
	scanf("%lf", &midtermScore);
	printf("\n");

	PrintFinalScoreToRegisterScore();
	scanf("%lf", &finalScore);
	printf("\n");

	//examScore[0] means midterm-score and examScore[1] means final-score.
	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	system("cls");
	printf("\n\n   Registration is Succeed!\n");
	printf("(   It will be returned to Score Menu after 3 seconds automatically)");
	Sleep(3000);
}

/***************************************************************************************************************************************************
	If user wants to modify score of student, this ModifyScore function will be performed.

	1) Getting input studentID from user
	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
	2-2) If studentId exists, user has to input midterm-score and final-score to modify.
	3) Informations about scores will be stored in 'examScore' array which index of 0 means midterm-score and index of 1 means final-score.
		(You have to input score from 0 to 100. Because deleted score will be treated as 300)
	4)After this process, the score will be modified in student's examScore variable who user input.
***************************************************************************************************************************************************/
void PrintIDToRegisterScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput student ID to register score");
	printf("\033[11;13H:  ");
}

void PrintMidtermScoreToRegisterScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput midterm score");
	printf("\033[11;13H:  ");
}

void PrintFinalScoreToRegisterScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput final score");
	printf("\033[11;13H:  ");
}

void ModifyScore(COURSE *course)
{
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	PrintIDToModifyScore();
	scanf("%s", studentID);
	getchar();
	printf("\n");

	for (int i = 0; i < course->studentCount; i++)
	{
		if (strcmp(course->student[i].id, studentID) == 0)
		{
			studentIndex = i;
			break;
		}
	}

	if (studentIndex == -1) //if it doesn't exists
	{
		system("cls");
		printf("\n\n   There is no student who you entered\n");
		printf("   It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		return;
	}

	PrintMidtermScoreToModifyScore();
	scanf("%lf", &midtermScore);
	getchar();

	printf("----------------Scores of you found-------------------------\n");
	PrintScore(course, PRINTTYPE_EDIT, studentIndex);

	PrintFinalScoreToModifyScore();
	printf("----------------Scores of you found-------------------------\n");
	PrintScore(course, PRINTTYPE_EDIT, studentIndex);
	scanf("%lf", &finalScore);
	getchar();

	//examScore[0] means midterm-score and examScore[1] means final-score.
	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	printf("----------------Changed Scores-------------------------\n");
	printf("midterm score what you changed : %.2lf\n", midtermScore);
	printf("final score what you changed : %.2lf\n\n", finalScore);
	system("cls");
	printf("\n\n   ----------------Changed Scores of %s-------------------------\n");
	printf("   midterm score what you changed : %.2lf\n", midtermScore);
	printf("   final score what you changed : %.2lf\n\n", finalScore);

	printf("   Modified Complete!\n");
	printf("   It will be returned to Score Menu after 3 seconds");
	Sleep(3000);
}

/***************************************************************************************************************************************************
	If user wants to delete score of student, this DeleteScore function will be performed.
	
	1) Getting input studentID from user
	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
	2-2) If score was deleted, it will be returned to score menu after 3 seconds automatically.
	3) Ask to user really want to delete score of input student's
	4-1) If confirm is yes, the score will be deleted(modify score to 300)
	4-2) if confrim is no, it will be returned to score menu after 3 secons autmatically.
***************************************************************************************************************************************************/
void PrintIDToModifyScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput student ID to modify score");
	printf("\033[11;13H:  ");
}

void PrintMidtermScoreToModifyScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput midterm score to modify");
	printf("\033[11;13H:  ");
}

void PrintFinalScoreToModifyScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput final score to modify");
	printf("\033[11;13H:  ");
}

void DeleteScore(COURSE *course)
{
	char studentID[10];
	int studentIndex = -1;
	char confirm = ' ';

	PrintIDToDeleteScore();
	scanf("%s", studentID);
	getchar();
	printf("\n");

	for (int i = 0; i < course->studentCount; i++)
	{
		if (strcmp(course->student[i].id, studentID) == 0)
		{
			studentIndex = i;
		}
	}

	if (studentIndex == -1) //if it doesn't exists
	{
		system("cls");
		printf("\n\n   There is no student who you entered\n");
		printf("   It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		return;
	}

	//deleted score is treated as a 300 so if score exceed 100, it is classifid as a deleted score.
	if (course->student[studentIndex].examScore[0] > 100 && course->student[studentIndex].examScore[1] > 100)
	{
		system("cls");
		printf("\n\n   It is already deleted score.\n");
		printf("   It will be returned to Score Menu after 3 seconds...");
		return;
	}

	printf("----------------Scores of you found one's-------------------------\n");
	PrintScore(course, PRINTTYPE_DELETE, studentIndex);

	printf("\nAre you sure of removing it? (Y/N) : ");
	scanf("%c", &confirm);
	getchar();

	if (confirm == 'n' || confirm == 'N')
	{
		system("cls");
		printf("\n\n   Deleteing Score is canceled.\n");
		printf("   It will be returned to Score Menu after 3 seconds");
		Sleep(3000);
		return;
	}

	else if (confirm == 'y' || confirm == 'Y')
	{
		course->student[studentIndex].examScore[0] = 300;
		course->student[studentIndex].examScore[1] = 300;
		system("cls");
		printf("\n\n   Deleted is complete!\n");
		printf("   It will be returned to Score Menu after 3 seconds");
		Sleep(3000);
		return;
	}
}

/***************************************************************************************************************************************************
	If user wants to print score of student or every scores of students and average score of this course, this PrintScore function will be performed.

	1) Classify Print type.
	2-1) If print type is ALL, prints all of students' scores and average score in a course.
	2-2) If print type is editing or deleting, prints a score of one student's who user input.
***************************************************************************************************************************************************/
void PrintScore(COURSE *course, int printType, int studentIndex)
{
	int i;
	int isDeleted;
	// Case every students' scores in this course.

	printf("\n\n");
	if (printType == PRINTTYPE_ALL)
	{
		if (course->studentCount == 0) // Case which a course doesn't have any students.
		{
			system("cls");
			printf("\n\n   No Data Error!\n");
			printf("   It will be returned to Score Menu after 3 seconds\n");
			Sleep(3000);
			return;
		}
		for (i = 0; i < course->studentCount; i++)
		{
			// The reason why classifed specific section is under 0 score means unregistered and over 100(300) means deleted score.
			if (0 <= course->student[i].examScore[0] && course->student[i].examScore[1] <= 100)
			{
				printf("%s %s\n", course->student[i].id, course->student[i].name);
				printf("Midterm Exam : %.2lf / Final Exam : %.2lf\n\n", course->student[i].examScore[0], course->student[i].examScore[1]);
			}
		}
		
		AverageCourseScore(course);
		printf("   It will be returned to Score Menu after 3 seconds\n");
		Sleep(3000);
		return;
	}

	//When only editing and deleting function activated, only a person's score who had been input displayed.
	if (printType == PRINTTYPE_EDIT || printType == PRINTTYPE_DELETE)
	{
		if (course->student[studentIndex].examScore[0] > 100 && course->student[studentIndex].examScore[1] > 100)
		{
			printf("   You didn't register score of studentID: %s\n", course->student[studentIndex].id);
			printf("   It will be returned to Score Menu after 3 seconds");
			Sleep(3000);
			return;
		}
		printf("   Student ID : %s\n", course->student[studentIndex].id);
		printf("   Student Name : %s\n", course->student[studentIndex].name);
		printf("   Midterm Exam Score : %.2lf  | Final Exam Score : %.2lf\n\n", course->student[studentIndex].examScore[0], course->student[studentIndex].examScore[1]);
	}
}

	// Case every students' scores in this course.
void PrintIDToDeleteScore() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HInput student ID to Delete Score");
	printf("\033[11;13H:  ");
}



/***************************************************************************************************************************************************
	If print-type was PRINTTYPE_ALL in PrintScore function, this method is called. 

	1) Classify Print type.
	2) Using for loop, every scores of midterm-score add to midtermSum and every scores of final-score add to finalSum.
	3) _register_count is counting only registered score of registered students.
***************************************************************************************************************************************************/
void AverageCourseScore(COURSE *course)
{
	int i;
	int midterm_registerd_count = 0;
	int final_registered_count = 0;
	double midtermSum = 0;
	double finalSum = 0;
	double average_midterm = 0;
	double average_final = 0;

	for (i = 0; i < course->studentCount; i++)
	{
		if (0 <= course->student[i].examScore[0] && course->student[i].examScore[0] <= 100)
		{
			midtermSum = midtermSum + course->student[i].examScore[0];
			midterm_registerd_count = midterm_registerd_count + 1;
		}

		if (0 <= course->student[i].examScore[1] && course->student[i].examScore[1] <= 100)
		{
			finalSum = finalSum + course->student[i].examScore[1];
			final_registered_count = final_registered_count + 1;
		}
	}

	average_midterm = midtermSum / (midterm_registerd_count);
	average_final = finalSum / (final_registered_count);

	if (midterm_registerd_count > 0 && final_registered_count > 0)
	{
		printf("Average score of midterm for %s course is %.2lf\n", course->name, average_midterm);
		printf("Average score of final for %s course is %.2lf\n\n", course->name, average_final);
	}

	Sleep(3000);
}

void WriteScoreFile()
{

}

void AssignmentMenu(COURSE *course)
{
	char menuInput;
	while (1)
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

void RegisterAssignment(COURSE *course)
{
	int i;
	char assignmentComment[50];

	PrintAssignmentToRegister();
	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';

	for (i = 0; i < 5; i++) {
		if (strlen(course->assignment[i]) == 0) {
			strcpy((*course).assignment[i], assignmentComment);
			break;
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully registed!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

void PrintAssignmentToRegister() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease insert comments of a new assignment");
	printf("\033[11;13H:  ");
}

void ModifyAssignment(COURSE *course)
{
	int assignmentNumber = 0;
	int i = 0;
	char assignmentComment[50];

	PrintAssignment(course);
	printf("\n\n\n\n\n\n\n\n");
	PrintAssignmentToModify();
	printf("\033[11;13H:  ");
	
	scanf("%d", &assignmentNumber);
	getchar();
	assignmentNumber--;

	PrintCommentsOfAssignmentToModify();
	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';

	for (i = 0; i < 5; i++) {
		if (i == assignmentNumber) {
			strcpy((*course).assignment[i], assignmentComment);
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully modified!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

void PrintAssignmentToModify() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HWhich assignment do you want to modify?");
	printf("\033[11;13H:  ");
}

void PrintCommentsOfAssignmentToModify() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HPlease insert comments about an assignment");
	printf("\033[11;13H:  ");
}

void DeleteAssignment(COURSE *course)
{
	int i = 0, j = 0;
	for (j = 0; j < 5; j++) {
		if (!(strlen(course->assignment[j]) == 0)) {
			break;
		}
		else if (j == 4 && strlen(course->assignment[j]) == 0) {
			system("cls");
			printf("\n\n   There is no assignments. Please register an assignment first.\n\n");
			printf("   It will return to assignment menu 3 seconds later");
			Sleep(3000);
			return;
		}
	}

	PrintAssignment(course);
	int assignmentNumber = 0;
	
	PrintAssignmentToDelete();
	scanf("%d", &assignmentNumber);
	assignmentNumber--;
	for (i = 0; i < 5; i++) {
		if (i == assignmentNumber) {
			strcpy((*course).assignment[i], "");
		}
	}
	system("cls");
	printf("\n\n   comments about an assignment is successfully deleted!\n\n");
	printf("   It will return to assignment menu 3 seconds later");
	Sleep(3000);
}

void PrintAssignmentToDelete() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HWhich assignment do you want to delete?");
	printf("\033[11;13H:  ");
}

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

/* 4.Manage -> 3.Student Management */
void StudentMenu(COURSE *course)
{
	char menuInput;

	while (1)
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

/****************************************************************************************************
	int currentStudentCnt : current the number of student in this course
	int checkRegister :  check if registration is possible to avoid duplicate student ID in a course

	If ID of new student is not duplicated (checkRegister!=0), enter the name of the student you want to add.
	The name and ID entered (addID, addName) are inserted into current index of the student array, 
	and the number of students in this course increases.
******************************************************************************************************/
void RegisterStudent(COURSE *course)
{
	int currentStudentCnt; 
	int checkRegister;
	char addID[10];
	char addName[20];

	PrintStudentToRegister();
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
		PrintNameOfStudentToRegister();
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

/****************************************************************************************************
	int searchStudent : index of the student you want to modify. (return value of SearchID function)

	If the student you want to modify is in student array (searchStudent!=1), you can change name of the student (newName).
*****************************************************************************************************/
void PrintStudentToRegister() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HID of new student");
	printf("\033[11;13H:  ");
}

void PrintNameOfStudentToRegister() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HName of new student");
	printf("\033[11;13H:  ");
}

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
		PrintNameOfStudentToModify();
		scanf("%s", newName);

		strcpy(course->student[searchStudent].name, newName);
		system("cls");
		printf("\n\n   ** Student has successfully been modified! **\n");
	}

	printf("\n   It will return to course menu 3 seconds later");
	Sleep(3000);
}

/****************************************************************************************************
	char checkDelete : a variable used to input whether to delete or not.

	Find students to delete by using SearchID function.
	If the checkDelete is 'y'/'Y', the next student of student to delete will be covered with data, and the array is pulling forwards.
	Also, thhe number of students in this course decreases.
*****************************************************************************************************/

void PrintNameOfStudentToModify() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HNew name of the student");
	printf("\033[11;13H:  ");
}

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
		PrintStudentToDelete();
		//scanf("%c", &checkDelete);
		//getchar();
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

/****************************************************************************************************
	If a student exists in this course, the print function will be performed.

	qsort() - This function arranges the list of students in ascending order by student ID 
	1) course->student : Point of start the target array
	2) course->studentCount : Array size for the element
	3) sizeof(STUDENT) : Element size in bytes
	4) CompareID : Pointer to a function that compares two elements. This function is called repeatedly by qsort to compare two elements
*****************************************************************************************************/

void PrintStudentToDelete() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HDelete the student [y/n]");
	printf("\033[11;13H:  ");
}

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

/* 4.Manage -> 4.Notice Management */
void NoticeMenu(COURSE *course)
{
	char menuInput;

	while (1)
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

/****************************************************************************************************
If user wants to register notice of course, this RegisterNotice function will be performed

int check : Check whether the notice array is full

If notice array is not full (check = 1), enter the notice of the course you want to add.
Print registered notice and return to the notice menu function().
******************************************************************************************************/

void RegisterNotice(COURSE *course)
{
	int i,check=0;
	char newNotice[50];

	PrintNoticeToRegister();	
	fgets(newNotice, sizeof(newNotice), stdin);
	newNotice[strlen(newNotice) - 1] = '\0';

	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			strcpy((*course).notice[i], newNotice);
			check++;
			break;
		}
	}

	if (check == 0) {
		system("cls");
		printf("\n\n   Unable to add notice! Please delete the notice.\n");
		Sleep(3000);
		NoticeMenu(course);
	}
	else {
		system("cls");
	}

	printf("   Notice [%d] is successfully registered!", i);
	Sleep(3000);

}

void PrintNoticeToRegister() {
	system("cls");
	printf("\n\n\n  忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛 \n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  弛                                                        弛\n");
	printf("  戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\033[9;13HEnter notice");
	printf("\033[11;13H:  ");
}

/****************************************************************************************************
If user wants to modify notice of course, this ModifyNotice function will be performed

int check : Check whether the notice array is empty

If notice array is not empty (check = 1), print registered notices and user will select notice that they want to modify. 
If the notice you select is not registered ( strlen(course->notice[index]) == 0 ), inform you about this.
else enter the notice of the course you want to modify and return to the notice menu function().
******************************************************************************************************/

void ModifyNotice(COURSE *course)
{
	int i, j, index, check=0;
	char newNotice[50];
	system("cls");
	//display notice
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0) {
		printf("There are no notices to modify\n");
		Sleep(3000);
		NoticeMenu(course);
	}

	printf("Select notice to modify ");
	scanf("%d", &index);


	while (strlen(course->notice[index]) == 0) {
		printf("Modify function was not working because notice of that index doesn't exist.\n");
		printf("Select again: ");
		scanf("%d", &index);
	}

	getchar();

	printf("Enter notice\n");
	fgets(newNotice, sizeof(newNotice), stdin);
	newNotice[strlen(newNotice) - 1] = '\0';

	strcpy((*course).notice[index], newNotice);

	printf("Notice [%d] is successfully modified!", index);
	Sleep(1500);

}

/****************************************************************************************************
If user wants to delete notice of course, this DeleteNotice function will be performed

int check : Check whether the notice array is empty

If notice array is not empty (check = 1), print registered notices and user will select notice that they want to delete.
If the notice you select is not registered ( strlen(course->notice[index]) == 0 ), inform you about this.
else delete the notice of the course you want to delete and return to the notice menu function().
******************************************************************************************************/

void DeleteNotice(COURSE *course)
{
	int i, j, index, check=0;
	system("cls");
	//display notice
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0) {
		printf("There are no notices to delete\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	printf("Select notice to delete ");
	scanf("%d", &index);

	while (strlen(course->notice[index]) == 0) {
		printf("Delete function was not working because notice of that index doesn't exist.\n");
		printf("Select again: ");
		scanf("%d", &index);
	}

	getchar();

	for (i = index; i < 9; i++)
		strcpy(course->notice[i], course->notice[i+1]);

	printf("Notice [%d] is successfully deleted!", index);
	Sleep(1500);
}

/****************************************************************************************************
If user wants to see the notice of course, this PrintNotice function will be performed

int check : Check whether the notice array is empty

If notice array is not empty (check = 1), print registered notices
else print("There are no notices to display") and  return to the notice menu function().
******************************************************************************************************/

void PrintNotice(COURSE *course)
{
	system("cls");
	int i, j, check = 0;

	//display notice
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0) {
		printf("There are no notices to display\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	printf("It will return to notice menu 3 seconds later\n");
	Sleep(3000);
}