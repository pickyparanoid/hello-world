#include <iostream>
#include <string.h>

using namespace std;

const int maxqueue = 10;
enum Error_code{success,underflow,overflow};

template <typename  T> class Queue {
 public:
   Queue();
  bool empty() const;
  Error_code serve();
  Error_code append(const T &item);
  Error_code retrieve(T &item) const;
 protected:
  int count;
  int front;
  int rear;
  T entry[maxqueue];
};

//��ʼ��
template <typename T> Queue <T>::Queue()
{
    count = 0;
    front = 0 ;
    rear = 0;
}

//�����Ƿ��
template <typename T> bool Queue <T> ::empty() const
{
    return (count == 0) ? true : false;
}

//����
template <typename T> Error_code Queue <T> :: serve ()
{
    if (count)
    {
        delete &entry[front] ;
        front = ((front == maxqueue-1) ? 0 : (front + 1));
        return success;
    }
    else
        return underflow;
}

//��β����һ��Ԫ��
template <typename T> Error_code Queue <T> :: append (const T&item)
{
    if(count >= maxqueue)
        return overflow;
    count++;
    entry [rear] = item;
    rear = ((rear+1) == maxqueue) ? 0 : (rear+1);
    return success;
}

//ȡ��ͷԪ��
template <typename T> Error_code Queue <T> :: retrieve(T&item) const
{
    if (count == 0)
        return underflow;
    item = entry[front];
    return success;
}

class Stu
{
    char Name[20];	//ѧ������
	float Chinese;		//���ĳɼ�
	float Math;		//��ѧ�ɼ�
public:
	float Average(void);	//����ƽ���ɼ�
	float Sum(void);	//�����ܷ�
	void Show(void);	//��ӡ��Ϣ
	void SetStudent(char*,float,float);//Ϊ�������������ɼ�
	void SetName(char *);	//Ϊ����������
	char *GetName(void);	//ȡ��ѧ������
};

float Stu::Average(void){  return (Chinese+Math)/2;}//ƽ���ɼ�
float Stu::Sum(void){    return Chinese+Math;  }//�ܷ�
void Stu::Show(void)	//��ӡ��Ϣ
{   cout<<"Name:  "<<Name<<endl<<"Score:  "<<Chinese<<'\t'<<
   Math<<'\t'<<"average:  "<<Average()<<'\t'<<"Sum:   "<<Sum()<<endl;
  }
void Stu::SetStudent(char *name,float chinese,float math)
{	strcpy(Name,name);	//������
	Chinese=chinese;	//�����ĳɼ�
	Math=math;		//����ѧ�ɼ�
}
char * Stu::GetName(void){	return Name;}//��������


int main()
{
	Queue<Stu> a;
	Stu  p1,p2,p3;

	char* b=new char[10];
	p1.SetStudent("Li qing",98,96);//�����ó�ֵ
	p2.SetStudent("Wang Gang",90,88); //�����ó�ֵ

    a.append(p1);
    a.append(p2);
    a.retrieve(p3);
    cout<<p3.GetName()<<endl;
    a.serve();
    a.retrieve(p3);
    cout<<p3.GetName()<<endl;
}


