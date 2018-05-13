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
	for (i = 0; i<*studentNumber; i++)
	{
		printf("请输入学号、名字、分数 中间以空格隔开\n");
		scanf("%s%s", student[i].id, student[i].name);
		for (j = 0; j<*subjectNumber; j++)
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
	for (i = 0; i<*subjectNumber; i++)
	{
		sum = 0;
		for (j = 0; j<*studenNumber; j++)
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

/*
int orderBig(const void *a,const void *b)
{
STUDENT *p1=(STUDENT*)a;
STUDENT *p2=(STUDENT*)b;

return (int)((p1->sumScore)-(p2->sumScore));
}
int orderSmall(const void *a,const void *b)
{
STUDENT *p1=(STUDENT*)a;
STUDENT *p2=(STUDENT*)b;
return (int)((p2->sumScore)-(p1->sumScore));
}
*/

int orderNumber(const void *a, const void *b)
{
	STUDENT *p1 = (STUDENT*)a;
	STUDENT *p2 = (STUDENT*)b;
	return (p2->id) - (p1->id);
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
	for (i = 0; i<*studentNumber; i++)
	{
		printf("%-12s%-10s ", student[i].id, student[i].name);
		for (j = 0; j<*subjectNumber; j++)
		{
			printf("%-8.2f ", student[i].examScore[j]);
		}
		printf("\n");
	}
	returnUserFace();
}
//按名字查找
void nameSearch(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i = 0, j, k = 0;
	char c;
	char name[30];
E:
	printf("请输入学生的名字\n"); //循环开端
						  //getchar();
	k = 0;
	scanf("%s", name);
	for (i = 0; i<*studentNumber; i++)
	{
		if (strcmp(name, student[i].name) == 0)
		{
			printf("%-12s%-10s", student[i].id, student[i].name);
			for (j = 0; j<*subjectNumber; j++)
				printf("%-8.2f", student[i].examScore[j]);
			k = 1;
		}

	}
	if (k == 1)
		putchar(10);
	else printf("没找到学生\n");
	getchar();
E1:
	printf("输\"n\"结束或者输入\"y\"继续\n");

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
//按学号查找
void numberSearch(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	int i = 0, j, k = 0;
	char c, number[10];
E:
	printf("请输入学号\n");//循环开端
					  //getchar();
	k = 0;
	scanf("%s", number);
	for (i = 0; i<*studentNumber; i++)
	{
		if (strcmp(student[i].id, number) == 0)
		{
			printf("%-12s%-10s ", student[i].id, student[i].name);
			for (j = 0; j<*subjectNumber; j++)
				printf("%-8.2f", student[i].examScore[j]);
			k = 1;
		}

	}
	if (k == 1)
		putchar(10);
	else printf("没找到学生\n");
	getchar();
E1:
	printf("输\"n\"结束或者输入\"y\"继续\n");

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
int Excellente = 0, Fine = 0, Medium = 0, Pass = 0, Fail = 0;
//分类成绩
void SortScore(STUDENT *student, int *studentNumber, int *subjectNumber)
{
	Excellente = 0, Fine = 0, Medium = 0, Pass = 0, Fail = 0;
	int i, j;
	for (i = 0; i<*subjectNumber; ++i)
	{
		for (j = 0; j<*studentNumber; ++j)
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
	for (i = 0; i<*studentNumber; i++)
	{
		printf("%-12s%-10s分数是 ", student[i].id, student[i].name);
		for (j = 0; j<*subjectNumber; j++)
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
	for (i = 0; i<*studentNumber; i++)
	{
		sum = 0;
		for (j = 0; j<*subjectNumber; j++)
		{
			sum += student[i].examScore[j];
		}
		//student[i].sumScore=sum;
	}

}

void WriteFile(STUDENT *student, int *studentNum, int *subjectNum)
{
	/*
	∴ Function Name
	- WriteFile

	∴ Parameter ([type] name)
	- [STU*] student       : Array of STU which contains student's information
	ex) name, student ID, array of score, total score, average score
	- [int*] studentNumber : Total number of students
	- [int*] subjectNumber : Total number of subjects

	∴ File
	- student.txt
	: WriteFile function uses file which name is "student.txt".
	So if you have "student.txt" and it contains important information, you should change your file name to another.

	∴ Description
	- 1) WriteFile function open or create the file which name is "student.txt".

	2-1) If the file exists,
	it writes the total number of students(studentNum) and subject(subjectNum) in the first row.
	Then, it writes information of student(student array) one row by one.
	The information contains student number, name, score, total score and average score.

	2-2) If the file doens't exist,
	Print the "Cannot open the file" on console windows and exit program.

	3) Finally, it closes the file and print "Successful File write!"
	*/

	FILE *file;        // file variables to open, write, and close the txt file
	int i, j;           // int variables for "for statement"

	file = fopen("student.txt", "w"); // open "student.txt" file by "write" mode. 
									  // if it doesn't exist, it makes new "student.txt" file.

	if (file == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	} // "student.txt" doesnt' exist
	else
	{
		/*
		There is two way to write information on file.
		1) If you want to write information by printf format, you can use 'fprintf'
		2) If not, you can use 'fwrite' which write all of information in buffer.
		*/

		// Write total number of student and subject on the first row.
		fprintf(file, "%d %d\n", *studentNum, *subjectNum);  // 1) fprintf
															 //fwrite(student,sizeof(STU),*studentNumber,p);   // 2) fwrite

															 // Write all information of student array on the next row.
		for (i = 0; i<*studentNum; i++)
		{
			fprintf(file, "%-12s%-10s ", student[i].id, student[i].name);

			for (j = 0; j<*subjectNum; j++)
			{
				fprintf(file, "%-8.2f", student[i].examScore[j]);
			}
			fprintf(file, "\n");
		}
	} // "student.txt" exist

	fclose(file);   // close the file
	printf("Successful File write!");
	returnUserFace();
}



void ReadFile(STUDENT *student, int *studentNum, int *subjectNum)
{
	/*
	∴ Function Name
	- ReadFile

	∴ Parameter ([type] name)
	- [STU*] student       : Array of STU which contains student's information
	ex) name, student ID, array of score, total score, average score
	- [int*] studentNumber : Total number of students
	- [int*] subjectNumber : Total number of subjects

	∴ File
	- student.txt
	: ReadFile function uses file which name is "student.txt".
	So if you want to read information from your file, you should change your file name to "student.txt"
	and the information format should be like this.

	---------------------------------------------------------------------------------------------------------------
	11 5
	13011040    Jongwon    63.00   63.00   100.00  10.00   36.00    272.00   54.40
	13011041    Minji      63.00   63.00   100.00  10.00   36.00    272.00   54.40
	13011042    Younghov   71.00   56.00   41.00   26.00   71.00    265.00   53.00
	13011043    Haein      66.00   56.00   46.00   36.00   66.00    270.00   54.00
	13011044    Seokho     78.00   56.00   63.00   63.00   78.00    338.00   67.60
	13011045    Dohyun     75.00   84.00   56.00   56.00   75.00    346.00   69.20
	13011046    Taegyun    91.00   80.00   56.00   49.00   91.00    367.00   73.40
	13011047    Jangwon    78.00   54.00   63.00   42.00   78.00    315.00   63.00
	13011048    Jaehyuk    64.00   84.00   56.00   84.00   64.00    352.00   70.40
	13011049    Moonsoo    84.00   80.00   77.00   80.00   84.00    405.00   81.00
	13011050    Myungho    80.00   54.00   41.00   54.00   80.00    309.00   61.80
	---------------------------------------------------------------------------------------------------------------

	Total number of students(11) and subjects(5) should be on the first row.
	Then, student_number(13011045) name(Jongwon) subject1_score(63.00) subject2_score(63.00) ... subject5_score(36)
	total_score(272.00) average_score(54.40) should be placed on one row by one student.


	∴ Description
	- 1) ReadFile function open the file which name is "student.txt".

	2-1) If the file exists,
	it reads the total number of students(studentNum) and subject(subjectNum) in the first row.
	Then, it reads information of student(student array) one row by one.
	The information contains student number, name, score, total score and average score.

	2-2) If the file doens't exist,
	Print the "Cannot open the file" on console windows and exit program.

	3) Finally, closes the file.
	*/


	int i, j;           // int variables for "for statement"

	FILE *file;         // file variables to open, write, and close the txt file
	file = fopen("student.txt", "r"); // open "student.txt" file by "read" mode. 

	if (file == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	} // "student.txt" doesnt' exist
	else
	{
		/*
		There is two way to read information on file.
		1) If you want to read information by scanf format, you can use 'fscanf'
		2) If not, you can use 'fread' which read bytes of file at once.
		*/

		// Read total number of student and subject on the first row.
		fscanf(file, "%d%d", studentNum, subjectNum);     // 1) fscanf
		fscanf(file, "\n");
		//fread(student,sizeof(STU),*studentNumber,p);    // 2) fread

		// Read all information of student array on the next row.
		for (i = 0; i<*studentNum; i++)
		{
			fscanf(file, "%s%s", student[i].id, student[i].name);

			for (j = 0; j<*subjectNum; j++)
			{
				fscanf(file, "%f", &student[i].examScore[j]);
			}

			fscanf(file, "\n");
		}
	} // "student.txt" exist

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
	printf("\n           [ Management ]  \n\n");
	printf(" 1.     Score    Management \n");
	printf(" 2.   Assignment Management \n");
	printf(" 3.     Student  Management \n");
	printf(" 4.     Notice   Management \n");
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
	printf(" 5.    FileWrite \n");
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
	printf(" 5.   FileRead \n");
	printf(" 6.   FileWrite \n");
	printf("ESC.    Back \n\n");
}

void PrintNoticeMenu()
{
	system("cls");
	printf("\n        [ Notice ]  \n\n");
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.     Delete \n");
	printf("ESC.     Back \n\n");
}

void PrintCourseList(COURSE **course, int *subjectNumber)
{
	int i;

	system("cls");
	printf("\n        [ Course Select ]   \n\n");

	for (i = 0; i < *subjectNumber; i++)
	{
		printf(" %d.   %15s\n", i, (*course)[i].name);
	}
}

void CourseMenu(COURSE **course, int *subjectNumber)
{
	char menuInput;
	
	while(1)
	{
		PrintCourseMenu();
		menuInput = getch();

		switch (menuInput)
		{
		case '1':
			RegisterCourse(course, subjectNumber);
			break;

		case '2':
			ModifyCourse(course);
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
	char courseName[20];

	printf("please insert name of new subject\n");	
	gets(courseName);

	if (*subjectNumber == 0)
	{
		*course = (COURSE*)malloc(sizeof(COURSE));
		(*course)->studentNumber = 0;
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
		(*course)[*subjectNumber].studentNumber=0;
	}

	strcpy((*course)[*subjectNumber].name, courseName);
	*subjectNumber += 1;

	printf("[ %s ] course is successfully registed!\n\n", (*course)[*subjectNumber-1].name);
	printf("It will return to course menu 3 seconds later\n");
	Sleep(3000);
}

void ModifyCourse(COURSE **course)
{

}

void DeleteCourse(COURSE **course, int *subjectNumber)
{

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
			DeleteScore();
			break;

		case '4':
			PrintScore(course, PRINTTYPE_ALL, 0);
			break;

		case '5':
			WriteScoreFile();
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
	system("cls");

	int studentID;
	double midtermScore;
	double finalScore;
	int studentIndex = 0;

	printf("Input student ID to register score: ");
	scanf("%d", &studentID);
	printf("\n");

	printf("Input midterm score : ");
	scanf("%lf", &midtermScore);
	printf("\n");

	printf("Input final score : ");
	scanf("%lf", &finalScore);
	printf("\n");

	for (int i = 0; i < course->studentNumber; i++)
	{
		if (course->student[i].id == studentID) 
		{
			studentIndex = i;
		}
	}
	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	printf("Registration is Succeed!\n");
	printf("(It will be returned to Score Menu after 2 seconds automatically)");
	Sleep(2000);
	ScoreMenu(course);
}

void ModifyScore(COURSE *course)
{
	
}

void DeleteScore()
{

}

void PrintScore(COURSE *course, int printType, int studentIndex)
{
	
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
			RegisterAssignment();
			break;

		case '2':
			ModifyAssignment();
			break;

		case '3':
			DeleteAssignment();
			break;

		case '4':
			PrintAssignment();
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}

void RegisterAssignment()
{

}

void ModifyAssignment()
{

}

void DeleteAssignment()
{

}

void PrintAssignment()
{

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
			RegisterStudent();
			break;

		case '2':
			ModifyStudent();
			break;

		case '3':
			DeleteStudent();
			break;

		case '4':
			PrintStudent();
			break;

		case '5':
			ReadStudentFile();
			break;

		case '6':
			WriteStudentFile();
			break;

		case ESC:
			return;

		default:
			break;
		}
	}
}

void RegisterStudent()
{

}

void ModifyStudent()
{

}

void DeleteStudent()
{

}

void PrintStudent()
{

}

void ReadStudentFile()
{

}

void WriteStudentFile()
{

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
			RegisterNotice();
			break;

		case '2':
			ModifyNotice();
			break;

		case '3':
			DeleteNotice();
			break;

		case ESC:
			return;
		
		default:
			break;
		}
	}
}

void RegisterNotice()
{

}

void ModifyNotice()
{

}

void DeleteNotice()
{

}
