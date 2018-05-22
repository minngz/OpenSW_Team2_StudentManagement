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

int CompareID(const void *elem1, const void *elem2)
{
	STUDENT *student1 = (STUDENT*)elem1;
	STUDENT *student2 = (STUDENT*)elem2;
	return strcmp((student1->id), (student2->id));
}

//Search for students by number
int SearchID(COURSE* course)
{
	int searchStudent = -1;
	char selectID[10];

	printf("Enter ID of student to select : ");
	scanf("%s", selectID);

	for (int i = 0; i < course->studentNumber; i++)
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

	file = fopen("sample_course.txt", "w");									 

	if (file == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	} // "sample_course.txt" doesnt' exist
	else
	{
		fprintf(file, "%d\n", (*course).studentNumber);  
														
		for (i = 0; i <  (*course).studentNumber; i++)
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
	printf("Write data is successfully done!\n\n");
	printf("It will return to course menu 3 seconds later\n");
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
		for (i = course->studentNumber; i < course->studentNumber+studentCount; i++)
		{
			fscanf(file, "%s%s%",(*course).student[i].id, (*course).student[i].name);
			fscanf(file, "%lf%lf", (*course).student[i].examScore, (*course).student[i].examScore+1);		

			for (j = 0; j < 5; j++)
			{
				fscanf(file, "%lf", (*course).student[i].assignmentScore+j);
			}
			fscanf(file, "\n");
		}

		(*course).studentNumber += studentCount;

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

		printf("File data is successfully loaded!\n\n");
		printf("It will return to course menu 3 seconds later\n");
		Sleep(3000);

	} // "sample_course.txt" exist

	fclose(file);  // close the file
}


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

void PrintCourseList(COURSE **course, int *subjectNumber)
{
	int i;

	system("cls");

	for (i = 0; i < *subjectNumber; i++)
	{
		printf(" %d.   %15s\n", i, (*course)[i].name);
	}
}

void CourseMenu(COURSE **course, int *subjectNumber)
{
	char menuInput;

	while (1)
	{
		PrintCourseMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterCourse(course, subjectNumber);
			break;

		case '2':
			ModifyCourse(course, subjectNumber);
			break;

		case '3':
			DeleteCourse(course, subjectNumber);
			break;

		case '4':
			SelectCourse(course, subjectNumber);
			break;

		case '5':
			exit(1);
			break;

		default:
			break;
		}
	}
}

void SelectCourse(COURSE **course, int *subjectNumber)
{
	int index;

	PrintCourseList(course, subjectNumber);
	scanf("%d", &index);

	ManagementMenu(&((*course)[index]));

}

void RegisterCourse(COURSE **course, int *subjectNumber)
{
	int i;
	char courseName[40];

	printf("please insert name of new subject\n");
	gets(courseName);

	if (*subjectNumber == 0)
	{
		*course = (COURSE*)malloc(sizeof(COURSE));
	}
	else
	{
		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*subjectNumber + 1));

		for (i = 0; i < *subjectNumber; i++)
		{
			temp[i] = (*course)[i];
		}

		free(*course);
		*course = temp;
	}


	(*course)[*subjectNumber].studentNumber = 0;

	initAssignment(&((*course)[*subjectNumber]));
	initNotice(&((*course)[*subjectNumber]));
	 

	strcpy((*course)[*subjectNumber].name, courseName);
	*subjectNumber += 1;

	printf("[ %s ] course is successfully registed!\n\n", (*course)[*subjectNumber - 1].name);
	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

void initAssignment(COURSE *course)
{
	int i;

	for (i = 0; i < 5; i++)
	{
		strcpy((*course).assignment[i], "");
	}
}

void initNotice(COURSE *course)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		strcpy((*course).notice[i], "");
	}
}

