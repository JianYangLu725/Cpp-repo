// Created by jason on 2026/10/18.
//
#include<iostream>
using namespace std;

int main() {
    /*
        +   加
        -   减
        *   乘
        /   除（向下取整）
     */
    int a = -5;
    int b= 2;
    cout<<a/b<<endl; // 向下取整往0靠
    a=+6; //此是赋值并未加6！
    cout<<a<<endl;
    a+=6; //a = a + 6;output a = 12(前面a被赋值为6)
    cout<<a<<endl;
    char A = 'A';
    cout<<int(A)<<endl;
    A = A + 1;//字符算术运算
    cout<<A<<" "<<int(A)<<endl;
    cout<<"---------------取余数%---------------"<<endl;
    /*
     % 取余数
     */
    int c = 100;
    int d = 99;
    cout<<c%d<<endl; // 1
    d = -99;
    cout<<c%d<<endl; // 1
    c = -100;
    d = 99;
    cout<<c%d<<endl; // -1
    c=-100;
    d=-99;
    cout<<c%d<<endl; // -1
    // 取余符号与分母符号保持相同

    cout<<"---------------自增 ++ 自减 --  ---------------"<<endl;
    int i = 1;
    int j = 2;
    int x = i++; //先把i赋值给x，再i + = 1；
    int y = ++j;//先执行j+=1，再将j赋值给y；(效率稍高)
    cout<<x<<" "<<y<<endl;
    // i = 2;j = 3
    int z  = (++i)+(j++);
    cout<<z<<endl;
    // i = 3;j = 4
    i--;
    --j;
    cout<<i<<" "<<j<<endl;
    return 0;
}