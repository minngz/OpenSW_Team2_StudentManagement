#include <stdio.h>
#include <stdlib.h>
#include"student.h"
int main()
{
    int studentNumber=0,subjectNumber=0;
    STU student[100];
    SystemSet();
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
    }
    return 0;
}