void ModifyCourse(COURSE **course, int *subjectNumber)
{
	int index;
	char newName[20];

	PrintCourseList(course, subjectNumber);
	printf("please insert number what you want to modify\n");
	scanf("%d", &index);
	getchar();
	printf("please enter the new name of course\n");
	gets(newName);

	strcpy((*course)[index].name, newName);

	printf("course is successfully modified!\n");
	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

void DeleteCourse(COURSE **course, int *subjectNumber)
{
	int i, j;
	int index;
	int newIndex;

	if (*subjectNumber == 0)
	{
		printf("There is nothing to delete\n");
	}
	else
	{
		PrintCourseList(course, subjectNumber);
		printf("please insert number what you want to delete\n");
		scanf("%d", &index);

		COURSE *temp = (COURSE*)malloc(sizeof(COURSE)*(*subjectNumber - 1));

		newIndex = 0;

		for (i = 0; i < *subjectNumber; i++)
		{
			if (i != index)
			{
				temp[newIndex] = (*course)[i];
				newIndex++;
			}
		}

		free(*course);
		*course = temp;

		*subjectNumber -= 1;
		printf("course is successfully deleted!\n\n");
	}

	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);

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

void RegisterScore(COURSE *course)
{
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	printf("Input student ID to register score: ");
	scanf("%s", studentID);
	printf("\n");

	//studentNumber means number of students in selected course
	for (int i = 0; i < course->studentNumber; i++)
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

	for (int i = 0; i < course->studentNumber; i++)
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

	for (int i = 0; i < course->studentNumber; i++)
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
		for (i = 0; i < course->studentNumber; i++)
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

	for (i = 0; i < course->studentNumber; i++)
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

	average_midterm = midtermSum / (course->studentNumber - midterm_delete_count);
	average_final = finalSum / (course->studentNumber - final_delete_count);

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

	printf("please insert comments of a new assignment\n");
	gets(assignmentComment);

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
	gets(assignmentComment);

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

void RegisterStudent(COURSE *course)
{
	int currentStudentCnt; //current the number of student in this course
	int checkRegister;
	char addID[10];
	char addName[20];

	printf("ID of new student : ");
	scanf("%s", addID);

	for (int i = 0; i < course->studentNumber; i++) 
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

		currentStudentCnt = course->studentNumber;
		strcpy(course->student[currentStudentCnt].id, addID);
		strcpy(course->student[currentStudentCnt].name, addName);
		course->studentNumber++;

		printf("\n** Student has successfully been registered! **");
	}
	
	printf("\nIt will return to course menu 3 seconds later\n");
	Sleep(3000);
}

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
		//scanf("%c", &checkDelete);
		//getchar();
		checkDelete = getche();

		if (checkDelete == 'y' || checkDelete == 'Y')
		{
			for (int i = 0; i < course->studentNumber - 1; i++) //单捞磐 丹绢静扁
				course->student[i] = course->student[i + 1];

			course->studentNumber--;

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

void PrintStudent(COURSE *course)
{
	if (course->studentNumber == 0)
	{
		printf("\nThere are no students in this class..\n");
	}
	else
	{
		printf("\n\t\t§ Student List №\n\n");
		printf("\t  ID		Name		\n");
		printf("	ΣΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΜΥ\n");

		qsort(course->student, course->studentNumber, sizeof(STUDENT), CompareID);
		for (int i = 0; i < course->studentNumber; i++)
		{
			printf("	  %s	%s	\n", course->student[i].id, course->student[i].name);
		}
		printf("\n\n");
	}
	//printf("\nIt will return to course menu 3 seconds later\n");
	//Sleep(3000);
}

void NoticeMenu(COURSE *course)
{
	char menuInput;
	getchar();

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

void RegisterNotice(COURSE *course)
{
	int i,check=0;
	char newNotice[50];

	printf("Enter notice\n");
	gets(newNotice);

	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			strcpy((*course).notice[i], newNotice);
			check=1;
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
	int i, j, index, check=0;
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

	getchar();

	printf("Enter notice\n");
	gets(newNotice);

	strcpy((*course).notice[index], newNotice);

	printf("Notice [%d] is successfully modified!\n", index);
	Sleep(1500);

}

void DeleteNotice(COURSE *course)
{
	int i, j, check=0;

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
	scanf("%d", &j);

	for (i = j; i < 9; i++)
		strcpy(course->notice[i], course->notice[i+1]);

	printf("Notice [%d] is successfully deleted!\n", j);
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