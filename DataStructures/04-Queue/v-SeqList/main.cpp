//
// Created by jason on 2026/11/11.
//
#include<iostream>
#include<limits>
#include<string>
#include<stdexcept>
#include<utility>
using namespace std;

//顺序表实现循环队列
/*
 入队写到rear，出队从front取，rear和front都只玩往后走，但rear+1达到capacity，回到0开始计数
 idx = (idx + 1) % capacity
 由于循环关系，当队空或队满时都有rear == front
 我们使用size判断是否要扩容
 队空 size == 0 ； 队满 size == capacity

 */
template<class T>
class Queue {
        T* data;//指向该顺序表
        int front = 0;//出队元素下标
        int rear = 0;//入队元素下表
        int size = 0;//当前元素个数
        int capacity = 0;//顺序表容量

        static constexpr int DEFAULT_CAPACITY = 10;
        static constexpr int MAX_CAP = std::numeric_limits<int>::max();

        void resize();//扩容
public:
        Queue(int capacity_ = DEFAULT_CAPACITY);
        ~Queue();
        Queue(const Queue& other);
        Queue& operator=(const Queue& other);
        Queue( Queue&& other) noexcept;//接收右值，直接接管,other对象释放
        Queue& operator=(Queue&& other) noexcept;
        void swap(Queue& other) noexcept;;

        void enqueue(T val);//入队
        T dequeue();//出队
        T& getFront();//获取队头
        const T& getFront() const;
        T& getRear();//获取对尾
        const T& getRear() const;

        bool empty() const;
        bool isFull() const;
        int getSize() const;
        int getCapacity() const;

        void clear() noexcept;
        void print() const;
        void printLayout() const;
};

template<class T>
Queue<T>::Queue(int capacity_) {
    if (capacity_ <= 0||capacity_ > MAX_CAP) {
        throw invalid_argument("invalid capacity");
    }
    capacity = capacity_;
    data = new T[capacity];
}

template<class T>
Queue<T>::~Queue(){delete[] data;}

template<class T>
void Queue<T>::resize() {
    if (capacity == MAX_CAP) {
        throw invalid_argument("capacity is too large");
    }
    int newCapacity;
    if (capacity == 0) {
        newCapacity = DEFAULT_CAPACITY;
    }else {
        newCapacity = (capacity<MAX_CAP/2) ? capacity*2 : MAX_CAP;
    }

    T* newData = new T[newCapacity];
    //从front开始复制，不从0开始复制，原因是队列可能开始了循环
    try {
        for (int i = 0,idx = front;i < size;i++,idx = (idx + 1) % capacity) {
            newData[i] = move(data[idx]);
        }
    }catch (...) {
        delete[] newData;
        throw;
    }

    delete[] data;
    capacity = newCapacity;
    data = newData;
    front = 0;
    rear = size;
}

template<class T>
Queue<T>::Queue(const Queue& other) {
    data = new T[other.capacity];
    capacity = other.capacity;
    try {
        for (int i = 0,idx = front;i < size;i++,idx = (idx + 1) % capacity) {
            data[i] = other.data[idx];
        }
    }catch (...) {
        delete[] data;
        throw;
    }
    size = other.size;
    rear = size;
}

template<class T>
void Queue<T>::swap(Queue& other) noexcept {
    std::swap(data,other.data);
    std::swap(capacity,other.capacity);
    std::swap(front,other.front);
    std::swap(rear,other.rear);
    std::swap(size,other.size);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        Queue<T> tmp(other);
        swap(tmp);
    }
    return *this;
}

template<class T>
Queue<T>::Queue(Queue&& other) noexcept {
    data = exchange(other.data,nullptr);
    front = exchange(other.front,0);
    rear = exchange(other.rear,0);
    size = exchange(other.size,0);
    capacity = exchange(other.capacity,0);
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        Queue<T> tmp(move(other));
        swap(tmp);
    }
    return *this;
}

template<class T>
void Queue<T>::enqueue(T val) {
    if (size == capacity) {
        resize();
    }
    data[rear] = move(val);
    rear = (rear + 1) % capacity;
    size++;
}

template<class T>
T Queue<T>::dequeue() {
    if (size == 0) {
        throw std::underflow_error("Queue underflow");
    }
    T val = move(data[front]);//省去一次拷贝
    front = (front + 1) % capacity;
    size--;
    return val;
}

template<class T>
T& Queue<T>::getFront() {
    if (size == 0) {
        throw std::underflow_error("Queue underflow");
    }
    return data[front];
}

