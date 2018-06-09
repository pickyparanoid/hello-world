#include <iostream>
#include<math.h>
using namespace std;

int jie(int n)
    {
        int sum = 1;
        if(n == 1 || n == 0)
            return 1;
        else
            sum =n * jie(n - 1);
        return sum;
    }

int main()
{
    int x,n;
    double amount=0;
    cout << "Input a Number:" << endl;
    cin>>x;

    for(n=0;pow(x,2*n)/jie(2*n)>=1e-5;n++)
    {
        if (n%2==0)
            amount+=pow(x,2*n)/jie(2*n);
        else
            amount-=pow(x,2*n)/jie(2*n);
    }

    cout<<"result="<<amount;
    return 0;
}
