//
// Created by jason on 2026/10/20.
//
#include<iostream>
using namespace std;

int main() {
    int a[5] = {1,2,3,4,5};
    int* p=a;//a ：数组a的首地址
   // cout<<a<<endl;
   // cout<<"address p:"<<p<<endl;
   // p++;//移动sizeof(指针类型)个字节
   // cout<<"address p:"<<p<<endl;
   // cout<<"address a[1]:"<<&a[1]<<endl;

    cout<<p+2<<endl;//p+i == &a[i]  or  a[i] == *(p+i)
    cout<<&a[2]<<endl;


    cout<<"------------------------"<<endl;
    double b[3]={1,2,3};
    double* pb=b;
    cout<<pb<<endl;
    cout<<++pb<<endl;//double 占用8个字节

    char c[]="I";
    char d[]="love";
    char e[]="you";

    char* ps[3];//创建一个数组，数组中的元素是指针，指向char*类型
    ps[0]=c;//把c首地址赋值给ps[0]
    ps[1]=d;
    ps[2]=e;

    for(int i=0;i<3;i++) {
        cout<<ps[i]<<endl;//打印c风格字符串时，会自动解析并持续读取知道/0
    }

    int a2d[3][4] = {{1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12}};

    //指针数组：存放指针的数组
    int* pa2d[3] ={a2d[0],a2d[1],a2d[2]};
    /*创建一个存放三个元素的数组，每个元素是一个指针分别指向二维数组的第一、二、三行的首地址

    */
    for(int i=0;i<3;i++) {
        for (int j=0;j<4;j++) {
            cout<<*(pa2d[i]+j)<<" ";
            if ((j+1)%4==0) {
                cout<<endl;
            }
        }
    }
    cout<<*(pa2d[0]+4)<<endl;//二维数组在内存中连续存储，第二行第一个元素紧挨着第一行最后一个元素

    //数组指针：指向数组的指针
    //int (*apa2d)[4] = a2d[0];  err:a2d[0]表示二维数组的第一行的第一个元素首地址，类型是int *
                                //数组指针(*apa2d)[4]需要指向的是int (*)[4]
                                //因此apa2d移动一次会移动16个字节
    int (*apa2d)[4] = a2d;//指向包含四个元素的整行数组
    cout<<apa2d<<endl;
    int x = (*apa2d)[0];//*apa2d,进行了一次解引用，得到第一行数组，再通过下标访问，注意[] 比*优先级要高，因此先*
    cout<<x<<endl;



    return 0;
}