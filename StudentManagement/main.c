#include <stdio.h>
#include <stdlib.h>
#include"student.h"
int main()
{
	int studentNumber = 0;
	int subjectNumber = 0;
    STU student[100];
    SystemSet();

	CourseMenu();
	/*
    userInterFace();
    while(1)
    {
        switch(ScanfSet())
        {
        case 0:
            exit(0);
        case 1:
            system("cls");
            readDate(student,&studentNumber,&subjectNumber);
            break;
        case 2:
            system("cls");
            sumAndAveSubjectSore(student,&studentNumber,&subjectNumber);
            break;
        case 3:
            system("cls");
            sumAndAveStudentSore(student,&studentNumber,&subjectNumber);
            break;
        case 4:
            system("cls");
            qsort(student,studentNumber,sizeof(STU),orderBig);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        case 5:
            system("cls");
            qsort(student,studentNumber,sizeof(STU),orderSmall);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        case 6:
            system("cls");
            qsort(student,studentNumber,sizeof(STU),orderNumber);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        case 7:
            system("cls");
            qsort(student,studentNumber,sizeof(STU),orderName);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        case 8:
            system("cls");
            numberSearch(student,&studentNumber,&subjectNumber);
            break;
        case 9:
            system("cls");
            nameSearch(student,&studentNumber,&subjectNumber);
            break;
        case 10:
            system("cls");
            SortScore(student,&studentNumber,&subjectNumber);
            break;
        case 11:
            system("cls");
            sumAndAveStudentSore2(student,&studentNumber,&subjectNumber);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        case 12:
            system("cls");
            sumAndAveStudentSore2(student,&studentNumber,&subjectNumber);
            WriteFile(student,&studentNumber,&subjectNumber);
            break;
        case 13:
            system("cls");
            ReadFile(student,&studentNumber,&subjectNumber);
            sumAndAveStudentSore2(student,&studentNumber,&subjectNumber);
            Print2(student,&studentNumber,&subjectNumber);
            break;
        default:
            system("cls");
            printf("Please input 0-13\n");
            returnUserFace();
            break;
        }
    }*/
    return 0;
}

void CourseMenu()
{
	int menuInput;

	PrintCourseMenu();
	scanf("%d", &menuInput);

	switch (menuInput)
	{
		case 1:			
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		default:
			printf("Wrong Input\n");
		break;
	}
}

void ScoreMenu()
{
	int menuInput;

	PrintCourseMenu();
	scanf("%d", &menuInput);

	switch (menuInput)
	{
	case 1:
		RegisterScore();
		break;

	case 2:
		ModifyScore();
		break;

	case 3:
		DeleteScore();
		break;

	case 4:
		PrintScore();
		break;
	
	case 5:
		WriteScoreFile();
		break;

	default:
		printf("Wrong Input\n");
		break;
	}
}

void RegisterScore()
{

}

void ModifyScore()
{

}

void DeleteScore()
{

}

void PrintScore()
{

}

void WriteScoreFile()
{

}

void AssignmentMenu()
{
	int menuInput;

	PrintAssignmentMenu();
	scanf("%d", &menuInput);

	switch (menuInput)
	{
	case 1:
		RegisterAssignment();
		break;

	case 2:
		ModifyAssignment();
		break;

	case 3:
		DeleteAssignment();
		break;

	case 4:
		PrintAssignment();
		break;

	default:
		printf("Wrong Input\n");
		break;
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

void StudentMenu()
{
	int menuInput;

	PrintStudentMenu();
	scanf("%d", &menuInput);

	switch (menuInput)
	{
	case 1:
		RegisterStudent();
		break;

	case 2:
		ModifyStudent();
		break;

	case 3:
		DeleteStudent();
		break;

	case 4:
		PrintStudent();
		break;

	case 5:
		ReadStudentFile();
		break;

	case 6:
		WriteStudentFile();
		break;

	default:
		printf("Wrong Input\n");
		break;
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

/*
void PrintNoticeMenu()
{
printf("   [ Notice ]  \n\n");;
printf("1. Register \n");
printf("2. Modifiy \n");
printf("3. Delete \n");
}*/