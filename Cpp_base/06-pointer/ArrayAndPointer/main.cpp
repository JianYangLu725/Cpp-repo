//
// Created by jason on 2026/10/20.
//
#include<iostream>
using namespace std;

int main() {
    int a[5] = {1,2,3,4,5};
    int* p=a;//a ：数组a的首地址
   // cout<<a<<endl;
   // cout<<"address p:"<<p<<endl;
   // p++;//移动sizeof(指针类型)个字节
   // cout<<"address p:"<<p<<endl;
   // cout<<"address a[1]:"<<&a[1]<<endl;

    cout<<p+2<<endl;//p+i == &a[i]  or  a[i] == *(p+i)
    cout<<&a[2]<<endl;


    cout<<"------------------------"<<endl;
    double b[3]={1,2,3};
    double* pb=b;
    cout<<pb<<endl;
    cout<<++pb<<endl;//double 占用8个字节
    return 0;
}