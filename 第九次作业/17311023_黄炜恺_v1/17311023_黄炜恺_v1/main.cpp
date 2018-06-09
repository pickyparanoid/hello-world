#include <iostream>

using namespace std;

class A
{
protected:
    int x;
public:
    A(){x = 1000;}
    inline virtual void p()
    {
        cout << "x= " << x << '\n';
        p2();
    }
    void p2()
    {
        cout << "A::p2()" << endl;
    }
};

class C:public A
{
    int z;
public:
    C(){z = 3000;}
    void p()
    {
        cout << "z= " << z << '\n';
        p2();
    }
    void p2()
    {
        cout << "C::p2()" << endl;
    }
};

int main()
{
    C c;
    A a,*pa = &a;
    pa->p();

    pa = &c;
    pa->p();
    return 0;
}


