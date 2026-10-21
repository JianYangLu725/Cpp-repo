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

int main() {
    int* res=getArray(1,1,10);
    //注意，虽然ret是局部指针变量，在函数结束后销毁，但函数创建的动态内存还存在，需要注意释放
    for (int i=0;i<10;i++) {
        cout<<res[i]<<" ";
        cout<<*(res+i)<<endl;
        }
    return 0;
}