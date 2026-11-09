//
// Created by jason on 2026/11/9.
//
#include<iostream>
#include<stdexcept>
#include<utility>
#include<limits>
using namespace std;

template<class T>
class Stack {
    T* data;
    int size;
    int capacity;
    void expand();
public:
    explicit Stack(int capacity_ = 10);
    ~Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);

    void push(T val);//入栈
    T pop() ;//出栈
    T& top() ;//获取栈顶元素
    const T& top() const;      // 获取栈顶元素（只读，供 const 栈使用）
    bool isEmpty() const;//判空
    int getSize() const;//获取元素个数
    void print() const;//打印栈
};

template<class T>
void Stack<T>::expand() {
    if (capacity > numeric_limits<int>::max() / 2) {
        throw out_of_range("Stack overflow");
    }
    int new_capacity = capacity * 2;
    T* newData = new T[new_capacity];
    try {
        for (int i = 0;i<size;i++) {
            newData[i] = data[i];
        }
    }catch(...) {
        delete[] newData;
        throw;
    }
    delete[] data;
    data = newData;
    capacity = new_capacity;
}

template<class T>
Stack<T>::Stack(int capacity_) {
    if (capacity_ <= 0) {
        throw out_of_range("Stack overflow");
    }
    data = new T[capacity_];
    capacity = capacity_;
    size = 0;

}

template<class T>
Stack<T>::~Stack() {
    delete[] data;
}

template<class T>
Stack<T>::Stack(const Stack& other) {
    data = new T[other.capacity];
    capacity = other.capacity;
    try {
        for (int i = 0;i<other.size;i++) {
            data[i] = other.data[i];
        }
    }catch (...) {
        delete[] data;
        throw;
    }
    size = other.size;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    Stack tmp(other);
    swap(data, tmp.data);
    swap(capacity, tmp.capacity);
    swap(size, tmp.size);
    return *this;
}

template<class T>
void Stack<T>::push(T val)  {
    if (size == capacity) {
        expand();
    }
    data[size] = move(val);
    size++;
}

template<class T>
T Stack<T>::pop() {
    if (size == 0) {
        throw out_of_range("Stack underflow");
    }
    return data[--size];
}

template<class T>
T& Stack<T>::top() {
    if (size == 0) {
        throw out_of_range("Stack underflow");
    }
    return  data[size-1];
}

template<class T>
const T& Stack<T>::top() const{
    return data[size-1];
}

template<class T>
bool Stack<T>::isEmpty() const {
    return size == 0;
}

template<class T>
int Stack<T>::getSize() const {
    return size;
}

template<class T>
void Stack<T>::print() const{
    cout<<"[";
    for (int i = 0;i < size;i++) {
        if (i) {
            cout<<",";
        }
        cout<<data[i];
    }
    cout<<"]";
}


int main() {
    // 1. 入栈并触发扩容
    Stack<int> s(2);
    for (int i = 1; i <= 5; i++) s.push(i);
    std::cout << "入栈 1~5：";
    s.print();
    std::cout << "元素个数：" << s.getSize() << "，栈顶：" << s.top() << std::endl;

    // 2. 出栈
    std::cout << "出栈：" << s.pop() << "，剩余：";
    s.print();

    // 3. 拷贝构造与赋值（含自赋值）
    Stack<int> c(s);
    c.push(100);
    Stack<int> a;
    a = c;
    a = a;
    std::cout << "拷贝 c：";
    c.print();
    std::cout << "赋值 a：";
    a.print();
    std::cout << "原栈 s：";
    s.print();

    // 4. const 栈只能读栈顶
    const Stack<int>& cs = s;
    std::cout << "const 栈顶：" << cs.top() << std::endl;

    // 5. 空栈与非法容量
    Stack<int> e;
    std::cout << "空栈打印：";
    e.print();
    try {
        e.pop();
    } catch (const std::underflow_error& ex) {
        std::cout << "捕获异常：" << ex.what() << std::endl;
    }
    try {
        Stack<int> z(0);
    } catch (const std::invalid_argument& ex) {
        std::cout << "捕获异常：" << ex.what() << std::endl;
    }
    return 0;
}