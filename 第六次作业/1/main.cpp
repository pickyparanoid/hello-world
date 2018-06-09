#include <iostream>
using namespace std;
class Myclass
{
public:
    Myclass(int x)
    {
        this->x = x;
    }
    int Getnum()
    {
        return x;
    }
private:
    int x;
};

int main()
{
    Myclass my (10);
    cout << my.Getnum() << endl;
}
