#include <stdio.h>
#include <stdlib.h>
#include "student.h"

#define PRINTTYPE_EDIT 1
#define PRINTTYPE_DELETE 2
#define PRINTTYPE_ALL 3
#define MAX_ASSIGNMENT 5
#define MAX_NOTICE 10

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

	printf("Enter ID of student to select : ");
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

/*****************************************************************************************************
   COURSE *course - the component of course that user want to add data to file.
   int noticeCount - the number of existing notice by using strlen.
   int assignmentCount - the number of existing assignment by using strlen.
   
   sample_course.txt - WriteFile function uses file which name is "sample_course.txt".
   So if you have "sample_course.txt" and it contains important information, 
   you should change your file name to another.
   
   1-1) If the file exists,
   it writes the total number of students(studentCount) in the first row.
   Then, it writes information of student(STUDNET array) one row by one.
   The information contains student ID, name, exam score and assignment score.
   Next, it writes the total number of assignment notice and details about assignment on next line.
   Finally, it writes the number of notice and details same as assignment.
   
   1-2) If the file doens't exist,
   Print the "Cannot open the file" on console windows and exit program.
   
   2) Finally, it closes the file and print success message.
******************************************************************************************************/
void WriteFile(COURSE *course)
{
	FILE *file;        // file variables to open, write, and close the txt file
	int i, j;           // int variables for "for statement"
	int noticeCount;
	int assignmentCount;

	file = fopen("sample_course.txt", "w");

	if (file == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	} // "sample_course.txt" doesnt' exist
	else
	{
		fprintf(file, "%d\n", (*course).studentCount);

		for (i = 0; i < (*course).studentCount; i++)
		{
			fprintf(file, "%s %s ", (*course).student[i].id, (*course).student[i].name);

			for (j = 0; j < 2; j++)
			{
				fprintf(file, "%-8.2f", (*course).student[i].examScore[j]);
			}

			for (j = 0; j < MAX_ASSIGNMENT; j++)
			{
				fprintf(file, "%-8.2f", (*course).student[i].assignmentScore[j]);
			}
			fprintf(file, "\n");
		}

		noticeCount = 0;

		for (i = 0; i < MAX_NOTICE; i++)
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

		for (i = 0; i < MAX_ASSIGNMENT; i++)
		{
			if (strlen((*course).assignment[i]) != 0)
			{
				assignmentCount++;
			}
		}

		fprintf(file, "%d\n", assignmentCount);

		for (i = 0; i < assignmentCount; i++)
		{
			fprintf(file, "%s\n", (*course).assignment[i]);
		}

	} // "sample_course.txt" exist

	fclose(file);   // close the file
	printf("Write data is successfully done!\n\n");
	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

/*****************************************************************************************************
   COURSE *course - the component of course that user want to add data from file.
   int studentCount - the number of student would be stored in this variable from text file.
   int existNoticeCount - the number of existing notice by using strlen.
   int existAssignmentCount -  the number of existing assignment by using strlen.
   int newNoticeCount - the integer that read from file and means the number of notice in file.
   int newAssignmentCount - the integer that read from file and means the number of notice in file.
   
   sample_course.txt - ReadFile function uses file which name is "sample_course.txt".
   if you want to read information from your file, you should change your file name to 
   "sample_course.txt" and the information format should be like this.
   
   -------------------------------------------------------------------------------------------
   5
   122172 suckho 80.0 90.0 7.0 10.0 6.0 10.0 7.0
   122211 youngho 95.0 95.0 7.0 10.0 8.0 10.0 0.0
   13011045 jongwon 70.0 50.0  0.0 10.0 0.0 10.0 0.0
   15010982 minji 90.0 95.0 10.0 10.0 10.0 10.0 8.0
   15011046 haeun 95.0 90.0 10.0 10.0 7.0 10.0 5.0
   3
   There is no lecture on 6, June.
   Final exam will be on 18, June.
   The last assignment should be done with your team member and submit report until friday.
   3
   Review of open source video
   OSS survey and presentation
   Development plan
   --------------------------------------------------------------------------------------------
   
   First line is number of students and 2~6 line is 
   [ studentID | name | midterm-score | finalExam-score | assignment score 0~4 ]
   Next integer is number of notice, after then you just write what you want to notify.
   The last Integer is number of assignment. you can add explain about assignment on next line.
   
******************************************************************************************************/
void ReadFile(COURSE *course)
{
	int i, j;
	int studentCount;
	int existNoticeCount;
	int existAssignmentCount;
	int newNoticeCount;
	int newAssignmentCount;

	FILE *file;         // file variables to open, write, and close the txt file
	file = fopen("sample_course.txt", "r"); // open "sample_course.txt" file by "read" mode. 

	if (file == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	} // "sample_course.txt" doesnt' exist
	else
	{
		fscanf(file, "%d", &studentCount);
		fscanf(file, "\n");

		// Read all information of student array on the next row.
		for (i = course->studentCount; i < course->studentCount + studentCount; i++)
		{
			fscanf(file, "%s%s%", (*course).student[i].id, (*course).student[i].name);
			fscanf(file, "%lf%lf", (*course).student[i].examScore, (*course).student[i].examScore + 1);

			for (j = 0; j < MAX_ASSIGNMENT; j++)
			{
				fscanf(file, "%lf", (*course).student[i].assignmentScore + j);
			}
			fscanf(file, "\n");
		}

		(*course).studentCount += studentCount;

		fscanf(file, "%d", &newNoticeCount);
		fscanf(file, "\n");

		existNoticeCount = 0;

		// If notice is null string, we can use it for new notice from text file.
		for (i = 0; i < MAX_NOTICE; i++)
		{
			if (strlen((*course).notice[i]) != 0)
			{
				existNoticeCount++;
			}
		}

		for (i = 0; i < newNoticeCount; i++)
		{
			fgets((*course).notice[existNoticeCount + i], sizeof((*course).notice[existNoticeCount + i]), file);
			(*course).notice[existNoticeCount + i][strlen((*course).notice[existNoticeCount + i]) - 1] = '\0';
		}

		fscanf(file, "%d", &newAssignmentCount);
		fscanf(file, "\n");

		existAssignmentCount = 0;

		for (i = 0; i < MAX_ASSIGNMENT; i++)
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

		printf("File data is successfully loaded!\n\n");
		printf("It will return to course menu 3 seconds later\n");
		Sleep(3000);

	} // "sample_course.txt" exist

	fclose(file);  // close the file
}


/******************************************
   Console print(UI) of Course menu
 ******************************************/
void PrintCourseMenu()
{
	system("cls");
	printf("\n      [ Course ]  \n\n");
	printf(" 1.     Register \n");
	printf(" 2.     Modifiy \n");
	printf(" 3      Delete \n");
	printf(" 4.     Manage \n");
	printf(" 5.      Exit \n\n");
}

/******************************************
   Console print(UI) of Management menu
*******************************************/
void PrintManagementMenu()
{
	system("cls");
	printf("\n        [ Management ]  \n\n");
	printf(" 1.     Score    Management \n");
	printf(" 2.   Assignment Management \n");
	printf(" 3.     Student  Management \n");
	printf(" 4.     Notice   Management \n");
	printf(" 5.          Read File\n");
	printf(" 6.         Write File\n\n");
	printf("ESC.           Back \n\n");
}

/******************************************
   Console print(UI) of score menu
*******************************************/
void PrintScoreMenu()
{
	system("cls");
	printf("\n        [ Score ]  \n\n");
	printf(" 1.     Register \n");
	printf(" 2.     Modifiy \n");
	printf(" 3.     Delete \n");
	printf(" 4.      Print \n");
	printf("ESC.     Back \n\n");
}

/******************************************
   Console print(UI) of assignment menu
*******************************************/
void PrintAssignmentMenu()
{
	system("cls");
	printf("\n      [ Assignment ]  \n\n");
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.     Delete \n");
	printf(" 4.     Print \n");
	printf("ESC.     Back \n\n");
}

/******************************************
   Console print(UI) of student menu
 *******************************************/
void PrintStudentMenu()
{
	system("cls");
	printf("\n      [ Student ]  \n\n");
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.    Delete \n");
	printf(" 4.     Print \n");
	printf("ESC.    Back \n\n");
}

/*******************************************
   Console print(UI) of notice menu
 *******************************************/
void PrintNoticeMenu()
{
	system("cls");
	printf("\n        [ Notice ]  \n\n");
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.     Delete \n");
	printf(" 4.     Print   \n");
	printf("ESC.     Back \n\n");
}


/***********************************************************************
   COURSE **course - the array of structure which want to print 
   int *coursecount - the number of course

   PrintCourseList prints the name list of COURSE structure array
************************************************************************/
void PrintCourseList(COURSE **course, int *courseCount)
{
	int i;

	system("cls");

	for (i = 0; i < *courseCount; i++)
	{
		printf(" %d.   %15s\n", i, (*course)[i].name);
	}
}

/***********************************************************************************************
   COURSE **course - the array of structure which want to manage in course menu.
   int *coursecount - the number of course
   char menuinput - the input of user that is used for selecting function

   CourseMenu receive one character from user and use it to select the menu of course.
*************************************************************************************************/
void CourseMenu(COURSE **course, int *courseCount)
{
	char menuInput;

	for(;;)
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

/************************************************************************************************
   COURSE **course - the array of structure that user want to select.
   int *coursecount - the number of course
   int index - the input of user that is used for selecting function.
   
   SelectCourse prints the list of course and receives input(inex) from the user. Then it calls 
   management menu with the one component of COURSE array that user selected.
*************************************************************************************************/
void SelectCourse(COURSE **course, int *courseCount)
{
	int index;

	// If there is no course, It doesn't work.
	if (*courseCount > 0)
	{
		PrintCourseList(course, courseCount);
		scanf("%d", &index);
		getchar();

		ManagementMenu(&((*course)[index]));
	}
	else
	{
		printf("There is no course to select.\n");
		printf("It will return to course menu 3 seconds later\n");
		Sleep(3000);
	}
}

/*****************************************************************************************************
   COURSE **course - the array of structure that new course would be addded.
   int *coursecount - the number of course
   int courseName[40] - the temporary variable which receive the string of course name from user.
   
   1) RegisterCourse receive the name of new course from user. 
   
   2-1) If there is no component in COURSE array, 
   it allocate the array dynamically which size is one COURSE.
   
   2-2) If there are components in COURSE array, 
   it allocate new array dynamically which size is courseCount+1.
   It copy the existing array to new array and copy the receiving name to new component of array.
   Then, add this new component to new array. Finally, it free the existing array.
******************************************************************************************************/
void RegisterCourse(COURSE **course, int *courseCount)
{
	int i;
	char courseName[40];

	printf("please insert name of new subject\n");
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

	printf("[ %s ] course is successfully registed!\n\n", (*course)[*courseCount - 1].name);
	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

/***************************************************************************************
   COURSE *course - the component of array of COURSE structre which want to initialize
   
   InitCourse function initialize data of COURSE structure as null string.
   The data are assignment(char[]), notice(char[]), studentCount(int)
***************************************************************************************/
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

/*******************************************************************************************************
   COURSE **course - the array of structure that user would change.
   int *coursecount - the number of course
   int newName[40] - the temporary variable which receive the string of course name from user.
   
   1) If there is course in **course, it prints the list of course. Then It receives the index of what
   the user want to modify and also receives the new name of course. Finally, it changes the course's 
   name that user selected.
   
   2) If not, it notify user that there is no course and would not modify anything.
********************************************************************************************************/
void ModifyCourse(COURSE **course, int *courseCount)
{
	int index;
	char newName[40];

	if (*courseCount > 0)
	{
		PrintCourseList(course, courseCount);

		printf("please insert number what you want to modify\n");
		scanf("%d", &index);
		getchar(); // Using getchar() for excluding enter key when using fgets below.

		printf("please enter the new name of course\n");
		fgets(newName, sizeof(newName), stdin);
		newName[strlen(newName) - 1] = '\0'; // Because fgets receive \n(Enter), it needs to exclude it.

		strcpy((*course)[index].name, newName);
		printf("course is successfully modified!\n");
	}
	else
	{
		printf("There is nothing to modify.\n");
	}

	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

/*****************************************************************************************************
   COURSE **course - the array of structure that user would delete.
   int *coursecount - the number of course
   int deleteIndex - the index of components in COURSE array which user want to delete.
   int countIndex - this variable is used for counting index of new array because it should copy 
   existing array excluding selected index to new array.
   
   1-1) If there is course in **course, it prints the list of course. Then It receives the index 
   of what the user want to delete.
   1-2) Then, it allocates new array dynamically which size is (existing array size -1 ) because 
   this function delete on component in array.
   1-3) And it copies existing array to new array excluding selected components.
   1-4) Finally, it free existing array of COURSE structure.
   
   2) If not, it notify user that there is no course and would not delete anything.
******************************************************************************************************/
void DeleteCourse(COURSE **course, int *courseCount)
{
	int i, j;
	int deleteIndex;
	int countIndex;

	if (*courseCount == 0)
	{
		printf("There is nothing to delete\n");
	}
	else
	{
		PrintCourseList(course, courseCount);
		printf("please insert number what you want to delete\n");
		scanf("%d", &deleteIndex);

		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*courseCount - 1));

		countIndex = 0;

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
		printf("course is successfully deleted!\n\n");
	}

	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);

}

/*****************************************************************************************************
 COURSE *course - the course that user want to manage in array of course.
 int *coursecount - the number of course
 char menuinput - the input of user that is used for selecting function

 ManagementMenu receive one character from user and use it to select the function of management.
******************************************************************************************************/
void ManagementMenu(COURSE *course)
{
	char menuInput;

	for(;;)
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

	for(;;)
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

void RegisterScore(COURSE *course)
{
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	printf("Input student ID to register score: ");
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

	if (studentIndex == -1) // case studentID which entered doesn't exists
	{
		printf("There is no student who you entered\n");
		printf("It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		ScoreMenu(course);
		return;
	}

	printf("Input midterm score : ");
	scanf("%lf", &midtermScore);
	printf("\n");

	printf("Input final score : ");
	scanf("%lf", &finalScore);
	printf("\n");

	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	printf("Registration is Succeed!\n");
	printf("(It will be returned to Score Menu after 3 seconds automatically)");
	Sleep(3000);
}

void ModifyScore(COURSE *course)
{
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	printf("Input student ID to modify score: ");
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
		printf("There is no student who you entered\n");
		printf("It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		return;
	}

	printf("----------------Scores of you found-------------------------\n");
	PrintScore(course, PRINTTYPE_EDIT, studentIndex);

	printf("Input midterm score to modify : ");
	scanf("%lf", &midtermScore);
	getchar();
	printf("\n");

	printf("Input final score to modify : ");
	scanf("%lf", &finalScore);
	getchar();
	printf("\n");

	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	printf("----------------Changed Scores of %s-------------------------\n");
	printf("midterm score what you changed : %.2lf\n", midtermScore);
	printf("final score what you changed : %.2lf\n\n", finalScore);

	printf("Modified Complete!\n");
	printf("It will be returned to Score Menu after 3 seconds");
	Sleep(3000);
}

void DeleteScore(COURSE *course)
{
	char studentID[10];
	int studentIndex = -1;
	char confirm = ' ';

	printf("Input student ID to Delete Score: ");
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
		printf("There is no student who you entered\n");
		printf("It will be returned to Score Menu after 3 seconds automatically");
		Sleep(3000);
		return;
	}

	if (course->student[studentIndex].examScore[0] > 100 && course->student[studentIndex].examScore[1] > 100) //already deleted case if score exceed 100
	{
		printf("It is already deleted score.\n");
		printf("It will be returned to Score Menu after 3 seconds...");
		return;
	}

	printf("----------------Scores of you found one's-------------------------\n");
	PrintScore(course, PRINTTYPE_DELETE, studentIndex);

	printf("\nAre you sure of removing it? (Y/N) : ");
	scanf("%c", &confirm);
	getchar();
	if (confirm == 'n' || confirm == 'N')
	{
		printf("Deleteing Score is canceled.\n");
		printf("It will be returned to Score Menu after 3 seconds");
		Sleep(3000);
		return;
	}

	else if (confirm == 'y' || confirm == 'Y')
	{
		course->student[studentIndex].examScore[0] = 300;
		course->student[studentIndex].examScore[1] = 300;
		printf("\nDeleted is complete!\n");
		printf("It will be returned to Score Menu after 3 seconds");
		Sleep(3000);
		return;
	}
}

void PrintScore(COURSE *course, int printType, int studentIndex)
{
	int i, j;
	double sum;
	if (printType == PRINTTYPE_ALL)
	{
		if (course->student[studentIndex].examScore[0] > 100 && course->student[studentIndex].examScore[1] > 100)
		{
			printf("You didn't register score of studentID: %s\n", course->student[studentIndex].id);
			printf("It will be returned to Score Menu after 3 seconds");
			Sleep(3000);
			return;
		}
		for (i = 0; i < course->studentCount; i++)
		{
			printf("%s %s\n", course->student[i].id, course->student[i].name);
			printf("Midterm Exam : %.2lf / Final Exam : %.2lf\n\n", course->student[i].examScore[0], course->student[i].examScore[1]);
		}
		AverageCourseScore(course);
		printf("It will be returned to Score Menu after 3 seconds\n");
		Sleep(3000);
		return;
	}

	if (printType == PRINTTYPE_EDIT || printType == PRINTTYPE_DELETE)
	{
		if (course->student[studentIndex].examScore[0] > 100 && course->student[studentIndex].examScore[1] > 100)
		{
			printf("You didn't register score of studentID: %s\n", course->student[studentIndex].id);
			printf("It will be returned to Score Menu after 3 seconds");
			Sleep(3000);
			return;
		}
		printf("Student ID : %s\n", course->student[studentIndex].id);
		printf("Student Name : %s\n", course->student[studentIndex].name);
		printf("Midterm Exam Score : %.2lf  | Final Exam Score : %.2lf\n\n", course->student[studentIndex].examScore[0], course->student[studentIndex].examScore[1]);
	}
}

void AverageCourseScore(COURSE *course)
{
	int i;
	int midterm_delete_count = 0;
	int final_delete_count = 0;
	double midtermSum = 0;
	double finalSum = 0;
	double average_midterm = 0;
	double average_final = 0;

	for (i = 0; i < course->studentCount; i++)
	{
		if (course->student[i].examScore[0] > 100)
		{
			midterm_delete_count = midterm_delete_count + 1;
		}

		if (course->student[i].examScore[1] > 100)
		{
			final_delete_count = final_delete_count + 1;
		}
		midtermSum = midtermSum + course->student[i].examScore[0];
		finalSum = finalSum + course->student[i].examScore[1];
	}

	midtermSum = midtermSum - 300 * midterm_delete_count;
	finalSum = finalSum - 300 * final_delete_count;

	average_midterm = midtermSum / (course->studentCount - midterm_delete_count);
	average_final = finalSum / (course->studentCount - final_delete_count);

	printf("Average score of midterm for %s course is %.2lf\n", course->name, average_midterm);
	printf("Average score of final for %s course is %.2lf\n\n", course->name, average_final);
	Sleep(3000);
}

void WriteScoreFile()
{

}

void AssignmentMenu(COURSE *course)
{
	char menuInput;
	getchar();
	for(;;)
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

	printf("please insert comments of a new assignment\n");
	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';


	for (i = 0; i < 5; i++) {
		if (strlen(course->assignment[i]) == 0) {
			strcpy((*course).assignment[i], assignmentComment);
			break;
		}
	}

	printf("comments about an assignment is successfully registed!\n\n");
	printf("It will return to assignment menu 3 seconds later\n");
	Sleep(3000);
}

void ModifyAssignment(COURSE *course)
{
	int assignmentNumber = 0;
	int i = 0;
	char assignmentComment[50];

	PrintAssignment(course);
	printf("\n\nwhich assignment do you want to modify?\n");
	scanf("%d", &assignmentNumber);
	getchar();
	assignmentNumber--;

	printf("\n\nplease insert comments about an assignment that you want to modify\n");
	fgets(assignmentComment, sizeof(assignmentComment), stdin);
	assignmentComment[strlen(assignmentComment) - 1] = '\0';

	for (i = 0; i < 5; i++) {
		if (i == assignmentNumber) {
			strcpy((*course).assignment[i], assignmentComment);
		}
	}

	printf("\ncomments about an assignment is successfully modified!\n\n");
	printf("It will return to assignment menu 3 seconds later\n");
	Sleep(3000);
}

void DeleteAssignment(COURSE *course)
{
	PrintAssignment(course);
	int assignmentNumber = 0;
	int i = 0;

	printf("\n\nwhich assignment do you want to delete?\n");
	scanf("%d", &assignmentNumber);
	assignmentNumber--;
	for (i = 0; i < 5; i++) {
		if (i == assignmentNumber) {
			strcpy((*course).assignment[i], "");
		}
	}

	printf("comments about an assignment is successfully deleted!\n\n");
	printf("It will return to assignment menu 3 seconds later\n");
	Sleep(3000);
}

void PrintAssignment(COURSE *course)
{
	int i = 0;
	int assignmentNumber = 0;
	for (i = 0; i < 5; i++)
	{
		assignmentNumber = i + 1;
		printf("%d %s\n", assignmentNumber, (*course).assignment[i]);
	}
	printf("\n\nIt will return to assignment menu 3 seconds later\n");
	Sleep(3000);
}

/* 4.Manage -> 3.Student Management */
void StudentMenu(COURSE *course)
{
	char menuInput;

	for(;;)
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

	printf("ID of new student : ");
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
		printf("\nstudent [%s] already exists in this course..", addID);
	}
	else
	{
		printf("Name of new student : ");
		scanf("%s", addName);

		currentStudentCnt = course->studentCount;
		strcpy(course->student[currentStudentCnt].id, addID);
		strcpy(course->student[currentStudentCnt].name, addName);
		course->studentCount++;

		printf("\n** Student has successfully been registered! **");
	}

	printf("\nIt will return to course menu 3 seconds later\n");
	Sleep(3000);
}

/****************************************************************************************************
	int searchStudent : index of the student you want to modify. (return value of SearchID function)

	If the student you want to modify is in student array (searchStudent!=1), you can change name of the student (newName).
*****************************************************************************************************/
void ModifyStudent(COURSE *course)
{
	int searchStudent; //index
	char newName[20];

	PrintStudent(course);

	searchStudent = SearchID(course);
	if (searchStudent == -1)
	{
		printf("\nNo student ID found..");
	}
	else
	{
		printf("\nNew name of the student : ");
		scanf("%s", newName);

		strcpy(course->student[searchStudent].name, newName);
		printf("\n** Student has successfully been modified! **\n");
	}

	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

/****************************************************************************************************
	char checkDelete : a variable used to input whether to delete or not.

	Find students to delete by using SearchID function.
	If the checkDelete is 'y'/'Y', the next student of student to delete will be covered with data, and the array is pulling forwards.
	Also, thhe number of students in this course decreases.
*****************************************************************************************************/
void DeleteStudent(COURSE *course)
{
	int searchStudent;
	char checkDelete;

	PrintStudent(course);

	searchStudent = SearchID(course);
	if (searchStudent == -1)
	{
		printf("\nNo student ID found..");
	}
	else
	{
		printf("Delete the student [y/n] : ");
		checkDelete = getche();

		if (checkDelete == 'y' || checkDelete == 'Y')
		{
			for (int i = 0; i < course->studentCount - 1; i++)
			{
				course->student[i] = course->student[i + 1];
			}
			course->studentCount--;

			printf("\n** Student has successfully been deleted! **\n");
		}
		else if (checkDelete == 'n' || checkDelete == 'N')
		{
		}
		else
		{
			printf("\nWrong input..");
		}
	}

	printf("\nIt will return to course menu 3 seconds later\n");
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
void PrintStudent(COURSE *course)
{
	if (course->studentCount == 0)
	{
		printf("\nThere are no students in this class..\n");
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

void NoticeMenu(COURSE *course)
{
	char menuInput;
	getchar();

	for(;;)
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

void RegisterNotice(COURSE *course)
{
	int i, check = 0;
	char newNotice[50];

	printf("Enter notice\n");
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
		printf("Unable to add notice! Please delete the notice.\n");
		Sleep(3000);
		NoticeMenu(course);
	}

	printf("Notice [%d] is successfully registered!\n", i);
	Sleep(3000);

}

void ModifyNotice(COURSE *course)
{
	int i, j, index, check = 0;
	char newNotice[50];

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

	printf("Notice [%d] is successfully modified!\n", index);
	Sleep(1500);

}

void DeleteNotice(COURSE *course)
{
	int i, j, index, check = 0;

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
		strcpy(course->notice[i], course->notice[i + 1]);

	printf("Notice [%d] is successfully deleted!\n", index);
	Sleep(1500);
}

void PrintNotice(COURSE *course)
{
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