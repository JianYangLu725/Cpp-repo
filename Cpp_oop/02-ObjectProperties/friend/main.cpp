//
// Created by jason on 2026/10/28.
//
#include<iostream>
#include<string>
using namespace std;

/*
 友元friend：
 1.全局函数作为友元
 2.类作为友元
 3.成员函数作为友元
 本质上都是通过friend能够去访问一个类的私有变量
 */
//声明
class People;//声明People类 对应吗20 21行
class PeopleFriend;//声明PeopleFriend类，对应28行
//成员函数作为友元
class People3 {
public:
    void printPub(People* p);
    void printAll(People* p);
};//声明People3类的printAll，对应30行

//1.全局函数作为友元,先声明全局函数，在People
void getAge(People *p);

class People {
    friend class PeopleFriend;//声明PeopleFriend类为友元
    friend void getAge(People* p);//声明全局函数getAge()为友元
    friend void People3::printAll(People* p);//声明People3中的某函数为友元，这里需要在前面先声明People3类
public:
    string name;
    People(string name,int age,double tall):name(name),age(age),tall(tall){}
    ~People(){}
private:
    int age;
    double tall;
};

//2.类作为友元
class PeopleFriend {
public:
    PeopleFriend(){}
    ~PeopleFriend(){}
    void getTall(People* p) {
        cout<<p->tall<<endl;
    }
};


int main() {
    People p("jason",23,170.00);
    People3 p3;
    PeopleFriend pf;
    pf.getTall(&p);
    p3.printAll(&p);
    getAge(&p);
    return 0;
}