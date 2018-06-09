#include <iostream>

using namespace std;

class A
{
public:
    void f1(){cout << "f1" << endl;};
protected:
    void f2(){cout << "f2" << endl;}
private:
    char i = 'i';
};

class B:public A
{
public:
    void f3(){cout << "f3" << endl ;};
    char k = 'k';
private:
    char m = 'm';
};

class C:protected B
{
public:
    void f4(){cout << "f4" << endl;};
protected:
    char m = 'm';
private:
    char n = 'n';
};

class D:private C
{
public:
    void f5(){cout << "f5" << endl;};
protected:
    char p = 'p';
private:
    char q = 'q';
};

int main()
{
      A a1;
      B b1;
      C c1;
      D d1;

}
