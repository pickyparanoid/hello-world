#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n,float s):num(n),score(s){}
    void change (int n ,float s){num = n;score = s;}
    void display(){cout << num << "  " << score << endl;}
private:
    int num;
    float score;
};

void fun(Student& t,int x,float y)
{
    t.change(x,y);
    t.display();
}

int main()
{
    Student stud (101,78.5);
    stud.display();
    stud.change(101,80.5);
    stud.display();
    fun(stud,54,153.5);
    return 0;
}
