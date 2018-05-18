#include <stdio.h>
#include <stdlib.h>
#include "student.h"

#define PRINTTYPE_EDIT 1
#define PRINTTYPE_DELETE 2
#define PRINTTYPE_ALL 3

//函数部分
//系统设置
void SystemSet()
{
	system("title  Student Management");
}
//读取选项。
int ScanfSet()
{
	int n;
	scanf("%d", &n);
	return n;
}

//读取数据
void readDate(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i, j;//控制读取的学生数和科目数
			 //FILE *p = freopen("test.txt","r",stdin);
	printf("请输入学生的数目\n");
	scanf("%d", studentNumber);
	printf("请输入科目数\n");
	scanf("%d", subjectNumber);
	getchar();
	for (i = 0; i < *studentNumber; i++)
	{
		printf("请输入学号、名字、分数 中间以空格隔开\n");
		scanf("%s%s", student[i].id, student[i].name);
		for (j = 0; j < *subjectNumber; j++)
		{
			scanf("%lf", &student[i].examScore[j]);
		}
	}
	//fclose(p);
	returnUserFace();
}

//返回用户界面
void returnUserFace()
{
	while (getchar() != '\n');
	system("pause");
	system("cls");
}

void sumAndAveSubjectSore(STUDENT *student, int *studenNumber, int *subjectNumber)
{
	int i, j;
	double sum;
	for (i = 0; i < *subjectNumber; i++)
	{
		sum = 0;
		for (j = 0; j < *studenNumber; j++)
		{
			sum += student[j].examScore[i];
		}
		printf("学科%d 的总分是 %-8.2lf ", i + 1, 1.0*sum);
		printf("平均分是 %-8.2lf\n", 1.0*sum / (*studenNumber));
	}
	returnUserFace();
}

void sumAndAveStudentSore(STUDENT *student, int *studenNumber, int *subjectNumber)
{
	int i, j;
	double sum = 0;
	for (i = 0; i < *studenNumber; i++)
	{
		sum = 0;
		for (j = 0; j < *subjectNumber; j++)
		{
			sum += student[i].examScore[j];
		}

		printf("id : %-12s name : %-10s ", student[i].id, student[i].name);
		printf("Sum : %-8.2lf  Avg : %-8.2lf\n", 1.0*sum, 1.0*sum / (*subjectNumber));
	}
	returnUserFace();
}

int orderBig(const void *a, const void *b)
{
	STUDENT *p1 = (STUDENT*)a;
	STUDENT *p2 = (STUDENT*)b;

	//return (int)((p1->sumScore) - (p2->sumScore));
}

int orderSmall(const void *a, const void *b)
{
	STUDENT *p1 = (STUDENT*)a;
	STUDENT *p2 = (STUDENT*)b;
	//return (int)((p2->sumScore) - (p1->sumScore));
}

int CompareID(const void *elem1, const void *elem2)
{
	STUDENT *student1 = (STUDENT*)elem1;
	STUDENT *student2 = (STUDENT*)elem2;
	return strcmp((student1->id), (student2->id));
}

int orderName(const void *a, const void *b)
{
	STUDENT *p1 = (STUDENT*)a;
	STUDENT *p2 = (STUDENT*)b;
	return strcmp((p1->name), (p2->name));
}

