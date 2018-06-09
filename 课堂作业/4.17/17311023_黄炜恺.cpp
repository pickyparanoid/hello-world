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

//初始化
template <typename T> Queue <T>::Queue()
{
    count = 0;
    front = 0 ;
    rear = 0;
}

//检查队是否空
template <typename T> bool Queue <T> ::empty() const
{
    return (count == 0) ? true : false;
}

//出队
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

//队尾插入一个元素
template <typename T> Error_code Queue <T> :: append (const T&item)
{
    if(count >= maxqueue)
        return overflow;
    count++;
    entry [rear] = item;
    rear = ((rear+1) == maxqueue) ? 0 : (rear+1);
    return success;
}

//取队头元素
template <typename T> Error_code Queue <T> :: retrieve(T&item) const
{
    if (count == 0)
        return underflow;
    item = entry[front];
    return success;
}

class Stu
{
    char Name[20];	//学生姓名
	float Chinese;		//语文成绩
	float Math;		//数学成绩
public:
	float Average(void);	//计算平均成绩
	float Sum(void);	//计算总分
	void Show(void);	//打印信息
	void SetStudent(char*,float,float);//为对象置姓名、成绩
	void SetName(char *);	//为对象置姓名
	char *GetName(void);	//取得学生姓名
};

float Stu::Average(void){  return (Chinese+Math)/2;}//平均成绩
float Stu::Sum(void){    return Chinese+Math;  }//总分
void Stu::Show(void)	//打印信息
{   cout<<"Name:  "<<Name<<endl<<"Score:  "<<Chinese<<'\t'<<
   Math<<'\t'<<"average:  "<<Average()<<'\t'<<"Sum:   "<<Sum()<<endl;
  }
void Stu::SetStudent(char *name,float chinese,float math)
{	strcpy(Name,name);	//置姓名
	Chinese=chinese;	//置语文成绩
	Math=math;		//置数学成绩
}
char * Stu::GetName(void){	return Name;}//返回姓名


int main()
{
	Queue<Stu> a;
	Stu  p1,p2,p3;

	char* b=new char[10];
	p1.SetStudent("Li qing",98,96);//对象置初值
	p2.SetStudent("Wang Gang",90,88); //对象置初值

    a.append(p1);
    a.append(p2);
    a.retrieve(p3);
    cout<<p3.GetName()<<endl;
    a.serve();
    a.retrieve(p3);
    cout<<p3.GetName()<<endl;
}