template<class T>
const T& Queue<T>::getFront() const {
    if (size == 0) {
        throw std::underflow_error("Queue underflow");
    }
    return data[front];
}

template<class T>
T& Queue<T>::getRear() {
    if (size == 0) {
        throw std::underflow_error("Queue underflow");
    }
    return data[rear == 0 ? capacity - 1 : rear - 1];
}

template<class T>
const T& Queue<T>::getRear() const {
    if (size == 0) {
        throw std::underflow_error("Queue underflow");
    }
    return data[rear == capacity ? capacity - 1 : rear - 1];
}

template<class T>
bool Queue<T>::empty() const {
    return size == 0;
}

template<class T>
bool Queue<T>::isFull() const {
    return size == capacity;
}

template<class T>
int Queue<T>::getSize() const {
    return size;
}

template<class T>
int Queue<T>::getCapacity() const {
    return capacity;
}

template<class T>
void Queue<T>::clear() noexcept {
    size = 0;
    front = 0;
    rear = 0;
}

//按照从front下标开始打印
template<class T>
void Queue<T>::print() const {
    cout<<'[';
    for (int i = 0,idx = front;i<size;i++,idx = (idx + 1)%capacity) {
        if (i == size - 1) {
            cout << data[i];
        }else {
            cout<<data[idx]<<",";
        }
    }
    cout<<']'<<endl;
}

//按照0下标开始打印
template<class T>
void Queue<T>::printLayout() const {
    std::cout << "  data = [";
    for (int j = 0; j < capacity; ++j) {
        int offset = (j >= front) ? j - front : j + (capacity - front);   // j 在队列中排第几
        if (j > 0) std::cout << ' ';
        if (offset < size) {
            std::cout << data[j];
        } else {
            std::cout << '_';
        }
    }
    std::cout << "]  front=" << front << " rear=" << rear << " size=" << size << std::endl;
}

int main() {
    // 1. 入队直到队满：rear 绕回 0，与 front 重合
    Queue<int> q(4);
    for (int i = 1; i <= 4; i++) q.enqueue(i);
    std::cout << "入队 1~4（左侧为队头）：";
    q.print();
    q.printLayout();

    // 2. 出队两个，再入队两个：新元素写到数组开头空出的位置
    std::cout << "\n出队：" << q.dequeue();
    std::cout << "，出队：" << q.dequeue() << std::endl;
    q.enqueue(5);
    q.enqueue(6);
    std::cout << "再入队 5、6：";
    q.print();
    q.printLayout();
    std::cout << "队头：" << q.getFront() << "，队尾：" << q.getRear()
              << "，元素个数：" << q.getSize() << std::endl;

    // 3. 绕回状态下再入队，触发扩容：按逻辑顺序重排，front 回到 0
    q.enqueue(7);
    std::cout << "\n入队 7（触发扩容）：";
    q.print();
    q.printLayout();

    // 4. 拷贝构造与拷贝赋值（含自赋值）
    Queue<int> c(q);
    c.enqueue(100);
    std::cout << "\n拷贝 c 再入队 100：";
    c.print();
    std::cout << "原队列 q 不受影响： ";
    q.print();
    Queue<int> a;
    a.enqueue(-1);
    a = c;
    Queue<int>& ref = a;
    a = ref;
    std::cout << "赋值并自赋值后 a：  ";
    a.print();

    // 5. 移动：c 的数组直接转交给 m，c 变为空队列但仍可继续使用
    Queue<int> m = std::move(c);
    std::cout << "\nc 移动给 m 后，m：";
    m.print();
    c.enqueue(42);
    std::cout << "被移动的 c 再入队 42：";
    c.print();

    // 6. 非平凡类型：队满时入队自身的队头元素（参数按值传递，扩容后不会悬空）
    Queue<std::string> sq(2);
    sq.enqueue("alpha");
    sq.enqueue("beta");
    sq.enqueue(sq.getFront());
    std::cout << "\nstring 队列：";
    sq.print();

    // 7. 清空与异常
    q.clear();
    std::cout << "\n清空后是否为空：" << (q.empty() ? "是" : "否")
              << "，元素个数：" << q.getSize() << "，打印：";
    q.print();
    try {
        q.dequeue();
    } catch (const std::underflow_error& ex) {
        std::cout << "捕获异常：" << ex.what() << std::endl;
    }
    try {
        Queue<int> z(0);
    } catch (const std::invalid_argument& ex) {
        std::cout << "捕获异常：" << ex.what() << std::endl;
    }


    return 0;
}