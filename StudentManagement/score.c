#include <stdio.h>
#include <stdlib.h>
#include "score.h"

#define PRINTTYPE_EDIT 1
#define PRINTTYPE_DELETE 2
#define PRINTTYPE_ALL 3

/*
*	If user wants to register score of student, this RegisterScore function will be performed.
*
*	1) Getting input studentID from user
*	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
*	2-2) If studentId exists, user has to input midterm-score and final-score to register.
*	3) Informations about scores will be stored in 'examScore' array which index of 0 means midterm-score and index of 1 means final-score.
*	   (You have to input score from 0 to 100. Because deleted score will be treated as 300)
*	4) After this process, the score will be registered in student's examScore variable who user input.
*/
void RegisterScore(COURSE *course)
{

	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	PrintRegisterScoreID();

	scanf("%s", studentID);
	printf("\n");

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

	PrintRegisterMidtermScore();
	scanf("%lf", &midtermScore);
	printf("\n");

	PrintRegisterFinalScore();
	scanf("%lf", &finalScore);
	printf("\n");

	course->student[studentIndex].examScore[0] = midtermScore;
	course->student[studentIndex].examScore[1] = finalScore;

	system("cls");
	printf("\n\n   Registration is Succeed!\n");
	printf("(   It will be returned to Score Menu after 3 seconds automatically)");
	Sleep(3000);
}

/*
*	If user wants to modify score of student, this ModifyScore function will be performed.
*
*	1) Getting input studentID from user
*	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
*	2-2) If studentId exists, user has to input midterm-score and final-score to modify.
*	3) Informations about scores will be stored in 'examScore' array which index of 0 means midterm-score and index of 1 means final-score.
*	   (You have to input score from 0 to 100. Because deleted score will be treated as 300)
*	4) After this process, the score will be modified in student's examScore variable who user input.
*/
void ModifyScore(COURSE *course)
{
	char studentID[10];
	double midtermScore;
	double finalScore;
	int studentIndex = -1;

	PrintModifyScoreID();
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

	PrintModifyMidtermScore();
	scanf("%lf", &midtermScore);
	getchar();

	PrintModifyFinalScore();
	scanf("%lf", &finalScore);
	getchar();

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

/*
*	If user wants to delete score of student, this DeleteScore function will be performed.
*
*	1) Getting input studentID from user
*	2-1) If studentID doesn't exists, it will be returned to score menu after 3 seconds automatically.
*	2-2) If score was deleted, it will be returned to score menu after 3 seconds automatically.
*	3) Ask to user really want to delete score of input student's
*	4-1) If confirm is yes, the score will be deleted(modify score to 300)
*	4-2) if confrim is no, it will be returned to score menu after 3 secons autmatically.
*/
void DeleteScore(COURSE *course)
{
	char studentID[10];
	int studentIndex = -1;
	char confirm = ' ';

	PrintDeleteScoreID();

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

/*
*	If user wants to print score of student or every scores of students and average score of this course, this PrintScore function will be performed.
*
*	1) Classify Print type.
*	2-1) If print type is ALL, prints all of students' scores and average score in a course.
*	2-2) If print type is editing or deleting, prints a score of one student's who user input.
*/
void PrintScore(COURSE *course, int printType, int studentIndex)
{
	int i;

	printf("\n\n");
	// Case every students' scores in this course.
	if (printType == PRINTTYPE_ALL)
	{
		if (course->studentCount == 0)
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

/*
*	If print-type was PRINTTYPE_ALL in PrintScore function, this method is called.
*
*	1) Classify Print type.
*	2) Using for loop, every scores of midterm-score add to midtermSum and every scores of final-score add to finalSum.
*	3) final_register_count is counting only registered score of registered students.
*/
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