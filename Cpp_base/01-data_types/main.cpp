//
// Created by jason on 2026/10/16.
//
//学习常见的数据类型
#include <iomanip>
#include<iostream>
using namespace std;
#define epsilon 1e-15
int main() {
    /*
整形
short        2字节  00         2^16    (-32768 -> 32767)
int          4字节  0000       2^32    (-2147483648 -> 2147483647)
long         8字节  0000       2^32    (-2147483648 -> 2147483647)
long long    8字节  00000000   2^64    (-2^63 -> 2^63-1)

 [l, r]
*/
    cout<<"---------------整形--------------"<<endl;
    short a = 32767;
    short a_overflow = 32768;
    int b = 32767;
    long c = 32767;
    long long d = 32767;
    cout<<"a = "<<a<<endl;
    cout<<"a_overflow = "<<a_overflow<<endl;
    cout<<"a占用的字节数为："<<sizeof(a)<<endl;
    cout<<"b占用的字节数为："<<sizeof(b)<<endl;
    cout<<"c占用的字节数为："<<sizeof(c)<<endl;
    cout<<"d占用的字节数为："<<sizeof(d)<<endl;

    cout<<"---------------浮点型--------------"<<endl;
    /*
float     4字节 0000  6~7位有效数字
double    8字节 0000  15～16位有效数字

*/
    //浮点型的精度问题
    float e = .1;
    float f = .2;
    float g = e+f;
    cout<<setprecision(10)<<g<<endl;
    if (fabs(g-0.3)<epsilon) {
        cout<<"g与0.3的误差小于"<<epsilon<<endl;
    }else {
        cout<<"g与0.3的误差大于"<<epsilon<<endl;
    }

    cout<<"---------------字符型--------------"<<endl;
    /*
     字符型 char   1字节
     */
    char h = 'x';//对应ASCII 120
    char i = 'y';//对应ASCII 121
    char j = 'z';//对应ASCII 122
    cout<<"h = "<<h<<endl;
    cout<<"x的ASCII值是："<<static_cast<int>(h)<<endl;
    char k = i - h;//'x' - 'h' =121 - 120 = 1
    cout << static_cast<int>(k) << endl;
    //转义字符
    /*
    '\n'	换行
    '\t'	水平制表符
    '\0'	空字符
    '\\'	反斜杠
    '\''	单引号
    '\"'	双引号
     */
    //字符串常量
    char l[] = "learning Cpp is funny";
    char m[] = "and happy";
    cout<<l<<" "<<m<<endl;

    cout<<"---------------布尔型--------------"<<endl;
    // bool 1字节 1==true 0==false
    bool flag1 = true;
    bool flag0 = false;
    cout<<"flag1为"<<flag1<<";"<<" "<<"flag0为"<<flag0<<endl;//output 1 0
    /*常见关系运算符
    运算符	含义	    示例	    结果
    ==	    等于	    5 == 5	true1
    !=  	不等于	5 != 3	true1
    >	    大于	    5 > 10	false0
    <	    小于	    3 < 5	true1
    >=	    大于等于	5 >= 5	true1
    <=	    小于等于	5 <= 3	false0
     */
    /*逻辑运算符
     &&     与       都真为真
     ||     或       有假则假
     ！     非      真假取反
     */



    return 0;
}