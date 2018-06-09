#include <iostream>
#include <string>
using namespace std;

class Teacher
{
public:
    Teacher(string nam,int ag,string se,string add,string tele,string tit,string ms);
    void display();
protected:
    string name;
    int age;
    string sex;
    string address;
    string telephone;
    string title;
    string marital_status;
};

Teacher::Teacher(string nam,int ag,string se,string add,string tele,string tit,string ms):
        name(nam),age(ag),sex(se),address(add),telephone(tele),title(tit),marital_status(ms){}

void Teacher::display()
{
    cout << "name:       " << name << endl
         << "age:        " << age  << endl
         << "sex:        " << sex  << endl
         << "address:    " << address  << endl
         << "telephone:  " << telephone  << endl
         << "title:      " << title  << endl;
}

class Cadre
{
public:
    Cadre(string nam,int ag,string se,string add,string tele,string po,string ms);
    void display();
protected:
    string name;
    int age;
    string sex;
    string address;
    string telephone;
    string post;
    string marital_status;
};

Cadre::Cadre(string nam,int ag,string se,string add,string tele,string po,string ms):
        name(nam),age(ag),sex(se),address(add),telephone(tele),post(po),marital_status(ms){}

void Cadre::display()
{
    cout << "name:       " << name << endl
         << "age:        " << age << endl
         << "sex:        " << sex << endl
         << "address:    " << address << endl
         << "telephone:  " << telephone  << endl
         << "post:       " << post << endl;
}

class Teacher_Cadre:public Teacher,public Cadre
{
public:
    Teacher_Cadre(string nam,int ag,string se,string add,string tele,string tit,string po,string ms,int wa);
    void show();
private:
    int wages;
};

Teacher_Cadre::Teacher_Cadre(string nam,int ag,string se,string add,string tele,string tit,string po,string ms,int wa):
        Teacher(nam,ag,se,add,tele,tit,ms),Cadre(nam,ag,se,add,tele,po,ms){wages = wa;}

void Teacher_Cadre::show()
{
    Teacher::display();
    cout << "post:       " << post << endl
         << "wages:      " << wages << endl
         << "marital status: " << Teacher::marital_status << endl;
}

int main()
{
    Teacher_Cadre Thisguy("Finch",64,"male","Baker Street 221B","30624700","professor","chairman","married",15000);
    Thisguy.show();
    return 0;
}
