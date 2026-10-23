//
// Created by jason on 2026/10/23.
//
#include<iostream>
using namespace std;
//函数的指针传递和指针引用传递
//指针值传递
void allocMemory1(int size,int* p) {
    p = new int[size];//为形参p动态分配一块存放size个元素的数组，指向首地址
}
void test1() {
    int* ptr = nullptr;
    //allocMemory1(10,ptr);//函数形参传递，相当于拷贝一份ptr，函数结束，局部变量ptr释放;
                            //  而且存在内存泄露，由于函数内部指向动态数组的ptr在函数结束后销毁，该堆区的内存已无法正常释放
    cout<<&ptr<<endl;//输出依旧是nullptr的ptr
}


void allocMemory2(int size,int*& p) {
    p = new int[size];//为形参p动态分配一块存放size个元素的数组，指向首地址
}
void test2() {
    int* ptr = nullptr;
    allocMemory2(10,ptr);//函数形参引用传递，相当于ptr
    cout<<&ptr<<endl;
}

int main() {
    //相当于变量的变名，改b值，相当于改a值
    int a=1;
    int& b = a;
    b=0;
    cout<<a<<endl;
    //引用特性：必须初始化，初始化后其所代表的变量无法修改(引用相当于指针常量)
    int x=1,y=2;
    int& z = x;
    z=y;//注意，z已经代表x，此处，相当于是把y的值赋值给z，相当于赋值给x。
    cout<<x<<' '<<y<<" "<<z<<endl;
    cout<<"----------------------------"<<endl;
    test1();

    test2();
    return 0;
}