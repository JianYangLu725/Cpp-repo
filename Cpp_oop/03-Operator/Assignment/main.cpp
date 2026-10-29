//
// Created by jason on 2026/10/29.
//
#include<iostream>
#include<string>
using namespace std;
//赋值运算符重载
class People {
private:
    string* name;
    int* age;
    double* tall;
public:
    //成员变量为指针类型，初始化需要申请内存
    People() {
        name = new string;
        age = new int;
        tall = new double;
    }
    //有参构造同样，需要申请内存
    People(string name,int age,double tall) {
        this->name = new string(name);
        this->age = new int(age);
        this->tall = new double(tall);
    }
    ~People() {
        cout<<"执行"<<*this->name<<"析构"<<endl;
        delete name;
        delete age;
        delete tall;
    }
    //赋值运算符重载
    People& operator=(People& op) {
        if (this != &op) {
            *name = *op.name;//将op对象对应的值解引用出来赋值给this对应地址解引用出来的值
            *age = *op.age;//不进行age = op.age;这样的指针直接赋值，有以下问题
            *tall = *op.tall;//1.this指针被覆盖，若没有正确的释放，会造成内存泄露
                            //2.程序结束，this依次析构，op也依次析构，由于地址相同，这会产生重复释放
        }
        return *this;

    }
    void print() {
        cout<<*name<<"年龄为："<<*age<<"岁"<<",身高为："<<*tall<<"cm"<<endl;
    }
};

int main() {
    People p1("jason",23,170.00);
    People p2("cow",25,180.00);
    People p3("skybaby",24,169.00);
    p1=p2=p3;
    p1.print();
    return 0;
}