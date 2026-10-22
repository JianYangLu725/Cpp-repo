//
// Created by jason on 2026/10/22.
//
#include<iostream>
#include<string>
using namespace std;

//结构体：相当于创建一个类型
//使用struct创建的对象，其内部的成员变量，成员函数默认是public权限
struct Book {
    string name;
    double price;

    Book(string n,double p) {
        name=n;;
        price=p;
    }

    void show() {
        cout<<"The name of this book is: "<<name<<endl;
        cout<<"The price of this book is: "<<price<<endl;
    }
};

//结构体嵌套
/*
 圆集合
   ｜
    圆
    ｜
----------
｜          ｜
半径          中心
        ------------
        ｜           ｜
        x           y
 */
struct point {
    double x;
    double y;
};
struct circle {
    double r;
    point p;

    double area() {
        constexpr double PI = 3.141592653589793;
        return PI * r * r;
    }
};
struct circles {
    int size ;
    circle* c ;
    circles(int n):size(n),c(new circle[n]){};
    double allArea(){
        double sum = 0;
        for (int i=0;i<size;i++) {
            sum+=(c+i)->area();
        }
        return sum;
    }
};
int main() {
    Book littlePrince("little prince",10);
    littlePrince.show();
    littlePrince.name = "little prince 2";
    littlePrince.price = 15;
    littlePrince.show();

    //创建结构体数组
    Book book[3] = {{"learning C++",10000},{"learning Python",20},{"learning Java",30}};
    for (int i=0;i<3;i++) {
        book[i].show();
    }
    cout<<"----------------------------"<<endl;
    Book* pb = book;
    pb->show();
    (pb+1)->show();
    pb++->show();
    pb->show();
    cout<<sizeof(book)<<endl;


    circles c(3) ;
    for (int i=0;i<3;i++) {
        c.c[i].r =i+1;
        c.c[i].p.x =i+1;
        c.c[i].p.y =i+1;
        c.c[i].area();
    }
 cout<<c.allArea()<<endl;


    return 0;
}