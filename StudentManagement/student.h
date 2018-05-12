#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#define ESC 27

#include <stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct student
{
    char id[10];
    char name[60];
    double examScore[10];
	double assignmentScore[10];
}STUDENT;

typedef struct course
{
	char name[60];
	STUDENT student[100];
	char notice[10][60];
	char assignment[10][60];
}COURSE;

//函数声明部分
void readDate(STUDENT *student,int *studentNumber,int *subjectNumber);
void returnUserFace();
void sumAndAveSubjectSore(STUDENT *student,int *studenNumber,int *subjectNumber);
void sumAndAveStudentSore(STUDENT *student,int *studenNumber,int *subjectNumber);
//int orderBig(const void *a,const void *b);
//int orderSmall(const void *a,const void *b);
void Print(STUDENT *student,int *studenNumber,int *subjectNumber);
int orderNumber(const void *a,const void *b);
int orderName(const void *a,const void *b);
void nameSearch(STUDENT *student,int *studentNumber,int *subjectNumber);
void numberSearch(STUDENT *student,int *studentNumber,int *subjectNumber);
void SortScore(STUDENT *student,int *studentNumber,int *subjectNumber);
void Print2(STUDENT *student,int *studentNumber,int *subjectNumber);
void sumAndAveStudentSore2(STUDENT *student,int *studenNumber,int *subjectNumber);
void SystemSet();
int ScanfSet();
void WriteFile(STUDENT *student,int *studentNumber,int *subjectNumber);
void ReadFile(STUDENT *student,int *studentNumber,int *subjectNumber);
void SystemSet();
void PrintCourseMenu();
void PrintManagementMenu();
void PrintScoreMenu();
void PrintAssignmentMenu();
void PrintStudentMenu();
void PrintNoticeMenu();
void RegisterCourse();
void ModifyCourse();
void DeleteCourse();
void ManagementMenu();
void ScoreMenu();
void RegisterScore();
void ModifyScore();
void DeleteScore();
void PrintScore();
void WriteScoreFile();
void AssignmentMenu();
void RegisterAssignment();
void ModifyAssignment();
void DeleteAssignment();
void PrintAssignment();
void StudentMenu();
void RegisterStudent();
void ModifyStudent();
void DeleteStudent();
void PrintStudent();
void ReadStudentFile();
void WriteStudentFile();
void NoticeMenu();
void RegisterNotice();
void ModifyNotice();
void DeleteNotice();

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
    scanf("%d",&n);
    return n;
}

//读取数据
void readDate(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i,j;//控制读取的学生数和科目数
    //FILE *p = freopen("test.txt","r",stdin);
    printf("请输入学生的数目\n");
    scanf("%d",studentNumber);
    printf("请输入科目数\n");
    scanf("%d",subjectNumber);
    getchar();
    for(i=0; i<*studentNumber; i++)
    {
        printf("请输入学号、名字、分数 中间以空格隔开\n");
        scanf("%s%s",student[i].id,student[i].name);
        for(j=0; j<*subjectNumber; j++)
        {
            scanf("%lf",&student[i].examScore[j]);
        }
    }
    //fclose(p);
    returnUserFace();
}

//返回用户界面
void returnUserFace()
{
    while(getchar()!='\n');
    system("pause");
    system("cls");
}

