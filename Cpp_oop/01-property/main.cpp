//
// Created by jason on 2026/10/24.
//
#include<iostream>
#include<string>
using namespace std;

//面向对象特性：封装，继承，多态

class People {
    //默认权限：private，外部无法访问，无法修改
    string  pGender;
    //判断器：判断性别是否被赋值过。是：true
    bool genderInitialized = false;
public:
    int pAge;//属性（成员变量）
    double pHeight;


    //行为
    void addAge(int age) {
        pAge = age;
    }

    //定义一个性别赋值函数，性别只允许赋值一次，先检测是否赋值过，再检测输入是否正确，若无误，性别赋值，判断器状态变为真
    bool addGender(const string& gender) {
        if (genderInitialized == true) {
            cout<<"you have already been added"<<endl;
            return false;
        }
        else if (gender != "male"&& gender!= " female") {
            cout<<"please enter right gender"<<endl;
            return false;
        }
        pGender = gender;
        genderInitialized = true;
        return true;
    };

    void addHeight(double height) {
        pHeight = height;
    }

};
int main() {
    People jason;
    jason.addAge(23);
    jason.addGender("man");
    jason.addGender("male");
    jason.addGender("female");
    jason.addHeight(170.5);
    cout<<jason.pAge<<endl;
    cout<<jason.pHeight<<endl;
  //  cout<<jason.pGender<<endl;  err:私有成员变量无法访问
    return 0;
}