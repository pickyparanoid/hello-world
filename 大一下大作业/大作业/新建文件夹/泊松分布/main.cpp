#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>
using namespace std;

std::default_random_engine generator;
int possion(double x)
{
  std::poisson_distribution<int> distribution(x);
  int number = distribution(generator);
  cout << number << '\t';
}


int main()
{
    for (int i=0;i<1000;i++)
    {
        possion(0.48);
    }
    return 0;
}
