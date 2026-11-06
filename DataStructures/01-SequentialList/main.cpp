//
// Created by jason on 2026/11/5.
//
#include<iostream>
using namespace std;
/*
功能	            函数	                    作用
初始化	        SeqList()	            创建空顺序表
销毁	            ~SeqList()	            释放动态内存
尾部添加	        push_back(value)	    在末尾添加元素
指定位置插入	    insert(index, value)	在指定索引插入元素
指定位置删除	    erase(index)	        删除指定索引的元素
按位置读取	    at(index)	            获取指定位置的元素
按值查找	        find(value)	            查找元素所在位置
获取长度	        getSize()	            返回当前元素数量
判断是否为空	    empty()	                判断是否为空表
清空	            clear()	                删除所有逻辑元素
遍历	            print()	                输出顺序表中的元素
 */

template<class T>
class SeqList {
private:
    T* data;
    int size;
    int capacity;

    void expand();//自动扩容
public:
    SeqList(int n = 10);//构造函数
    ~SeqList();//析构函数
    SeqList(const SeqList& other);//拷贝构造
    SeqList& operator=(const SeqList& other);//拷贝赋值
    void push_back(const T& val);//尾部插入元素
    void insert(int index,const T& val);//指定位置插入元素
    void erase(int index);//删除指定位置元素
    void pop_back();//删除尾部元素
    T& at(int index);//按下标访问
    const T& at(int index) const;//常量对象按下标访问
    int find(const T& val) const;//按值查找下标
    int getSize() const;//获取当前长度
    int getCapacity() const;//获取容量上限
    bool isEmpty() const;//判空
    void clear();//清空
    void print() const;//打印
};

//1.自动扩容
template<class T>
void SeqList<T>::expand() {
    if (capacity > numeric_limits<int>::max() / 2) {
        throw length_error("顺序表容量过大");
    }
    int newCapacity = capacity == 0 ? 1 : capacity * 2;
    T* newData = new T[newCapacity];
    try {
        for (int i = 0;i < size;i++) {
            newData[i] = data[i];
        }
    }catch (...) {
        cout<<"error"<<endl;
        delete[] newData;
        throw;
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

//2.构造函数
template<class T>
SeqList<T>::SeqList(int n ) :data(nullptr),size(0),capacity(0) {
    if (n<0) {
        throw length_error("容量不能为负数！");
    }
     data = new T[n];
    capacity = n;
}

//3.析构函数
template<class T>
SeqList<T>::~SeqList() {
    delete[] data;
}

//4.拷贝构造函数
template<class T>
SeqList<T>::SeqList(const SeqList& other) :data(nullptr), size(0), capacity(other.capacity) {
    if (capacity > 0) {
        data  = new T[other.capacity];
    }
    try {
        for (int i = 0;i < other.size;i++) {
            data[i] = other.data[i];
        }
        size = other.size;
    }catch (...) {
        cout<<"error"<<endl;
        delete[] data;
        throw;
    }
}

//5.拷贝赋值
template<class T>
SeqList<T>& SeqList<T>::operator=(const SeqList& other) {
    if (this != &other) {
        SeqList<T> tmp(other);
        swap(data,tmp.data);
        swap(size,tmp.size);
        swap(capacity,tmp.capacity);
    }
    return *this;
}

//6.指定位置插入元素
template<class T>
void SeqList<T>::insert(int index,const T& val) {
    if (index<0||index>size) {
        throw out_of_range("插入位置不合法");
    }
    /*
     1.如果val是顺序表某元素引用，先创建副本，防止后续移动时val值被前一值覆盖
     2.在扩容前创建副本，扩容创建新的顺序表会释放val原顺序表，是val成为悬空引用
     */
    T tmp = val;

    if (size == capacity) {
        expand();
    }

    //从后先向前移动
    for (int i = size;i>index;i--) {
        data[i] = data[i-1];
    }
    data[index] = tmp;
    size++;
}

//7.尾插
template<class T>
void SeqList<T>::push_back(const T& val) {
    insert(size,val);
}

//8.删除指定元素
template<class T>
void SeqList<T>::erase(int index) {
    if (index<0||index>size) {
        throw out_of_range("删除位置不合法");
    }

    //从前向后移动
    for (int i = index;i<size;i++) {
        data[i] = data[i+1];
    }
    size--;
}

//9.删除尾部元素
template<class T>
void SeqList<T>::pop_back() {
   if (size==0) {
       throw out_of_range("顺序表为空");
   }
    size--;
}

//10.访问指定元素
template<class T>
T& SeqList<T>::at(int index) {
    if (index<0||index>size) {
        throw out_of_range("访问位置不合法");
    }
    return data[index];
}

//11.常量对象访问指定元素
template<class T>
const T& SeqList<T>::at(int index) const {
    if (index<0||index>size) {
        throw out_of_range("访问位置不合法");
    }
    return data[index];
}

//12.按值查找
template<class T>
int SeqList<T>::find(const T& val) const {
    for (int i = 0;i<size;i++) {
        if (data[i]==val) {
            return i;
        }
    }
    return -1;
}

//13.获取元素个数
template<class T>
int SeqList<T>::getSize() const {
    return size;
}

//14.获取容量
template<class T>
int SeqList<T>::getCapacity() const {
    return capacity;
}

//15.判空
template<class T>
bool SeqList<T>::isEmpty() const {
    return size==0;
}

//16.清空
template<class T>
void SeqList<T>::clear() {
    size = 0;
}

//17.打印
template<class T>
void SeqList<T>::print() const {
    cout<<"[";
    for (int i = 0;i<size;i++) {
        cout<<data[i];
        if (i<size-1) {
            cout<<",";
        }
    }
    cout<<"]"<<endl;
}
int main() {
    SeqList<int> list(3);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.print();  // [10, 20, 30]

    list.push_back(40);  // 触发扩容

    cout << "长度: " << list.getSize() << endl;
    cout << "容量: " << list.getCapacity() << endl;

    list.insert(1, 99);
    list.print();  // [10, 99, 20, 30, 40]

    list.erase(2);
    list.print();  // [10, 99, 30, 40]

    cout << "查找99: " << list.find(99) << endl;

    list.at(0) = 100;
    list.print();  // [100, 99, 30, 40]

    return 0;
}