void Print(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i, j;//控制读取的学生数和科目数
	for (i = 0; i < *studentNumber; i++)
	{
		printf("%-12s%-10s ", student[i].id, student[i].name);
		for (j = 0; j < *subjectNumber; j++)
		{
			printf("%-8.2f ", student[i].examScore[j]);
		}
		printf("\n");
	}
	returnUserFace();
}
//Search for students by name
void nameSearch(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i, j, k = 0;
	char c;
	char name[30];
E:
	printf("Enter student name \n");
	scanf("%s", name);

	//find student
	for (i = 0; i < *studentNumber; i++)
	{
		if (strcmp(name, student[i].name) == 0)
		{
			printf("number: %-15s \nname: %-15s\n", student[i].id, student[i].name);
			printf("score: ");
			for (j = 0; j < *subjectNumber; j++)
				printf("%-8.2f", student[i].examScore[j]);
			k = 1;
		}

	}

	if (k == 1) //success
		printf("\n");
	else
		printf("Cannot fine the student\n");
	getchar();
E1:
	printf("Continue \"y\" Exit and return \"n\" \n");
	scanf("%c", &c);

	if (c == 'y')
		goto E;
	else if (c == 'n')
		returnUserFace();
	else
	{
		while (getchar() != '\n');
		goto E1;
	}
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

int Excellente = 0, Fine = 0, Medium = 0, Pass = 0, Fail = 0;
//分类成绩
void SortScore(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	Excellente = 0, Fine = 0, Medium = 0, Pass = 0, Fail = 0;
	int i, j;
	for (i = 0; i < *subjectNumber; ++i)
	{
		for (j = 0; j < *studentNumber; ++j)
		{
			if (student[j].examScore[i] >= 90) Excellente++;
			else if (student[j].examScore[i] >= 80) Fine++;
			else if (student[j].examScore[i] >= 70) Medium++;
			else if (student[j].examScore[i] >= 60) Pass++;
			else Fail++;
		}
		printf("科目 %d\n", i + 1);
		printf("优秀(90-100) %2d %-5.2f%%\n", Excellente, 1.0*Excellente / (*studentNumber) * 100);
		printf("良好(80-89)  %2d %-5.2f%%\n", Fine, 1.0*Fine / (*studentNumber) * 100);
		printf("中等(70-79)  %2d %-5.2f%%\n", Medium, 1.0*Medium / (*studentNumber) * 100);
		printf("及格(60-69)  %2d %-5.2f%%\n", Pass, 1.0*Pass / (*studentNumber) * 100);
		printf("不及格(0-59) %2d %-5.2f%%\n", Fail, 1.0*Fail / (*studentNumber) * 100);
		Excellente = 0, Fine = 0, Medium = 0, Pass = 0, Fail = 0;
	}
	returnUserFace();
}
//打印没门成绩和总分平均分
void Print2(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i, j;//控制读取的学生数和科目数
	for (i = 0; i < *studentNumber; i++)
	{
		printf("%-12s%-10s分数是 ", student[i].id, student[i].name);
		for (j = 0; j < *subjectNumber; j++)
		{
			printf("%-8.2f", student[i].examScore[j]);
		}
		//     printf("总分是 %-8.2f平均分是 %-8.2f",student[i].sumScore,student[i].sumScore/(*subjectNumber));
		printf("\n");
	}
	returnUserFace();
}
//单独计算总分
void sumAndAveStudentSore2(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i, j;
	float sum = 0;
	for (i = 0; i < *studentNumber; i++)
	{
		sum = 0;
		for (j = 0; j < *subjectNumber; j++)
		{
			sum += student[i].examScore[j];
		}
		//student[i].sumScore=sum;
	}

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
	ScoreMenu(course);

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
		ScoreMenu(course);
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
		printf("It will be returned to Score Menu after 3 seconds");
		Sleep(3000);
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
	for (i = 0; i < 5; i++) {
		assignmentNumber = i + 1;
		printf("%d %12s\n", assignmentNumber, (*course).assignment[i]);
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
	int i, size = 0;
	//get size
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			size = i; break;
		}
	}

	if (size == 9) {
		printf("Unable to add notice! Please delete the notice.\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	printf("Enter notice ");
	scanf("%s", course->notice[size]);

	printf("[%d] notice is successfully registered!\n", size + 1);

	//display notice
	for (i = 0; i <= size; i++)
		printf("Notice [%d]\n%s\n\n", i + 1, course->notice[i]);
	printf("It will return to notice menu 3 seconds later\n");
	Sleep(3000);
}

void ModifyNotice(COURSE *course)
{
	int i, a, size = 0;
	//get size
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			size = i; break;
		}
	}

	if (size == 0) {
		printf("There are no notices to modify\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	//display notice
	for (i = 0; i < size; i++)
		printf("Notice [%d]\n%s\n\n", i + 1, course->notice[i]);

	printf("Select notice to modify ");
	scanf("%d", &a);

	printf("Enter notice ");
	scanf("%s", course->notice[a - 1]);

	printf("[%d] notice is successfully modified!\n", a);
	Sleep(1500);

}

void DeleteNotice(COURSE *course)
{
	int i, a, size = 0;
	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			size = i; break;
		}
	}

	if (size == 0) {
		printf("There are no notices to delete\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	//display notice
	for (i = 0; i < size; i++)
		printf("Notice [%d]\n%s\n\n", i + 1, course->notice[i]);

	printf("Select notice to delete ");
	scanf("%d", &a);

	for (i = a; i < 10; i++)
		strcpy(course->notice[i - 1], course->notice[i]);

	printf("[%d] notice is successfully deleted!\n", a);
	Sleep(1500);
}

void PrintNotice(COURSE *course)
{
	int i, size = 0;

	for (i = 0; i < 10; i++) {
		if (strlen(course->notice[i]) == 0) {
			size = i; break;
		}
	}

	if (size == 0) {
		printf("There are no notices to display\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	for (i = 0; i < size; i++)
		printf("Notice [%d]\n%s\n\n", i + 1, course->notice[i]);
	printf("It will return to notice menu 3 seconds later\n");
	Sleep(3000);
}