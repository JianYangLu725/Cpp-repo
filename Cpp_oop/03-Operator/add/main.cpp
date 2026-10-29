//
// Created by jason on 2026/10/29.
//
#include<iostream>
using namespace std;

class Complex {
    friend ostream& operator<<(ostream& cout, const Complex &b);
private:
    int real;
    int image;
public:
    Complex():real(0), image(0) {}
    Complex(int real,int image) {
        this->real = real;
        this->image = image;
    }
    ~Complex() {
        cout<<"析构完成"<<endl;
    }
    //成员函数运算符重载
    //定义一个虚数向加/减的运算符重载函数
    Complex operator+(Complex &b) {
        Complex res;
        res.real = this->real + b.real;
        res.image = this->image + b.image;
        return res;
    }
    //前置自增运算符重载。返回Complex& 是为了可以实现连续自增。若返回Complex，则是拷贝构造新对象返回，不是this本身
    Complex& operator++() {
        this->real++;
        return *this;
    }
    //后置自增,返回自增前状态，这里不能返回引用，tmp在函数结束后销毁，返回引用会悬空
    Complex operator++(int) {
        Complex tmp = *this;
        this->real++;
        return tmp;
    }

};
ostream& operator<<(ostream& cout, const Complex &b) {
    cout<<b.real<<"+"<<b.image<<"i";
    return cout;
}
int main() {
    Complex a(1,2);
    Complex b(3,4);
    Complex c = a+b;
    cout<<c<<endl;
    cout<<(a++)<<endl;
    cout<<a<<endl;
    cout<<++(++b)<<endl;
    cout<<b<<endl;
    return 0;
}