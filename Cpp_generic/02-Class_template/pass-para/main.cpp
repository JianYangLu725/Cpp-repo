
//
// Created by jason on 2026/11/4.
//
#include<iostream>
using namespace std;

template<class pName,class pAge,class pTall>
class People {
    friend void test1(People<string,int,double>& p);

    template<typename T1,typename T2,typename T3>
    friend void test2(People<T1,T2,T3>& p);

    template<typename T>
    friend void test3(T& p) ;
private:
    pName name;
    pAge age;
    pTall tall;
public:
    People(pName Name, pAge Age, pTall Tall) ;
    ~People();
    void printInfo()const;
};

template<class pName,class pAge,class pTall>
People<pName,pAge,pTall>::People(pName Name, pAge Age, pTall Tall) {
    this->name = Name;
    this->age = Age;
    this->tall = Tall;
}
template<class pName,class pAge,class pTall>
People<pName,pAge,pTall>::~People() {
    cout<<"People Destructor"<<endl;
}

template<class T1,class T2,class T3>
void  People<T1,T2,T3>::printInfo()const {
    cout<<name<<endl;cout<<age<<endl;cout<<tall<<endl;
}

//1.直接指定类型
void test1(People<string,int,double>& p) {
    p.printInfo();
}

//2.参数模版化
template<typename T1,typename T2,typename T3>
void test2(People<T1,T2,T3>& p) {
    p.printInfo();
}

//3.类模版化
template<typename T>
void test3(T& p) {
    p.printInfo();
}

template<class T1,class T2,class T3>
class PeopleSon:public People<T1,T2,T3> {
public:
    PeopleSon(T1 name,T2 age,T3 tall);
    ~PeopleSon();
};

// 子类构造函数
template<class T1,class T2,class T3>
PeopleSon<T1,T2,T3>::PeopleSon(T1 name,T2 age,T3 tall)
    : People<T1,T2,T3>(name,age,tall) {
    cout << "PeopleSon Constructor" << endl;
}

// 子类析构函数
template<class T1,class T2,class T3>
PeopleSon<T1,T2,T3>::~PeopleSon() {
    cout << "PeopleSon Destructor" << endl;
}
int main() {
    People<string,int,double> p("jsaon",23,170);
    test1(p);
    test2(p);
    test3(p);
    PeopleSon<string,int,double> pSon("jy",22,199);
    pSon.printInfo();
    return 0;
}