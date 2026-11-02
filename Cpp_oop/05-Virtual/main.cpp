//
// Created by jason on 2026/11/2.
//
#include<iostream>
using namespace std;

//纯虚函数与虚析构
/*虚函数的意义是：允许子类重写父类成员函数的同时，
 *并提供虚指针，指向各自类中的虚函数表，
 *这保证了在函数调用时，不同类型对象通过虚指针指向的自己虚函数表，来达到动态函数调用的目的*/
//虚析构保证多态中析构的正确执行
//纯虚函数：父类仅提供接口定义，子类继承实现具体逻辑。此时父类是抽象类无法实例化。
class People {
public:
    People(){};
    virtual ~People() = 0;
    virtual void printInfo() = 0;
};
People::~People() {
    cout<<"People destructor"<<endl;
};

class yellowPeople:public People {
public:
    yellowPeople(){};
    ~yellowPeople() override{
        cout<<"yellowPeople destructor"<<endl;
    };
    void printInfo()  override{
        cout<<"This is yellowPeople"<<endl;
    }
};
class whitePeople:public People {
    public:
    whitePeople(){};
    ~whitePeople() override{
        cout<<"whitePeople destructor"<<endl;
    }
    void printInfo() override {
        cout<<"This is whitePeople"<<endl;
    }
};
int main() {
    People* p = new yellowPeople();
    p->printInfo();
    whitePeople wp;
    //p指向的动态申请的内存，在堆区，需要手动释放
    delete p;
    p = nullptr;
    p = &wp;
    p->printInfo();
  //wp是局部变量在栈区，不需要delete，程序结束自动销毁
    return 0;
}