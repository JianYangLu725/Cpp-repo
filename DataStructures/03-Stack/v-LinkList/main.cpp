//
// Created by jason on 2026/11/10.
//
#include<iostream>
#include<stdexcept>  //underflow_error
#include<string>
#include<utility> //swap move exchange
using namespace std;

template<class T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(T val):data(std::move(val)),next(nullptr){}
    };
    Node* head = nullptr;
    int size = 0;
public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);

    void push(T val);
    T pop();
    T& top();
    const T& top() const;
    bool isEmpty() const;
    int getSize() const;
    void clear() noexcept;
    void print() const;
};

template<class T>
Stack<T>::Stack():head(nullptr),size(0) {}

template<class T>
Stack<T>::~Stack() {clear();}

//按照other顺序复制，不能依次压入新栈栈顶，顺序反了，因此必须在新栈顶从前往后添加
template<class T>
Stack<T>::Stack(const Stack<T>& other) {
    Node* tail = nullptr;
    Node* p = other.head;
    try {
        while (p) {
            Node* node = new Node(p->data);
            if (!tail) {
                head = node;
            }else {
                tail->next = node;
            }
            p = p->next;
            tail = node;
            size++;
        }
    }catch (...) {
        clear();
        throw;
    }
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        Stack<T> tmp(other);
        swap(head,tmp.head);
        swap(size,tmp.size);
    }
    return *this;
}

template<class T>
void Stack<T>::push(T val) {
    Node* newHead = new Node(std::move(val));
    newHead->next = head;
    head = newHead;
    size++;
}

template<class T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    T topVal = std::move(head->data);
    Node* oldHead = head;//保存原头节点状态
    head = head->next;//更换头节点
    delete oldHead;//释放原头节点内存
    size--;
    return topVal;
}

template<class T>
T& Stack<T>::top() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return head->data;
}

template<class T>
const T& Stack<T>::top() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return head->data;
}

template<class T>
bool Stack<T>::isEmpty() const {
    return head == nullptr;
}

template<class T>
void Stack<T>::clear() noexcept {
    while (head) {
        Node* oleHead = head;
        head = head->next;
        delete oleHead;
    }
    size = 0;
}

template<class T>
int Stack<T>::getSize() const {
    return size;
}

template<class T>
void Stack<T>::print() const {
    std::cout<<"[";
    for (const Node* p = head; p; p = p->next) {
        if (p != head) std::cout<<"->";
        std::cout<<p->data;
    }
    std::cout<<"]"<<std::endl;
}

int main() {
    // 1. 入栈
    Stack<int> s;
    for (int i = 1; i <= 5; i++) s.push(i);
    std::cout << "入栈 1~5（左侧为栈顶）：";
    s.print();
    std::cout << "元素个数：" << s.getSize() << "，栈顶：" << s.top() << std::endl;

    // 2. 出栈
    std::cout << "出栈：" << s.pop() << "，剩余：";
    s.print();

    // 3. 拷贝构造：顺序必须与原栈一致
    Stack<int> c(s);
    c.push(100);
    std::cout << "\n拷贝 c 再入栈 100：";
    c.print();
    std::cout << "原栈 s 不受影响：  ";
    s.print();

    // 4. 拷贝赋值（含自赋值）
    Stack<int> a;
    a.push(-1);
    a = c;
    Stack<int>& ref = a;
    a = ref;
    std::cout << "赋值并自赋值后 a：";
    a.print();

    // 5. 移动构造：整条链表直接转交，c 变为空栈但仍可继续使用
    Stack<int> m = std::move(c);
    std::cout << "\nc 移动给 m 后，m：";
    m.print();
    c.push(42);
    std::cout << "被移动的 c 再入栈 42：";
    c.print();

    // 6. 移动赋值：a 原有的链表被释放，改为接管 m 的
    a = std::move(m);
    std::cout << "m 移动赋值给 a 后，a：";
    a.print();
    std::cout << "m 是否为空：" << (m.isEmpty() ? "是" : "否") << std::endl;

    // 7. const 栈只能读栈顶
    const Stack<int>& cs = s;
    std::cout << "\nconst 栈顶：" << cs.top() << std::endl;

    // 8. 非平凡类型
    Stack<std::string> ss;
    ss.push("alpha");
    ss.push("beta");
    ss.push(ss.top());
    std::cout << "string 栈：";
    ss.print();

    // 9. 拷贝空栈
    Stack<int> e;
    Stack<int> e2(e);
    std::cout << "\n拷贝空栈：";
    e2.print();

    // 10. 清空与空栈异常
    s.clear();
    std::cout << "清空后是否为空：" << (s.isEmpty() ? "是" : "否")
              << "，元素个数：" << s.getSize() << "，打印：";
    s.print();
    try {
        s.pop();
    } catch (const std::underflow_error& ex) {
        std::cout << "捕获异常：" << ex.what() << std::endl;
    }
    return 0;
}