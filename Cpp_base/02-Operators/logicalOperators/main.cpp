//
// Created by jason on 2026/10/18.
//
#include <iostream>
using namespace std;

int main() {
    /*
    ==     等于
    !=     不等于
    <      小于
    >      小于
    <=     小于等于
    >=     大于等于
     */
    int a=1;
    int b=2;
    bool c = a==b;
    cout<<c<<endl; //a==b返回了false
    cout<<(a!=b)<<endl;
    /*

    &&    与 有假则假
    ||    或 有真则真
    !     非 真假取反

    判断优先级 || < && < !

*/
    bool d = (1&&0)||1&&0; // 根据判断优先集，等价于(1&&0)||(1&&0) == 0||0 == 0
    bool e = !(1&&0)||1&&0; // 根据判断优先集，等价于(!(1&&0))||(1&&0) == 1||0 == 1
    cout<<boolalpha<<d<<endl;
    cout<<boolalpha<<e<<endl;

    cout<<"---------------- 位与 & ---------------"<<endl;
    // & 1&1==1 ;1&0==0;0&0==0;
    //判断奇偶
    //int x = 5;//    0b101 奇数的末位必为1
              //1   0b001
             //&    0b001
    int x;
    cin>>x;
    if ((x&1)==1) {
        cout<<"x is odd number"<<endl;
    }else {
        cout<<"x is even number"<<endl;
    }

    //获取二进制数的末i位
    int  y = 0b101101;
           //0b001111
    cout<<bitset<8>(y&0b1111)<<endl;

    //将末i位归零 (归零y的后3位)
   int f = 0b111111111111111111111111111111000;
    cout<<bitset<8>(y&f)<<endl;

    //消除末位连续1
    int z = 0b100111;
      //z+1 0b101000
      //&   0b100000;
    cout<<bitset<8>(z&(z+1))<<endl;

    //2的幂判定
    int g = 0b100000000; //对非负整数来说，2 的幂次方的二进制表示一定只有一个 1
    // g-1= 0b011111111;
    //   &= 0b000000000 = 0;
    cout<<((g > 0) && ((g & (g - 1)) == 0))<<endl;
    return 0;
}