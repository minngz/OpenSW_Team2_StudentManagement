/*
*	< StudentManagement >
*
*	assignment.c : register, modify, delete, print functions about assignment
*	course.c : init, select, register, modify, delete, print functions about student
*	file.c : read & write functions about file
*	menu.c : menu of course, management, score, assignment, student, notice
*	notice.c : register, modify, delete, print functions about notice
*	score.c : register, modify, delete, print, average functions about score 
*	student.c : search by id, compare by id, register, modify, delete, print functions about course
*	ui.c : UI for printing menu
*
*	Program for managing student scores such as grades and assignments, as well as notices and assginments.
*	Also, this program can read  a file to manage studnets and write the file.
*	We use text file (location : StudentManagement\StudentManagement\sample_course.txt).
*
*	sample_course.txt - ReadFile function uses this file
*   If you want to read information from your file, you should change your file name to
*   "sample_course.txt" and the information format can be found in file.c 
*
*	original source - https://github.com/lylllcc/StudentManagment
*	Released under the MIT license.
*
*	Version - v 1.1
*/
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main()
{
	//init total number of courses to 0
	int courseCount = 0;
	
	//list of courses
	COURSE *course;
	
	SystemSet();
	CourseMenu(&course, &courseCount);
	return 0;
}