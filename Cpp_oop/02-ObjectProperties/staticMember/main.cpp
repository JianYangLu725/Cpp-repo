//
// Created by jason on 2026/10/26.
//
#include<iostream>
#include<string>
using namespace std;
/*
 静态成员变量:1.所有该类型对象共享改变量
            2.在类内声明，使用static
            3.类外初始化，加上类名限定作用域
 */
class People {
private:
    string name;
    int age;
    double tall;
public:
    //  初始化列表
    People(string p_name,int p_age,double p_tall):name(p_name),age(p_age),tall(p_tall) {
        count++;
    }
    ~People() {
        cout<<"析构函数成功执行"<<endl;
    }
    inline static int count = 0;;//静态成员变量，需要在类外初始化

    /*
     静态成员函数：
     1.所有对象共享
     3.在不显示传入某种类型的对象形参时，它只能访问静态成员变量。
     2.不依赖具体对象状态，例如该People类中，静态变量count没创建一次People类对象+1
        我们获取该People类的count时，不依赖具体对象状态，可以通过People::getCount();使用
     */
    static int getCount() {
        cout<<"正在调用静态成员函数，输出结果（当前人数）："<<count<<endl;
    }
};

//int People::count = 0;  另一种静态成员变量初始化方法，声明作用域People，当类内仅仅是static int count;

int main() {
    People::getCount();
    People jason("jason",23,170);
    People zoro("zdior",23,172);

    jason.getCount();
    cout<<&(jason.count)<<endl;
    cout<<&(zoro.count)<<endl;
    return 0;
}

