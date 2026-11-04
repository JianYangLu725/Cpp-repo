//
// Created by jason on 2026/11/4.
//
#include<iostream>
using namespace std;

//实现一个动态数组类
template<class T>
class dynamicArray {
private:
    T* p;
    int size;
public:
    dynamicArray(int n);
    ~dynamicArray() ;
    //[]运算符重载，用以获取元素
    T& operator[](int i) ;
    //返回只读引用
    //第一个const:修饰返回值
    //第二个const:修饰成员函数
    const T& operator[](int n) const ;
    void upgrade(int i,T value);//更新参数
};
template<class T>
dynamicArray<T>::dynamicArray(int n):size(n) {
    p =new T[size];
}
template<class T>
dynamicArray<T>::~dynamicArray() {
    delete[] p;
}
template<class T>
T& dynamicArray<T>::operator[](int i) {
    return p[i];
}
template<class T>
const T& dynamicArray<T>::operator[](int i) const {
    return p[i];
}
template<class T>
void dynamicArray<T>::upgrade(int i,T value) {
    p[i] = value;
}
int main() {
    dynamicArray<int> arr(100);
    for (int i = 0;i<100;i++) {
        arr[i] = i;
    }
    for (int i = 0;i<100;i++) {
        cout<<arr[i]<<endl;
    }
    const dynamicArray<int>& constArr = arr;
    //类模板中还未指定类型的部分暂不进行创建
    return 0;
}