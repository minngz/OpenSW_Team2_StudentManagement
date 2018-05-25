#include <stdio.h>
#include <stdlib.h>
//#include "management.h"
#include "file.h"

#define MAX_ASSIGNMENT 5
#define MAX_NOTICE 10

/*
*   COURSE *course - the component of course that user want to add data from file.
*   int studentCount - the number of student would be stored in this variable from text file.
*   int existNoticeCount - the number of existing notice by using strlen.
*   int existAssignmentCount -  the number of existing assignment by using strlen.
*   int newNoticeCount - the integer that read from file and means the number of notice in file.
*   int newAssignmentCount - the integer that read from file and means the number of notice in file.
*
*   This function uses file which name is "sample_course.txt".
*	Information format of the file should be like this.
*   -------------------------------------------------------------------------------------------
*   5
*   122172 suckho 80.0 90.0 7.0 10.0 6.0 10.0 7.0
*   122211 youngho 95.0 95.0 7.0 10.0 8.0 10.0 0.0
*   13011045 jongwon 70.0 50.0  0.0 10.0 0.0 10.0 0.0
*   15010982 minji 90.0 95.0 10.0 10.0 10.0 10.0 8.0
*   15011046 haeun 95.0 90.0 10.0 10.0 7.0 10.0 5.0
*   3
*   There is no lecture on 6, June.
*   Final exam will be on 18, June.
*   The last assignment should be done with your team member and submit report until friday.
*   3
*   Review of open source video
*   OSS survey and presentation
*   Development plan
*   --------------------------------------------------------------------------------------------
*
*   First line is number of students and 2~6 line is
*   [ studentID | name | midterm-score | finalExam-score | assignment score 0~4 ]
*   Next integer is number of notice, after then you just write what you want to notify.
*   The last Integer is number of assignment. you can add explain about assignment on next line.
*/
void ReadFile(COURSE *course)
{
	FILE *file;
	int i, j;
	int studentCount;
	int existNoticeCount;
	int existAssignmentCount;
	int newNoticeCount;
	int newAssignmentCount;

	system("cls");
	file = fopen("sample_course.txt", "r"); // open "sample_course.txt" file by "read" mode. 

	if (file == NULL)
	{
		printf("\n\n   Cannot open the file\n");
		exit(0);
	}
	else
	{
		fscanf(file, "%d", &studentCount);
		fscanf(file, "\n");

		// Read all information of student array on the next row.
		for (i = course->studentCount; i < course->studentCount + studentCount; i++)
		{
			fscanf(file, "%s%s", (*course).student[i].id, (*course).student[i].name);
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

		printf("\n\n   File data is successfully loaded!\n\n");
		printf("\n   It will return to course menu 3 seconds later");
		Sleep(3000);
	} // "sample_course.txt" exist

	fclose(file);
}

/*
*   COURSE *course - the component of course that user want to add data to file.
*	File *file - file variables to open, write, and close the txt file.
*   int noticeCount - the number of existing notice by using strlen.
*   int assignmentCount - the number of existing assignment by using strlen.
*
*   sample_course.txt - WriteFile function uses file which name is "sample_course.txt".
*   So if you have "sample_course.txt" and it contains important information,
*   you should change your file name to another.
*
*   1-1) If the file exists,
*   it writes the total number of students(studentCount) in the first row.
*   Then, it writes information of student(STUDNET array) one row by one.
*   The information contains student ID, name, exam score and assignment score.
*   Next, it writes the total number of assignment notice and details about assignment on next line.
*   Finally, it writes the number of notice and details same as assignment.
*
*   1-2) If the file doens't exist,
*   Print the "Cannot open the file" on console windows and exit program.
*
*   2) Finally, it closes the file and print success message.
*/
void WriteFile(COURSE *course)
{
	FILE *file;
	int i, j;
	int noticeCount;
	int assignmentCount;

	file = fopen("sample_course.txt", "w");

	if (file == NULL)
	{
		printf("\n\n   Cannot open the file\n");
		exit(0);
	}
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

	fclose(file);
	printf("\n\n   Write data is successfully done!\n\n");
	printf("   It will return to course menu 3 seconds later");
	Sleep(3000);
}
