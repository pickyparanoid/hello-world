#include <iostream>

using namespace std;

class Sell
    {
    private:
        int num;
        int quantity;
        float price;
        static float sum;
        static int n;
        static float discount ;
    public:
        Sell(int x,int y,float z):num(x),quantity(y),price(z){}
        void total();
        static float average();
        static void display();
	};

float Sell::sum = 0;
int Sell::n = 0;
float Sell::discount = 0.8;


void Sell::total()
{
    if (quantity >= 10)
        sum += quantity * price * discount * 0.98;
    else
        sum += quantity * discount * price;
    n += quantity;
}

float Sell::average()
{
    return (sum/n);
}

void Sell::display()
{
    cout << "the total sales is " << Sell::sum <<endl;
    cout << "The average selling price is " << Sell::average() << endl;
}
int  main(void)
{
    Sell sell[3]=
    {
        Sell(101,5,23.5),
        Sell(102,12,24.56),
        Sell(103,100,21.5)
    };
    int m = 3;
    for (int i=0; i < m ; i++)
    {
        sell[i].total();
    }
    Sell::display();
    return 0;
}
