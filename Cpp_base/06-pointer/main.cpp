//
// Created by jason on 2026/10/19.
//

#include<iostream>
using namespace std;

int main() {
    int a=1;
    int b=2;
    cout<<"address of a:"<<&a<<endl;//取地址
    cout<<"address of b:"<<&b<<endl;

    int* pa=&a;//地址赋值给指针变量
    cout<<pa<<endl;
    cout<<*pa<<endl;//*：解引用，取出pa指向地址存储的值
    cout<<*(&a)<<endl;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(&a)<<endl;//指针指向一个地址，但指针变量也是变量，也有地址，其占用8个字节
    cout<<&a<<endl;
    cout<<&pa<<endl;
    cout << sizeof(int*) << endl;
    cout << sizeof(short*) << endl;
    cout << sizeof(char*) << endl;
    cout << sizeof(long*) << endl;
    cout << sizeof(long long*) << endl;
    cout << sizeof(double*) << endl;
    cout << sizeof(float*) << endl;//64位mac上，指针变量均占用8个字节
    cout<<"-------------------------"<<endl;
    int* p=NULL;
    //cout<<*p<<endl;
    //cout<<&p<<endl;
    p = (int *)0x121412;
    cout << *p << endl;


    return 0;
}