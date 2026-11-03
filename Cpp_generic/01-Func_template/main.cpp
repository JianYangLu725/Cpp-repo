//
// Created by jason on 2026/11/3.
//
#include<iostream>
using namespace std;

int add(int a,int b) {
    cout<<"普通函数"<<endl;
    return a+b;
}
//function template
template<typename T>
T add(T a,T b) {
    cout<<"函数模版"<<endl;
    return a+b;
}

//多参数函数模版
template<typename T1,typename T2,typename T3>
T1 add(T1 a,T2 b,T3 c) {
    cout<<"多参数函数模版"<<endl;
    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    cout<<typeid(c).name()<<endl;
    return a+b+c;
}
int main() {
    cout<<"1.当普通函数与函数模版同名且参数列表相同，编译器比较匹配程度，若普通函数匹配程度更高，优先调用普通函数"<<endl;
    //两个int类型直接传入普通函数，而函数模版需要进行一次类型推倒，因此直接调用普通函数
    int a = 1,b=2;
    int c = add(a,b);
    cout<<c<<endl;

    cout<<"--------------2.显示指定类型，强制调用函数模版-------------"<<endl;
    c = add<int>(a,b);
    cout<<c<<endl;

    cout<<"----------------3.普通函数调用有隐式类型转换---------------"<<endl;
    double aa = 1.0,bb=2.1;
    double cc = add(aa,b);//double类型被普通函数隐式转换为int
    cout<<cc<<endl;
    //普通函数需要两次类型转换，函数模版进行一次类型推倒，因此这里调用函数模版
    cc = add(aa,bb);
    cout<<cc<<endl;

    cout<<"--------4.函数模版没有隐式类型转换-----------"<<endl;
    cc = add(aa,b);//这会调用普通函数，因为普通函数和函数模版都只需一次类型操作，优先调用普通函数。
    //但是如果函数模版会报错，因为aa已经指定T为double，后续b又指定T为int，冲突。
    cout<<cc<<endl;
    //通过显示指定类型，函数模版具备了隐式转换
    cc = add<double>(a,b);
    cout<<cc<<endl;

    cout<<"--------5.多参数模版函数模版----------------"<<endl;
   // cc = add(aa,b,bb);//err:函数模版没有隐式类型转换，T1被aa指定为double,b又指定T1位int，冲突
    cc = add<double>(aa,b,bb);//只需要显示指定T1为double（顺序），此时函数模版就具备隐式转换能力
    //T1 == double;T2 == int;T3 == double;
    cout<<cc<<endl;

    /*关于调用函数模版和普通函数的优先级
     *看匹配程度
     *普通函数发生类型转换的次数
     *函数模版在类型推导后发生类型转换的次数
     *谁的次数越低，匹配程度越高，优先调用
     *相同时优先调用普通函数
     *显示指定是强制调用函数模版
     *
     */
    return 0;
}