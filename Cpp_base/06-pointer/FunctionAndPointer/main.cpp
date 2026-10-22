//
// Created by jason on 2026/10/21.
//
#include<iostream>
using namespace std;

//指针函数：返回指针的函数
//等差数列：首项a，公差b；n项
int* getArray(int a,int b,int n) {
    int* ret = new int[n];//动态申请一块存放n*4个字节的内存，并将首地址赋值给ret
    for (int i=0;i<n;i++) {
        ret[i] = a+i*b;
    }
    return ret;
}

//函数指针：指向函数的指针
//定义一个函数指针类型，这表明后续可通过fptr xxx = yyy;来创建一个指向yyy函数的xxx指针变量。yyy函数必须返回void ，且接收变量为(int a,int b,float c,double d,char e);
using fptr = void (*)(int a,int b,float c,double d,char e);

//函数指针数组：存放函数指针的数组，每个元素是一个指向函数的指针变量
using fptrarr = void (*)(int a,int b,float c,double d,char e);

void func1(int a,int b,float c,double d,char e) {
    cout<<"you have called fun1"<<endl;
}
void func2(int a,int b,float c,double d,char e) {
    cout<<"you have called fun2"<<endl;
}
void func3(int a,int b,float c,double d,char e) {
    cout<<"you have called fun3"<<endl;
}
int main() {
    int* res=getArray(1,1,10);
    //注意，虽然ret是局部指针变量，在函数结束后销毁，但函数创建的动态内存还存在，需要注意释放
    for (int i=0;i<10;i++) {
        cout<<res[i]<<" ";
        cout<<*(res+i)<<endl;
        }

    fptr p = func1;
    func1(1,2,3,4,5);
    p = func2;
    func2(1,2,3,4,5);
    p = func3;
    func3(1,2,3,4,5);//通过函数指针类型fptr创建函数指针变量p，p可以被不同的函数地址赋值

    fptrarr q[3] = {func1,func2,func3};


    for (int i=0;i<3;i++) {

        q[i](1,2,3,4,5);
    }
    delete res;
    return 0;
}