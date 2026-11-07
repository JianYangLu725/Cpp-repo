//
// Created by jason on 2026/11/7.
//

#include<iostream>
using namespace std;
//单向链表
template<class T>
class LinkedList {
private:
    //链表的一个节点，保存当前节点数据以及指向下一个节点的指针
    struct Node {
        T data;
        Node* next;

        Node(const T& val,Node* p = nullptr): data(val), next(p) {}
    };
public:
    Node* head;
    int size;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

    //插入
    void insert(int index,const T& val);
    void push_front(const T& val);
    void push_back(const T& val);

    //删除
    void erase(int index);
    void pop_front();
    void pop_back();
    void clear();

    //按索引查找
    T& at(int index);
    const T& at(int index) const;

    //按值查找
    int find(const T& val)const;

    int getSize() const;
    bool isEmpty();
    void print();
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& other) :head(nullptr),size(0) {
    //
    Node* last = nullptr;

    try {
        const Node* p = other.head;
        while (p!=nullptr) {
            Node* newNode = new Node(p->data);
            //判断新链表head是否是空节点
            if (head == nullptr) {
                //head指向newNode指向的节点
                head = newNode;
            }else {
                last->next = newNode;
            }
            //第一次head==nullptr后，last和head都指向了同一个节点，该节点是链表的头节点，当时节点的后继节点为空
            //之后通过else{}内将last后继节点改为newNode指向节点，由于last和head都指向了同一个节点，这相当于也将head的后继节点指向newNode指向节点
            //再将last指向节点改为last的后继节点。循环形成链表
            last = newNode;
            p = p->next;
            size++;
        }
    }catch (...) {
        clear();
        throw;
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        LinkedList<T> tmp(other);
        swap(head, tmp.head);
        swap(size, tmp.size);
    }
}

template<class T>
void LinkedList<T>::insert(int index,const T& val) {
    if (index<0||index>size) {
        throw out_of_range("index out of range");
    }
    if (index == 0) {
        head = new Node(val,head);
    }else {
        Node* p = head;
        for (int i = 0;i<index-1;i++) {
            p = p->next;
        }
        Node* newNode = new Node{val,p->next};
        p->next = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::push_front(const T& val) {
    insert(0,val);
}

template<class T>
void LinkedList<T>::push_back(const T& val) {
    insert(size,val);
}

template<class T>
void LinkedList<T>::erase(int index) {
    if (index<0||index>=size) {
        throw out_of_range("index out of range");
    }
    Node* del = nullptr;
    if (index == 0) {
        del = head;
        head = head->next;
        delete del;
    }else {
        Node* p = head;
        for (int i = 0;i<index-1;i++) {
            p = p->next;
        }
        del = p->next;
        p->next = del->next;
        delete del;
    }
    size--;
}

template<class T>
void LinkedList<T>::pop_front() {
    erase(0);
}

template<class T>
void LinkedList<T>::pop_back() {
    erase(size-1);
}

template<class T>
void LinkedList<T>::clear() {
    while (head!=nullptr) {
        Node* del = head;
        head = head->next;
        delete del;
    }
    size = 0;
}

template<class T>
T& LinkedList<T>::at(int index) {
    if (index<0||index>size) {
        throw out_of_range("index out of range");
    }
    Node* p = head;
    for (int i = 0;i<index;i++) {
        p = p->next;
    }
    return p->data;
}

template<class T>
const T& LinkedList<T>::at(int index) const {
    if (index<0||index>size) {
        throw out_of_range("index out of range");
    }
    const Node* p = head;
    for (int i = 0;i<index;i++) {
        p = p->next;
    }
    return p->data;
}

template<class T>
int LinkedList<T>::find(const T& val) const {
    Node* p = head;
    int index = 0;

   while (p!=nullptr) {
       if (p->data == val) {
           return index;
       }
       p = p->next;
       index++;
   }
    return -1;
}

template<class T>
int LinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() {
    return size == 0;
}

template<class T>
void LinkedList<T>::print() {
    Node* p = head;
    while (p!=nullptr) {
        cout<<p->data<<"->";
        p = p->next;
    }
    cout<<"nullptr"<<endl;
}
int main() {
    LinkedList<int> list;

    // 尾部插入
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();

    // 头部插入
    list.push_front(5);
    list.print();

    // 在索引 2 处插入 99
    list.insert(2, 99);
    list.print();

    // 删除索引 1 处的节点
    list.erase(1);
    list.print();

    // 按下标访问和修改
    list.at(1) = 100;
    list.print();

    // 查找
    cout << "100 的下标: " << list.find(100) << endl;

    // 删除头尾节点
    list.pop_front();
    list.pop_back();
    list.print();

    cout << "当前长度: " << list.getSize() << endl;

    // 深拷贝
    LinkedList<int> list2 = list;
    list2.at(0) = 500;

    cout << "原链表: ";
    list.print();

    cout << "拷贝链表: ";
    list2.print();

    // 清空
    list.clear();
    cout << boolalpha << "是否为空: "
         << list.isEmpty() << endl;
/*
    10->20->30->nullptr
    5->10->20->30->nullptr
    5->10->99->20->30->nullptr
    5->99->20->30->nullptr
    5->100->20->30->nullptr
    100 的下标: 1
    100->20->nullptr
    当前长度: 2
    原链表: 100->20->nullptr
    拷贝链表: 500->20->nullptr
    是否为空: true
 */
    return 0;
}