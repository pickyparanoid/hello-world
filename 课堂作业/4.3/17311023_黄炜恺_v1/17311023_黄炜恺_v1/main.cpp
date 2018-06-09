#include <iostream>

using namespace std;

int add(int a, int b)
{
    return a+b;
}

double add (double a , double b)
{
    return a+b;
}

struct plu
{
    double shi , xu;
}x,y;

void add (plu a,plu b)
{
    cout << "result = " ;
    cout << a.shi+b.shi << "+";
    cout << a.xu +b.xu  << "i" << endl;
}

int main()
{
    int i,j;
    double k,l;
    cout << "Enter two integer:\n";
    cin >> i >> j;
    cout << "result = " << add(i,j) << endl;

    cout << "Enter two real numbers:\n";
    cin >> k >> l;
    cout << "result = " << add(k,l) << endl;

    cout << "Enter two imaginary numbers:\n";
    cout << "The real part of the first number is:   ";
    cin >> x.shi;
    cout << "The imaginary part of the second number is:   ";
    cin >> x.xu;
    cout << "The real part of the first number is:   ";
    cin >> y.shi;
    cout << "The imaginary part of the second number is:   ";
    cin >> y.xu;

    add (x,y);
    return 0;
}
