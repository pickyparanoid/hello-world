#include <iostream>
#include <stdbool.h>
using namespace std;

double add(int n)
{
    double total , mid = (double)1/n;
    for (total = 1; mid >= 0.00001; mid = mid/n)
    {
        total+=mid;
    }
    return total;
}

bool prime(int a)
{
    int n;
    for(n=2;n<=a/2;n++)
    {
        if (a%n == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    char s;
    cin >> s;
    if (isalpha(s))
        cout << "Sorry , please enter a number." << endl;

    int x;
    cin >> x;
    cout << add(x) << endl;

    cout << "100到200间的素数：" << endl;
    for(int i=100;i<=200; i++)
    {
       if(prime(i)==1)
       {
           cout<<i<<"\t";
       }
    }
    return 0;
}
