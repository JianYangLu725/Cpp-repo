//
// Created by jason on 2026/10/19.
//
#include <iostream>
using namespace std;

//函数声明
//通过函数声明，前面的函数可以调用后面函数来实现，且函数可在main()后实现
int add(int a, int b) ;
void func2(int x);

void func1(int x) {
    //递归终止条件
    if (x<=0) {
        return;
    }
    //打印func1被调用
    cout<<"func1"<<x<<endl;
    //调用func2
    func2(x-1);
}
void func2(int x) {
    //打印func2被调用呢
    cout<<"func2"<<x<<endl;
    //调用func1
    func1(x-1);
}
void swap(int a,int b) {
    cout<<a<<" "<<b<<endl;
    a = a^b;
    b = a^b;
    a = a^b;
    cout<<a<<" "<<b<<endl;
}
void realSwap(int &a,int &b) {
    cout<<a<<" "<<b<<endl;
    a = a^b;
    b = a^b;
    a = a^b;

}

int main() {
    int a = 5;
    int b = 6;
    swap(a, b);//将实参复制给形参，函数结束，形参释放
    //cout<<a<<" "<<b<<endl;

    //通过引用值传递，相当于为实参a，b提供新名字，函数内的操作对a，b产生影响
    realSwap(a, b);
    cout<<a<<" "<<b<<endl;

    func1(9);

    add(1,2);
    return 0;
}
int add(int a, int b) {
    cout<<a<<"+"<<b<<"="<<a+b<<endl;
    return 0;
}