//
// Created by jason on 2026/11/21.
//
#include<iostream>
#include <list>
#include<stdexcept>
#include<queue>
using namespace std;

template<typename T>
struct listNode {
    T data;
    listNode* next;
    explicit listNode(T d) : data(d), next(nullptr) {}
};

template<typename T>
struct treeNode {
    T data;//树节点真正存储的数据

    /*
     孩子链表头节点与尾节点（尾节点用来实现尾插法），链表节点里存储的数据类型是treeNode<T>*,
     即树节点的指针，孩子节点本身也是个树节点
     */
    listNode<treeNode<T>*>* childHead;
    listNode<treeNode<T>*>* childTail;

    treeNode<T>* parent;

    //
    treeNode():data(0), childHead(nullptr), childTail(nullptr), parent(nullptr) {}

    //禁止拷贝构造
    treeNode(const treeNode<T>*&) = delete;
    treeNode<T>& operator=(const treeNode<T>*&) = delete;

    void addChild(treeNode<T>* child) {
        auto* p = new listNode<treeNode<T>*>(child);

        if (childHead == nullptr) {
            childHead = p;
            childTail = p;
        }else {
            childTail->next = p;
            childTail = p;
        }
    }

    ~treeNode() {
        auto* p = childHead;
        while (p) {
            auto* tmp = p->next;
            delete p;
            p = tmp;
        }
    }
};

template<typename T>
class tree {
private:
    treeNode<T>* root = nullptr;
    treeNode<T>* nodes = nullptr;

    int capacity;

    treeNode<T>* getNodeMutable(int idx);
    bool belongsToRoot(treeNode<T>* node) const;//判断节点是否属于该树
    void printFrom(treeNode<T>* node,int level) const;//递归打印树
    void dfsFrom(const treeNode<T>* node) const;//深度优先遍历
    void bfsFrom(const treeNode<T>* node) const;//广度优先遍历
    int sizeFrom(const treeNode<T>* node)const;//递归统计节点数量
    // 递归计算树的高度
    // 约定：
    // 空树高度 = -1
    // 叶子结点高度 = 0
    // 高度按照最长路径上的边数计算
    int highFrom(const treeNode<T>* node) const;
    //递归计算树的度
    // 树的度 = 所有结点的度中的最大值
    // 结点的度 = 该结点的直接孩子数量
    int degreeFrom(const treeNode<T>* node) const;

public:
    tree():tree(1001){};
    //有参构造函数
    explicit tree(const int maxCapacity) {
        if (maxCapacity < 0) {
            throw std::invalid_argument("maxCapacity cannot be less than 0");
        }
        nodes = new treeNode<T>[maxCapacity];
        capacity = maxCapacity;
    }

    //禁止拷贝狗仔
    tree(const tree&) = delete;
    tree& operator=(const tree&) = delete;

    ~tree() {
        delete[] nodes;
    }
};

template<typename T>
treeNode<T>* tree<T>::getNodeMutable(int idx) {
    if (idx < 0 || idx >= capacity) {
        throw std::out_of_range("idx out of range");
    }
    return &nodes[idx];
}

template<typename T>
bool tree<T>::belongsToRoot(treeNode<T>* node) const {
    while (node) {
        if (node == root) {
            return true;
        }

        node = node->parent;
    }
    return false;
}

template<typename T>
void tree<T>::printFrom(treeNode<T>* node,int level)const {
    if (node == nullptr) {
        return;
    }
    for (int i = 0;i<level;i++) {
        cout<<" ";
    }
    cout<<node->data<<'\n';
    auto* p = node->childHead;
    while (p) {
        printFrom(p->data,level+1);
        p = p->next;
    }
}

template<typename T>
void tree<T>::dfsFrom(const treeNode<T>* node)const {
    if (node == nullptr) {
        return;
    }

    cout<<node->data<<" ";
    auto* p = node->childHead;
    while (p) {
        printFrom(p->data);
        p = p->next;
    }
}

template<typename T>
void tree<T>::bfsFrom(const treeNode<T>* node) const {
    if (node == nullptr) {
        return;
    }
    queue<treeNode<T>*> q;
    q.push(node);

    while (!q.empty()) {
        cout<<q.front()->data<" ";
        auto* p = q.front()->childHead;;
        q.pop();
        while (p) {
            q.push(p);
            p = p->next;
        }
    }
}

template<typename T>
int tree<T>::sizeFrom(const treeNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    int res = 1;
    auto* p = node->childHead;
    while (p) {
        res = res + sizeFrom(p->data);
        p = p->next;
    }
    return res;
}

template<typename T>
int tree<T>::highFrom(const treeNode<T>* node) const {
    if (node == nullptr) {
        return -1;
    }

    int max = -1;
    auto* p = node->childHead;

    while (p) {
        int h = highFrom(p->data);
        if (h > max) {
            max = h;
        }
    }
    return max+1;
}

template<typename T>
int tree<T>::degreeFrom(const treeNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }

    int currentCount = 0;
    int maxCount = 0;

    auto* p = node->childHead;

    while (p) {
        currentCount++;
        int degree = degreeFrom(p->data);
        if (degree > maxCount) {
            maxCount = degree;
        }
        p = p->next;
    }
    return currentCount > maxCount ? currentCount: maxCount;
}
























int main() {


    return 0;
}
