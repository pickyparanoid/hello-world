#include <iostream>
using namespace std;

class Stu
{
    public:
        int Average();
        int Sum ();
        void Show();
        void SetStudent(char* x,int y, int z);
        void SetName(char* x);
        char* GetName();
    private:
        char* Name;
        int Chinese;
        int Math;
};

inline int Stu::Average()
{
    return (Chinese+Math)/2;
}

inline int Stu::Sum()
{
    return (Chinese+Math);
}

inline void Stu::Show()
{
    cout << "Name:" << Name <<endl;
    cout << "Chinese:" << Chinese <<endl;
    cout << "Math:" << Math <<endl;
}

inline void Stu::SetStudent(char* x,int y, int z)
{
    Name = x;
    Chinese = y;
    Math = z;
}

inline void Stu::SetName(char* x)
{
    Name = x;
}

inline char* Stu::GetName()
{
    return Name;
}

int main()
{
    Stu p1,p2;
    p1.SetStudent("Li Qing",98,96);
    p2.SetStudent("Wang Gang",90,88);
    p1.Show();
    p2.Show();
    cout << "p1的总成绩:" << p1.Sum() << endl;
    cout << "p2的总成绩:" << p2.Sum() << endl;
    cout << "p1的平均成绩:" << p1.Average() << endl;
    cout << "p2的平均成绩:" << p2.Average() << endl;
    p1.SetName("Zhao si");
    p1.Show();
    cout << "p1的姓名是" << p1.GetName() << endl;
    return 0;
}
