#include <iostream>
#include <string.h>

using namespace std;

const int maxqueue = 10;
enum Error_code{success,underflow,overflow};

template <typename  T> class Extended_queue {
 public:
   Extended_queue();
  bool empty() const;
  Error_code serve();
  Error_code append(const T &item);
  Error_code retrieve(T &item) const;

  bool full() const;
  int size() const;
  void clear();
  Error_code serve_and_retrieve(T&item);

 protected:
  int count;
  int front;
  int rear;
  T entry[maxqueue];
};

template <typename T>
bool Extended_queue<T>::full()const
{
    return (count == maxqueue) ? true : false;
}

template <typename T>
int Extended_queue<T>::size()const
{
    return count;
}

template <typename T>
void Extended_queue<T>::clear()
{
    for(int i=front ; i < front+count ; i++)
        delete &entry[i];
    count = 0;
    front = 0 ;
    rear = 0;
}

template <typename T>
Error_code Extended_queue<T>::serve_and_retrieve(T&item)
{
    if (count == 0)
    return underflow;
    else
    {
        item = entry[front];
        delete &entry[front];
        return success;
    }
}

//��ʼ��
template <typename T> Extended_queue <T>::Extended_queue()
{
    count = 0;
    front = 0 ;
    rear = 0;
}

//�����Ƿ��
template <typename T> bool Extended_queue <T> ::empty() const
{
    return (count == 0) ? true : false;
}

//����
template <typename T> Error_code Extended_queue <T> :: serve ()
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
template <typename T> Error_code Extended_queue <T> :: append (const T&item)
{
    if(count >= maxqueue)
        return overflow;
    count++;
    entry [rear] = item;
    rear = ((rear+1) == maxqueue) ? 0 : (rear+1);
    return success;
}

//ȡ��ͷԪ��
template <typename T> Error_code Extended_queue <T> :: retrieve(T&item) const
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
	Extended_queue<int> q;
	q.append(1);
	q.append(2);
	q.append(3);
	cout << q.full() << endl;
	cout << q.size() << endl;

	int tmp = 0;
	q.serve_and_retrieve(tmp);
	cout << tmp << endl;
	tmp = 0;
	q.clear();
	q.serve_and_retrieve(tmp);
	cout << tmp << endl;
}


