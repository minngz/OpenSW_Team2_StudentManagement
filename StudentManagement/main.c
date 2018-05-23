#include <stdio.h>
#include <stdlib.h>
#include"student.h"

int main()
{
	int courseCount = 0;

	COURSE *course;
	
	SystemSet();
	CourseMenu(&course, &courseCount);
	return 0;
}