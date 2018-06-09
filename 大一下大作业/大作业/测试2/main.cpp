#include <iostream>
#include <vector>


using std::cin ;
using std::cout ;
using std::endl;
using std::vector ;


int main()
{
int num;
vector<int> ivec;
do
{
cout<<"please enter some numbers:"<<endl;
while(cin>>num)
ivec.push_back(num);

//增加了两行
cin.clear();
cin.sync();   //或者用cin.ignore();

if(ivec.size()==0)
cout<<"Error!"<<endl;


}while(ivec.size()==0);
}
