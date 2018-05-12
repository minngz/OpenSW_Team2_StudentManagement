#include <stdio.h>
#include <stdlib.h>
#include"student.h"

int main()
{
	int studentNumber = 0;
	int subjectNumber = 0;

	COURSE *course;
    
	SystemSet();
	CourseMenu(&course, &subjectNumber);
    return 0;
}