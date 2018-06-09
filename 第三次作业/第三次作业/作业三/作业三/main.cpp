#include <iostream>

using namespace std;

void f(int n){
    if(n/10)
        f(n/10);
    cout << n << endl;
}

int main()
{
    int a;
    cin >> a;
    f(a);
    return 0;
}
