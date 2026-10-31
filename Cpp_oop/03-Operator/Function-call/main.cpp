//
// Created by jason on 2026/10/31.
//
#include<iostream>
using namespace std;

//()函数调用运算符
class addPoint {
private:
    int m_x,m_y;
    int calNum = 0;
public:
    addPoint() {m_x = 0;m_y = 0;}
    addPoint(int x,int y):m_x(x),m_y(y){}
    ~addPoint(){}

    //通过初始化对象的函数调用重载，可以保存一些状态。例如calNum。
    int operator() () {
        calNum++;
        return m_x + m_y;
    }
    void printCalNum() const{
        cout<<"执行了"<<calNum<<"次计算"<<endl;
    }
};

int main() {
    addPoint p(1,2);
    for (int i=0;i<10;i++) {
        cout<<p()<<endl;
    }
   p.printCalNum();
    return 0;
}