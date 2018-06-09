#include <iostream>

using namespace std;

int prime(int x)
{
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)
        return 0;
    }
    return 1;
}

int gotbaha(int y)
{
    for(int i=y;i>=y/2;i--)
    {
        if (prime(i))
        {
            int j;
            j=y-i;
            if(prime(j))
                cout << y << " = " << i  << " + " << j;
                return 0;
        }
    }
    return 1;
}

int main()
{
    int a;
    cout << "Enter a number:" << endl;
    cin >> a;
    if (a%2==1 || a<6)
    {
        cout << "Please Enter a Positive Odd Number" << endl;
        return 0;
    }
    if (gotbaha(a))
        cout << "Something terrible has happened..." << endl;

    return 0;
}
