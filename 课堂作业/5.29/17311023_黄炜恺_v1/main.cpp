#include <iostream>
#include <math.h>
using namespace std;

class Dot
{
public:
    Dot(double a,double b):x(a),y(b){}
    void display()
    {
        cout << "x= " << x << endl;
        cout << "y= " << y << endl;
    }
    double getx(){return x;}
    double gety(){return y;}
protected:
    double x;
    double y;
};

class Line:public Dot
{
private:
    Dot dot1,dot2;
public:
    Line(double a,double b,double c,double d):Dot((a+c)*0.5,(b+d)*0.5),dot1(a,b),dot2(c,d){}
    double Length()
    {
        double x = pow((dot1.getx() - dot2.getx()),2),y = pow((dot1.gety() - dot2.gety()),2);
        return sqrt(x+y);
    }
    void show()
    {
        cout << "Midpoint coordinates are : " << "(" << x << "," << y << ")" << endl;
    }
};

int main()
{
    double a,b,c,d;
    cout << "X coordinate of Dot1: " << endl;
    cin >>  a ;
    cout << "Y coordinate of Dot1: " << endl;
    cin >>  b ;
    cout << "X coordinate of Dot2: " << endl;
    cin >>  c ;
    cout << "Y coordinate of Dot2: " << endl;
    cin >>  d ;
    Line line(a,b,c,d);
    cout << "Length is :" << line.Length() << endl;
    line.show();
    return 0;
}
