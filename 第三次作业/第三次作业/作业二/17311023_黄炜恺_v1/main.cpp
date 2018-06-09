#include <iostream>

using namespace std;

int gcd1 (int x , int y )
{
    if (y == 0)
        return x;
    else
        return gcd1 (y , x%y);
}

int gcd2 (int x , int y)
{
    while(x!=y)
    {
        if (x > y)
            x = x-y;
        else
            y = y-x;
    }
    return x;
}

int main()
{
    int a,b;
    cin >> a >> b;
    cout << "gcd1�Ľ��Ϊ" << gcd1 (a,b) << endl;
    cout << "gcd2�Ľ��Ϊ" << gcd2 (a,b) << endl;
    return 0;
}
