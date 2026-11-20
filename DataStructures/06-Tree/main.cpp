//
// Created by jason on 2026/11/18.
//
#include<iostream>
#include<stdexcept>
#include<queue>
using namespace std;
/*
 tree:一个树节点，包括一个父节点，以及一个孩子节点链表，以及它所存储的数据。
 */

//链表节点：用于构建孩子节点链表。之前学习单向链表时，知道一个链表节点存储1.节点本身数据2.指向下一个节点的指针。
//在要构建的孩子节点链表内。一个链表节点保存1.孩子节点地址（孩子节点本身也是一个树节点）2.指向下一个孩子节点的指针
template<typename T>
struct listNode {
    T data;
    listNode* next;
    explicit listNode(T d):data(d),next(nullptr){}
};

/*
 treeNode：树节点，保存树节点存储的数据，孩子链表的头节点，尾节点以及当前树节点的父节点
 */
template<typename T>
struct treeNode {
    T data;

    listNode<treeNode<T>*>* childHead;
    listNode<treeNode<T>*>* childTail;//使用尾插法往孩子节点链表里添加的孩子节点

    treeNode<T>* parent;//当前树节点的父节点

    //默认构造
    treeNode() {
        data = 0;
        childHead = nullptr;
        childTail = nullptr;
        parent = nullptr;
    }

    //禁止拷贝构造
    //如果树节点已有一个动态分配内存的孩子节点链表，浅拷贝使得两个对象指向同一个孩子节点链表，存在重复释放风险
    treeNode(const treeNode&) = delete;
    treeNode& operator=(const treeNode&) = delete;

    //添加孩子节点
    void addChild(treeNode<T>* child) {
       auto* link = new listNode<treeNode<T>*>(child);

        if (childHead == nullptr) {
            childHead = link;
            childTail = link;
        }else {
            childTail->next = link;
            childTail = link;
        }
        child->parent = this;
    }

    ~treeNode() {
        auto* p = childHead;
        while (p) {
            listNode<treeNode<T>*>* tmp = p->next;
            delete p;
            p = tmp;
        }
    }
};

template<typename T>
class tree {
private:
    treeNode<T>* nodes;
    treeNode<T>* root;
    int capacity;

    //根据id获取可修改的树节点
    treeNode<T>* getNodeMutable(int index) {
        if (index<0||index>capacity) {
            throw out_of_range("index out of range");
        }

        return &nodes[index];
    }

    //判断一个树节点是否当前树
    bool belongsToRoot(treeNode<T>* node) const{
        while (node) {

            if (node == root) {
                return true;
            }

            node = node->parent;
        }

        return false;
    }

    //递归打印树的层次结构
    void printFrom(  treeNode<T>* node,int level) const {
        //递归终止条件
        if (node == nullptr) {
            return;
        }
        //根据level层次打印缩进
        for (int i = 0 ; i < level ;i++) {
            cout<<" ";
        }

        cout<<node->data;
        //获取当前树节点的孩子节点链表头节点
        auto* p = node->childHead;

        //遍历每个孩子节点
        while (p) {
            //递归当前孩子及其所有后代
            //p->data的类型是treeNode<T>*
            printFrom(p->data,level+1);
            p = p->next;
        }
    }

    //深度优先遍历-根遍历
    void dfsFrom(const treeNode<T>* node) const {
        //退出条件
        if (node == nullptr) {
            return;
        }

        cout<<node->data<<" ";
        //获取孩子链表头节点
        auto* p = node->childHead;

        //遍历孩子链表
        while (p) {
            //不断递归往下深入，直到为空，返回上一级进行如下 p = p->next;
            dfsFrom(p->data);
            p = p->next;
        }
    }

    //广度优先遍历-队列先进先出，通过维护一个不断push孩子节点的队列实现广度搜索
    void bfsFrom(const treeNode<T>* node) const {
        if (node == nullptr) {
            return ;
        }

        queue<const treeNode<T>*> q;
        q.push(node);

        while (!q.empty()) {
            auto* current = q.front();
            q.pop();
            cout<<current->data<<" ";
            auto* p = current->childHead;
            //所有孩子节点存储的其树节点地址入队
            while (p) {
                q.push(p->data);
                p = p->next;
            }
        }
    }

    //递归统计节点数量
    int sizeFrom(const treeNode<T>* node)const {
        if (node == nullptr) {
            return 0;
        }

        //当前节点算一次数量级
        int res = 1;
        auto* p = node->childHead;

        while (p) {
            res = res + sizeFrom(p->data);
            p = p->next;
        }

        return res;
    }

    // 递归计算树的高度
    // =================================================
    // 约定：
    // 空树高度 = -1
    // 叶子结点高度 = 0
    // 高度按照最长路径上的边数计算
    int highFrom(const treeNode<T>* node) const {
        if (node == nullptr) {
            return -1;
        }

        //记录每一层的最大高度
        int max = -1;

        auto* p = node->childHead;

        //递归遍历孩子节点
        while (p) {
            //获取当前节点的高度
            int h = highFrom(p->data);

            //判断当前节点高度是否大于这一层孩子节点最大高度
            if (h>max) {
                max = h;
            }

            p = p->next;
        }

        //返回当前节点的高度
        return max+1;
    }

