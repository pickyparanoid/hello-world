#include <iostream>

using namespace std;

int main()
{
    // c1=,c2='b',c3='c',c4='\101',c5='\x55';
    //cout<<c1<<c2<<c3<<'\n';
    //cout<<"\t\b"<<c4<<'\t'<<c5<<'\n';


    int a=12,n=5;
    a+=a-=a*=a;
    cout<<a<<'\n';
    return 0;
}
