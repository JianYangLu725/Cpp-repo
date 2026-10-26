//
// Created by jason on 2026/10/25.
//
#include<iostream>
#include<string>
using namespace std;

/*
 构造函数           classname(){}
 析构函数           ~classname(){}
 拷贝构造函数         通过已有类型的对象，拷贝构造一个同类型的新对象
 */

class People{
private:
    int age;
    string name;
    double tall;
public:
    //constructor
    People() {
       cout<<"default constructor invocation completed"<<endl;
    }
    //Parameterized constructor
    People(int age, string name,double tall) {
        this->age=age;
        this->name=name;
        this->tall=tall;
        cout<<"Parameterized constructor invocation completed"<<endl;
    }
    //Destructor
    ~People() {
        cout<<"destructor invocation completed"<<endl;
    }
    //Copy constructor
    /*
     拷贝构造函数的三个调用时机
     1.用已创建的对象来初始化一个同类型对象
     2.作为函数的形参传递（值传递）
     3.作为函数的返回值
     */
    People(const People& p) {
        cout<<"copy constructor invocation completed"<<endl;
    }

    void modifyAge(int newAge) {
        age = newAge;
    }
    void modifyName(string newName) {
        name=newName;
    }
    void modifyTall(double newTall) {
        tall=newTall;
    }

};

People modifyProperty(int age,string name,double tall, People& p) {
    p.modifyAge(age);
    p.modifyName(name);
    p.modifyTall(tall);
    return p;//作为函数的返回值，调用拷贝构造函数
}
//注意一种情况:如果People p；在函数内部创建，p是一个局部变量作为返回值，按理说会进行拷贝构造
//但是编译器在执行到类似People jason = funcexample（）；函数返回在内部创建的局部变量p
//会执行NVRO优化，会直接在对象jason的位置创建p，省去拷贝构造。

int main() {
    People jason;
    People tq(23,"zara",172.00);
    jason = modifyProperty(23,"zara",172.00,tq);//拷贝赋值
    People jason2 = jason;
  //  People p(); // 这是函数声明，不是创建对象，因此不会出发构造/析构
    People p{};
    return 0;
}