    //递归计算树的度
    // =================================================
    // 树的度 = 所有结点的度中的最大值
    // 结点的度 = 该结点的直接孩子数量
    int degreeFrom(const treeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        //记录当前节点下的最大度
        int maxCount = 0;
        //记录当前节点的度
        int childCount = 0;

        auto* p = node->childHead;
        while (p) {
            //有孩子，+1
            childCount++;

            int degree = degreeFrom(p->data);

            if (degree>maxCount) {
                maxCount = degree;
            }

            p = p->next;
        }
        return childCount > maxCount ? childCount : maxCount;
    }

public:
    tree():tree(1001){}

    explicit tree(const int maxNodes ): capacity(maxNodes) {
        nodes = nullptr;
        root = nullptr;

        if (maxNodes<0) {
            throw out_of_range("maxNodes must be non-negative");
        }

        nodes = new treeNode<T>[maxNodes];
    }

    //禁止浅拷贝
    tree(const tree&) = delete;
    tree& operator=(const tree&) = delete;

    ~tree() {
        delete[] nodes;
    }

    //根据id读取树节点---只读
    const treeNode<T>* getNode(int idx)const {
        if (idx<0||idx>capacity) {
            throw out_of_range("index out of range");
        }
        return &nodes[idx];
    }

    //设置根节点
    void setRoot(int rootIdx) {
        if (rootIdx<0||rootIdx>capacity) {
            throw out_of_range("index out of range");
        }
        root = getNodeMutable(rootIdx);
    }

    //添加孩子节点
    void addChild(int parentIdx, int childIdx) {
        if (parentIdx<0||parentIdx>capacity) {
            throw out_of_range("parent index out of range");
        }
        if (childIdx<0||childIdx>capacity) {
            throw out_of_range("child index out of range");
        }
        if (root == nullptr) {
            throw logic_error("root node is null");
        }
        auto* parentNode = getNodeMutable(parentIdx);
        auto* childNode = getNodeMutable(childIdx);

        if (parentNode == childNode) {
            throw logic_error(
                "Node cannot be its own child"
            );
        }

        //父节点必须属于该树
        if (!belongsToRoot(parentNode)) {
            throw logic_error("Parent must be connected to the root");
        }

        //根节点不能成为孩子
        if (childNode == root) {
            throw logic_error("Root cannot become a child");
        }

        //一个节点只能有一个父节点
        if (childNode->parent != nullptr) {
            throw logic_error("Child already has a parent");
        }

        //调用父节点的添加节点函数
        parentNode->addChild(childNode);
    }

    //修改某个树节点数据
    //直接调用函数assignData(0,'a');这样的话，不用const T& val传参报错
    //原因是T& val这种普通的非const引用无法直接绑定右值。但是const T& val可以绑定
    void assignData(int id, const T& val) {
        getNodeMutable(id)->data = val;
    }

    //输出整棵树
    void Print() const {

        // 从根结点开始，初始层次为 0
        printFrom(root, 0);
    }

    //深度优先遍历
    void DFS() const {

        dfsFrom(root);

        cout << endl;
    }

    // 18. 获取树的结点数量
    int GetSize() const {

        return sizeFrom(root);
    }

    // 19. 获取树的高度
    int GetHeight() const {

        return highFrom(root);
    }

    // 20. 获取树的度
    int GetDegree() const {

        return degreeFrom(root);
    }
};

int main() {
    // 创建一棵最多包含 9 个结点的树
    tree<char> t(9);

    // 设置 nodes[0] 为根结点
    t.setRoot(0);


    // -------------------------
    // 1. 为所有结点赋值
    // -------------------------
    t.assignData(0, 'a');
    t.assignData(1, 'b');
    t.assignData(2, 'c');
    t.assignData(3, 'd');
    t.assignData(4, 'e');
    t.assignData(5, 'f');
    t.assignData(6, 'g');
    t.assignData(7, 'h');
    t.assignData(8, 'i');


    // -------------------------
    // 2. 建立父子关系
    // -------------------------

    // a 的孩子：先 c，后 b
    t.addChild(0, 2);
    t.addChild(0, 1);

    // b 的孩子：d
    t.addChild(1, 3);

    // c 的孩子：先 f，后 e
    t.addChild(2, 5);
    t.addChild(2, 4);

    // d 的孩子：i、h、g
    t.addChild(3, 8);
    t.addChild(3, 7);
    t.addChild(3, 6);


    // -------------------------
    // 3. 打印树结构
    // -------------------------
    cout << "Tree structure:" << endl;

    t.Print();


    // -------------------------
    // 4. DFS 遍历
    // -------------------------
    cout << "DFS: ";

    t.DFS();


    // -------------------------
    // 5. 输出树的基本信息
    // -------------------------
    cout << "Size: "
         << t.GetSize() << endl;

    cout << "Height (edges): "
         << t.GetHeight() << endl;

    cout << "Degree: "
         << t.GetDegree() << endl;


    // main 结束时，tree 自动析构。
    // 析构会释放所有孩子链表及 nodes 数组。

    return 0;
}






















