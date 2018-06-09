#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void EnterNum(double& i)
{
    label:
    while(!(cin >> i))
    {
      cin.clear();
      cin.sync();

      cout<<"ERROR !!! Please enter an nonnegative integer number :";
    }
    int a = i;
    if (a != i || i <= 0 )
    {
        cout<<"ERROR !!! Please enter an nonnegative integer number :";
        goto label;
    }
}

int main()
{
    double c ;
    EnterNum(c);
    cout << c << endl;
    return 0;
}
