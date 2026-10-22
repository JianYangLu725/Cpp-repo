//
// Created by jason on 2026/10/22.
//
#include<iostream>
using namespace std;

//union:内存共享 所有成员共享同一块内存
union Data {
    char a;
    int b;
    double c;

    Data(char a,int b,double c) {
        this->a=a;
        this->b=b;
        this->c=c;
    }
};
int main() {
    Data d('1',2,3.14);
    cout<<sizeof(d)<<endl;//由于共享内存，其输出最后写入的double类型的字节：8
    int x= d.b;//为定义行为
    cout<<x<<endl;


    return 0;
}