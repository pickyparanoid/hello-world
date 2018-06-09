#include <iostream>
#include <string.h>

using namespace std;

class Stu
{
    char Name[20];	//学生姓名
	float Chinese;		//语文成绩
	float Math;		//数学成绩
public:
    Stu(char*,float,float);
	float Average(void);	//计算平均成绩
	float Sum(void);	//计算总分
	void Show(void);	//打印信息
	void SetStudent(char*,float,float);//为对象置姓名、成绩
	void SetName(char *);	//为对象置姓名
	char *GetName(void);	//取得学生姓名
};

Stu::Stu(char* x,float y,float z)
{
    strcpy(Name,x);
    Chinese = y;
    Math = z;
}

float Stu::Sum(void)
{
    return Chinese+Math;
}

char * Stu::GetName(void)
{
    return Name;
}

void max(Stu *t)
{
    int maximum = 0;
    Stu *tp = t;
    for (int i=0 ; i < 5 ; i++)
    {
        if (t->Sum() > maximum)
        {
            maximum = t->Sum();
            tp = t;
        }
        t++;
    }
    cout << tp->GetName() << endl;
}

int main()
{
    Stu stu[5] = {Stu("name1",65,97),
                  Stu("name2",64,35),
                  Stu("name3",87,105),
                  Stu("name4",90,88),
                  Stu("name5",68,45)};
    max(&stu[0]);
    return 0;
}
