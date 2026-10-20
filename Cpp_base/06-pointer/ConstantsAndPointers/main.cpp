//
// Created by jason on 2026/10/20.
//
#include<iostream>
using namespace std;

int main() {
    //指针常量：该指针是常量，其指向的地址无法修改
    int a=1;
    int b=2;
    int* const p = &a;
    cout<<p<<endl;
   // p = &b;  err:尝试赋值新地址给指针常量 p
    *p = 3; // 指针常量指向地址不可修改，但指向地址存储的值可修改
    cout<<a<<endl;//修改p指向地址的值，相当于同时修改了a的值
    cout<<&a<<endl;
    cout<<*p<<endl;
    cout<<"--------------------------"<<endl;
    //常量指针：指向常量的指针，指针指向的地址存储的值是常量，因此无法通过指针修改该指，但可以改变指针的指向
    int c=1;
    int d=2;
    const int* q = &c;
    //*q = d; err:无法通过指针去修改它指向地址的值
    cout<<&c<<endl;
    cout<<q<<endl;
    q = &d;//可以改变常量指针的指向
    cout<<&d<<endl;
    cout<<q<<endl;

    //常量指针常量：该指针是常量，指针指向地址存储的值也是常量。
    //因此无法修改指针指向，也无法修改指针指向地址存储的值
    int e =1;
    const int* const qp=&e;
   /* qp = &d;
    *qp = d;
    err
    */
    return 0;
}