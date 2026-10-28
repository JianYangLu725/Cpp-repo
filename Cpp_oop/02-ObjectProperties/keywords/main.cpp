//
// Created by jason on 2026/10/28.
//
#include<iostream>
#include<string>
using namespace std;

class People {
private:
    string name;
    string gender;
    int age;
    mutable double tall;
    inline static int count = 0;
public:
    People(string name,string gender,int age,double tall):name(name),gender(gender),age(age),tall(tall) {
        count++;
    }
    ~People(){}
    static void printCount() {
        cout<<"当前人数："<<count<<endl;
    }
    //定义一个更新年龄的函数，传入形参为age，与成员变量age同名，使用this指针。
    void modifyAge(int age) {
        //this相当于该对象的地址，使用*可解引用
        this->age = age;
        cout<<(*this).age<<endl;
    }
    //定义获取身高的函数，由于只获取身高，可用const关键字修饰函数，以防止其修改对象状态
    void getTall() const {
        //如果在常函数内确实涉及修改对象状态的逻辑，可用mutable修饰成员变量使其能在常函数内可被修改
        tall = tall + 0;
        cout<<name<<"的身高为"<<tall<<endl;
    }
};

int main() {
    People jason("jsaon","mele",23,170.00);
    People::printCount();
    jason.getTall();

    return 0;
}