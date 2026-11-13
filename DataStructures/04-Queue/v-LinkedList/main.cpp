//
// Created by jason on 2026/11/13.
//
#include<iostream>
#include<stdexcept>
#include<utility>

using namespace std;

template<class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(T d):data(std::move(d)),next(nullptr){}
    };
    Node* front = nullptr;//指向队首节点
    Node* rear = nullptr;//指向队尾节点
    int size = 0;
public:
    Queue() = default;
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    void enqueue(T val);//入队
    T dequeue();//出队
    T& getFront();//获取队头
    const T& getFront() const;
    T& getRear();//获取对尾
    const T& getRear() const;

    bool empty() const;
    //bool isFull() const;
    int getSize() const;
    //int getCapacity() const;

    void clear() noexcept;
    void print() const;
    //void printLayout() const;
};

template<class T>
Queue<T>::~Queue() {
    clear();
}

template<class T>
Queue<T>::Queue(const Queue& other) {
    try {
        Node* p = other.front;
        while (p) {
            enqueue(p->data);
            p = p->next;
        }
    }catch (...) {
        clear();
        throw;
    }
}

template<class T>
void Queue<T>::clear() noexcept {
    while (front) {
        Node* tmp = front;
        front = front->next;
        delete tmp;
    }
    rear = nullptr;
    size = 0;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        Queue<T> tmp(other);
        swap(front, tmp.front);
        swap(rear, tmp.rear);
        swap(size, tmp.size);
    }
    return *this;
}

template<class T>
void Queue<T>::enqueue(T val) {
    Node* newNode = new Node(val);
    if (!size) {
        front = newNode;
        rear = newNode;
    }else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

template<class T>
T Queue<T>::dequeue() {
    if (size == 0) {
        throw std::out_of_range("Queue is empty");
    }
    Node* tmp = front;
    front = front->next;
    T val = move(tmp->data);
    if (!front) {
        rear = nullptr;
    }
    delete tmp;
    size--;
    return val;
}

template<class T>
T& Queue<T>::getFront() {
    if (size == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return front->data;
}

template<class T>
const T& Queue<T>::getFront() const {
    if (size == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return front->data;
}

template<class T>
T& Queue<T>::getRear() {
    if (size == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return rear->data;
}

template<class T>
const T& Queue<T>::getRear() const {
    if (size == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return rear->data;
}

template<class T>
bool Queue<T>::empty() const {
    return size == 0;
}

template<class T>
int Queue<T>::getSize() const {
    return size;
}

template<class T>
void Queue<T>::print() const {
    cout<<'[';
    Node* p = front;
    while (p!=rear) {
        cout<<p->data<<"->";
        p = p->next;
    }
    cout<<p->data<<"]"<<endl;

}

int main() {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.print();

    cout << "Front: " << q.getFront() << ", Rear: " << q.getRear() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;

    Queue<int> q2 = q; // 测试拷贝构造
    q2.enqueue(40);
    q2.print();
    return 0;
}