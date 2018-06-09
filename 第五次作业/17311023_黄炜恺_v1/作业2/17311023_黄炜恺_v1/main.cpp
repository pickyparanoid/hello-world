#include <iostream>
#include <string.h>

using namespace std;

class Stu
{
    char Name[20];	//ѧ������
	float Chinese;		//���ĳɼ�
	float Math;		//��ѧ�ɼ�
public:
    Stu(char*,float,float);
	float Average(void);	//����ƽ���ɼ�
	float Sum(void);	//�����ܷ�
	void Show(void);	//��ӡ��Ϣ
	void SetStudent(char*,float,float);//Ϊ�������������ɼ�
	void SetName(char *);	//Ϊ����������
	char *GetName(void);	//ȡ��ѧ������
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