void sumAndAveSubjectSore(STUDENT *student,int *studenNumber,int *subjectNumber)
{
    int i,j;
    double sum;
    for(i=0; i<*subjectNumber; i++)
    {
        sum=0;
        for(j=0; j<*studenNumber; j++)
        {
            sum+=student[j].examScore[i];
        }
        printf("学科%d 的总分是 %-8.2lf ",i+1,1.0*sum);
        printf("平均分是 %-8.2lf\n",1.0*sum/(*studenNumber));
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

int orderNumber(const void *a,const void *b)
{
    STUDENT *p1=(STUDENT*)a;
    STUDENT *p2=(STUDENT*)b;
    return (p2->id)-(p1->id);
}
int orderName(const void *a,const void *b)
{
    STUDENT *p1=(STUDENT*)a;
    STUDENT *p2=(STUDENT*)b;
    return strcmp((p1->name),(p2->name));
}
void Print(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i,j;//控制读取的学生数和科目数
    for(i=0; i<*studentNumber; i++)
    {
        printf("%-12s%-10s ",student[i].id,student[i].name);
        for(j=0; j<*subjectNumber; j++)
        {
            printf("%-8.2f ",student[i].examScore[j]);
        }
        printf("\n");
    }
    returnUserFace();
}
//按名字查找
void nameSearch(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i=0,j,k=0;
    char c;
    char name[30];
E:
    printf("请输入学生的名字\n"); //循环开端
    //getchar();
    k=0;
    scanf("%s",name);
    for(i=0; i<*studentNumber; i++)
    {
        if(strcmp(name,student[i].name)==0)
        {
            printf("%-12s%-10s",student[i].id,student[i].name);
            for(j=0; j<*subjectNumber; j++)
                printf("%-8.2f",student[i].examScore[j]);
            k=1;
        }

    }
    if(k==1)
        putchar(10);
    else printf("没找到学生\n");
    getchar();
E1:
    printf("输\"n\"结束或者输入\"y\"继续\n");

    scanf("%c",&c);
    if(c=='y')
        goto E;
    else if(c=='n')
        returnUserFace();
    else
    {
        while(getchar()!='\n');
        goto E1;
    }


}
//按学号查找
void numberSearch(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i=0,j,k=0;
    char c,number[10];
E:
    printf("请输入学号\n");//循环开端
    //getchar();
    k=0;
    scanf("%s",number);
    for(i=0; i<*studentNumber; i++)
    {
        if(strcmp(student[i].id,number)==0)
        {
            printf("%-12s%-10s ",student[i].id,student[i].name);
            for(j=0; j<*subjectNumber; j++)
                printf("%-8.2f",student[i].examScore[j]);
            k=1;
        }

    }
    if(k==1)
        putchar(10);
    else printf("没找到学生\n");
    getchar();
E1:
    printf("输\"n\"结束或者输入\"y\"继续\n");

    scanf("%c",&c);
    if(c=='y')
        goto E;
    else if(c=='n')
        returnUserFace();
    else
    {
        while(getchar()!='\n');
        goto E1;
    }

}
int Excellente=0,Fine=0,Medium=0,Pass=0,Fail=0;
//分类成绩
void SortScore(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    Excellente=0,Fine=0,Medium=0,Pass=0,Fail=0;
    int i,j;
    for(i=0; i<*subjectNumber; ++i)
    {
        for(j=0; j<*studentNumber; ++j)
        {
            if(student[j].examScore[i]>=90) Excellente++;
            else if(student[j].examScore[i]>=80) Fine++;
            else if(student[j].examScore[i]>=70) Medium++;
            else if(student[j].examScore[i]>=60) Pass++;
            else Fail++;
        }
        printf("科目 %d\n",i+1);
        printf("优秀(90-100) %2d %-5.2f%%\n",Excellente,1.0*Excellente/(*studentNumber)*100);
        printf("良好(80-89)  %2d %-5.2f%%\n",Fine,1.0*Fine/(*studentNumber)*100);
        printf("中等(70-79)  %2d %-5.2f%%\n",Medium,1.0*Medium/(*studentNumber)*100);
        printf("及格(60-69)  %2d %-5.2f%%\n",Pass,1.0*Pass/(*studentNumber)*100);
        printf("不及格(0-59) %2d %-5.2f%%\n",Fail,1.0*Fail/(*studentNumber)*100);
        Excellente=0,Fine=0,Medium=0,Pass=0,Fail=0;
    }
    returnUserFace();
}
//打印没门成绩和总分平均分
void Print2(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i,j;//控制读取的学生数和科目数
    for(i=0; i<*studentNumber; i++)
    {
        printf("%-12s%-10s分数是 ",student[i].id,student[i].name);
        for(j=0; j<*subjectNumber; j++)
        {
            printf("%-8.2f",student[i].examScore[j]);
        }
   //     printf("总分是 %-8.2f平均分是 %-8.2f",student[i].sumScore,student[i].sumScore/(*subjectNumber));
        printf("\n");
    }
    returnUserFace();
}
//单独计算总分
void sumAndAveStudentSore2(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    int i,j;
    float sum=0;
    for(i=0; i<*studentNumber; i++)
    {
        sum=0;
        for(j=0; j<*subjectNumber; j++)
        {
            sum+=student[i].examScore[j];
        }
        //student[i].sumScore=sum;
    }

}
//写文件操作
void WriteFile(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    FILE *p;
    int i,j;//控制读取的学生数和科目数
    if((p=fopen("student.txt","w"))==NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    else
    {
        //fwrite(student,sizeof(STUDENT),*studentNumber,p); //按模块存
        fprintf(p,"%d %d\n",*studentNumber,*subjectNumber);
        for(i=0; i<*studentNumber; i++)
        {
            fprintf(p,"%-12s%-10s ",student[i].id,student[i].name);
            for(j=0; j<*subjectNumber; j++)
            {
                fprintf(p,"%-8.2f",student[i].examScore[j]);
            }
            fprintf(p,"\n");
        }
    }
    fclose(p);
    printf("写入成功\n");
    returnUserFace();
}
//读取文件1
void ReadFile(STUDENT *student,int *studentNumber,int *subjectNumber)
{
    FILE *p;
    int i,j;//控制读取的学生数和科目数
    if((p=fopen("student.txt","r"))==NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    else
    {
        //fread(student,sizeof(STUDENT),*studentNumber,p);//按模块区取
        fscanf(p,"%d%d",studentNumber,subjectNumber);
        for(i=0; i<*studentNumber; i++)
        {
            fscanf(p,"%s%s",student[i].id,student[i].name);
            for(j=0; j<*subjectNumber; j++)
            {
                fscanf(p,"%f",&student[i].examScore[j]);
            }
            fscanf(p,"\n");
        }
    }
    fclose(p);



}


//读取文件2
//void ReadFile(STUDENT *student,int *studentNumber,int *subjectNumber)
//{
//    int i,j;//控制读取的学生数和科目数
//    scanf("%d%d",studentNumber,subjectNumber);
//        for(i=0; i<*studentNumber; i++)
//        {
//            scanf("%s%s",student[i].number,student[i].name);
//            for(j=0; j<*subjectNumber; j++)
//            {
//                scanf("%f",&student[i].examScore[j]);
//            }
//            scanf("%f%f",&student[i].sumScore,&student[i].avescore);
//        }
//}


void PrintCourseMenu()
{
	system("cls");
	printf("\n       [ Course ]  \n\n");;
	printf("1.     Register \n");
	printf("2.     Modifiy \n");
	printf("3      Delete \n");
	printf("4.     Manage \n");
	printf("ESC.    Back \n\n");
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
	printf("\n        [ Score ]  \n\n");;
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
	printf("\n      [ Assignment ]  \n\n");;
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.     Delete \n");
	printf(" 4.     Print \n");
	printf("ESC.     Back \n\n");
}

void PrintStudentMenu()
{
	system("cls");
	printf("\n      [ Student ]  \n\n");;
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
	printf("\n        [ Notice ]  \n\n");;
	printf(" 1.    Register \n");
	printf(" 2.    Modifiy \n");
	printf(" 3.     Delete \n");
	printf("ESC.     Back \n\n");
}

void CourseMenu()
{
	char menuInput;

	PrintCourseMenu();
	menuInput = getch();

	switch (menuInput)
	{
	case '1':
		RegisterCourse();
		break;

	case '2':
		ModifyCourse();
		break;

	case '3':
		DeleteCourse();
		break;

	case '4':
		ManagementMenu();
		break;

	default:
		printf("Wrong Input\n");
		break;
	}
}

void RegisterCourse()
{

}

void ModifyCourse()
{

}

void DeleteCourse()
{

}

void ManagementMenu()
{
	char menuInput;

	PrintManagementMenu();
	menuInput = getch();
	
	switch (menuInput)
	{
	case '1':
		ScoreMenu();
		break;

	case '2':
		AssignmentMenu();
		break;

	case '3':
		StudentMenu();
		break;

	case '4':
		NoticeMenu();
		break;

	case ESC:
		CourseMenu();
		break;

	default:
		printf("Wrong Input\n");
		break;
	}
}

void ScoreMenu()
{
	char menuInput;

	PrintCourseMenu();
	menuInput = getch();

	switch (menuInput)
	{
	case '1':
		RegisterScore();
		break;

	case '2':
		ModifyScore();
		break;

	case '3':
		DeleteScore();
		break;

	case '4':
		PrintScore();
		break;

	case '5':
		WriteScoreFile();
		break;

	case ESC:
		ManagementMenu();
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
	char menuInput;

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
		ManagementMenu();
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
	char menuInput;

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
		ManagementMenu();
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

void NoticeMenu()
{
	char menuInput;

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

	case ESC :
		ManagementMenu();
		break;

	default:
		printf("Wrong Input\n");
		break;
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

#endif // STUDENT_H_INCLUDED
