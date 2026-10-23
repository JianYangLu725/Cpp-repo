//
// Created by jason on 2026/10/23.
//
#include<iostream>
using namespace std;
/*
代码区（Code Segment）：主要存储编译后的机器指令。
全局区（Global/Static Storage）：主要存储全局变量、静态变量等。
栈区（Stack）：通常用于管理函数调用及局部变量。
堆区（Heap）：通常用于程序运行期间的动态内存分配。
 */
// 全局变量：静态存储期
int globalA = 100;
int globalB;

void func() {
    // 静态局部变量
    static int staticA = 200;

    // 普通局部变量
    int localA = 300;

    // 动态分配堆区
    int* heapA = new int(400);
     cout<<*heapA<<endl;
    cout << "globalA 地址："
         << &globalA << endl;

    cout << "globalB 地址："
         << &globalB << endl;

    cout << "staticA 地址："
         << &staticA << endl;

    cout << "localA 地址："
         << &localA << endl;

    cout << "heapA 指向的地址："
         << heapA << endl;

    cout << "heapA 指针自己的地址："
         << &heapA << endl;

    delete heapA;
}

int main() {
    func();
    return 0;
}