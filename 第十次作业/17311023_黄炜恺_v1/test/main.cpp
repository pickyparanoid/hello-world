#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    string s;//Ĭ�ϳ�ʼ����һ�����ַ���
    string s1("ssss");//s1������ֵ��ssss���ĸ���
    string s2(s1);//s2��s1�ĸ���
    string s3=s2;//s3��s2�ĸ���
    string s4(10,'c');//��s4��ʼ��
    string s5="hiya";//������ʼ��
    string s6=string(10,'c');//������ʼ��������һ����ʼ���õĶ��󣬿�����s6

    //string s(cp,n)
    char cs[]="12345";
    string s7(cs,3);//�����ַ���cs��ǰ3���ַ���s����

    //string s(s2,pos2)
    string s8="asac";
    string s9(s8,2);//��s2�ĵڶ����ַ���ʼ���������ܳ���s2��size

    //string s(s2,pos2,len2)
    string s10="qweqweqweq";
    string s11(s10,3,4);//s4��s3���±�3��ʼ4���ַ��Ŀ���������s3.size����δ����

    cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl << s5 << endl << s6 << endl << s7<< endl << s8 << endl << s9 << endl << s10 << endl << s11 << endl;

    return 0;
}
