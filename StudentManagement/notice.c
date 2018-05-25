#include <stdio.h>
#include <stdlib.h>
//#include "management.h"
#include "notice.h"

/*
*	If user wants to register notice of course, this RegisterNotice function will be performed
*
*	int check : Check whether the notice array is full
*
*	If notice array is not full (check = 1), enter the notice of the course you want to add.
*	Print registered notice and return to the notice menu function().
*/
void RegisterNotice(COURSE *course)
{
	int i, check = 0;
	char newNotice[50];

	PrintRegisterNotice();

	fgets(newNotice, sizeof(newNotice), stdin);
	newNotice[strlen(newNotice) - 1] = '\0';

	for (i = 0; i < 10; i++)
	{
		if (strlen(course->notice[i]) == 0)
		{
			strcpy((*course).notice[i], newNotice);
			check++;
			break;
		}
	}

	if (check == 0)
	{
		system("cls");
		printf("\n\n   Unable to add notice! Please delete the notice.\n");
		Sleep(3000);
		NoticeMenu(course);
	}
	else
	{
		system("cls");
	}

	printf("   Notice [%d] is successfully registered!", i);
	Sleep(3000);

}

/*
*	If user wants to modify notice of course, this ModifyNotice function will be performed
*
*	int check : Check whether the notice array is empty
*
*	If notice array is not empty (check = 1), print registered notices and user will select notice that they want to modify.
*	If the notice you select is not registered ( strlen(course->notice[index]) == 0 ), inform you about this.
*	else enter the notice of the course you want to modify and return to the notice menu function().
*/
void ModifyNotice(COURSE *course)
{
	int i, j, index, check = 0;
	char newNotice[50];

	system("cls");
	//display notice
	for (i = 0; i < 10; i++)
	{
		if (strlen(course->notice[i]) == 0)
		{
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0)
	{
		printf("There are no notices to modify\n");
		Sleep(3000);
		NoticeMenu(course);
	}

	printf("Select notice to modify ");
	scanf("%d", &index);

	while (strlen(course->notice[index]) == 0)
	{
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

/*
*	If user wants to delete notice of course, this DeleteNotice function will be performed
*
*	int check : Check whether the notice array is empty
*
*	If notice array is not empty (check = 1), print registered notices and user will select notice that they want to delete.
*	If the notice you select is not registered ( strlen(course->notice[index]) == 0 ), inform you about this.
*	else delete the notice of the course you want to delete and return to the notice menu function().
*/
void DeleteNotice(COURSE *course)
{
	int i, j, index, check = 0;

	system("cls");
	//display notice
	for (i = 0; i < 10; i++)
	{
		if (strlen(course->notice[i]) == 0)
		{
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0)
	{
		printf("There are no notices to delete\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	printf("Select notice to delete ");
	scanf("%d", &index);

	while (strlen(course->notice[index]) == 0)
	{
		printf("Delete function was not working because notice of that index doesn't exist.\n");
		printf("Select again: ");
		scanf("%d", &index);
	}

	getchar();

	for (i = index; i < 9; i++)
	{
		strcpy(course->notice[i], course->notice[i + 1]);
	}

	printf("Notice [%d] is successfully deleted!", index);
	Sleep(1500);
}

/*
*	If user wants to see the notice of course, this PrintNotice function will be performed
*
*	int check : Check whether the notice array is empty
*
*	If notice array is not empty (check = 1), print registered notices
*	else print("There are no notices to display") and  return to the notice menu function().
*/
void PrintNotice(COURSE *course)
{
	int i, j, check = 0;

	system("cls");
	for (i = 0; i < 10; i++)
	{
		if (strlen(course->notice[i]) == 0)
		{
			for (j = 0; j < i; j++)
				printf("Notice [%d] %s\n", j, (*course).notice[j]);
			check++;
			break;
		}
	}

	if (check == 0)
	{
		printf("There are no notices to display\n");
		Sleep(1500);
		NoticeMenu(course);
	}

	printf("It will return to notice menu 3 seconds later\n");
	Sleep(3000);
}
