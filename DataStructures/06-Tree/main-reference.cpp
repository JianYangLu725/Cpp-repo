//
// Created by jason on 2026/11/20.
//

#include <iostream>
#include <stdexcept>
using namespace std;


// ====================================================
// 一、单链表结点 ListNode
// 作用：存储一个孩子结点的地址，并连接下一个链表结点
// ====================================================

template<typename T>
struct ListNode {
    T data;             // 链表结点保存的数据
    ListNode* next;     // 指向下一个链表结点

    // 构造函数：初始化数据，并将 next 置为空
    explicit ListNode(T value)
        : data(value), next(nullptr) {}
};


// ====================================================
// 二、树结点 TreeNode
// 作用：保存树结点的数据、孩子链表以及父结点地址
// ====================================================

template<typename T>
struct TreeNode {
    T data;     // 当前树结点存储的数据

    // 指向孩子链表的第一个链表结点
    ListNode<TreeNode<T>*>* childrenHead;

    // 指向孩子链表的最后一个链表结点
    // 用于实现 O(1) 的尾插法
    ListNode<TreeNode<T>*>* childrenTail;

    // 指向当前树结点的父结点
    // 根结点的 parent 为 nullptr
    TreeNode<T>* parent;


    // -------------------------
    // 1. 默认构造函数
    // -------------------------
    TreeNode()
        : data(T()),
          childrenHead(nullptr),
          childrenTail(nullptr),
          parent(nullptr) {
    }


    // -------------------------
    // 2. 禁止默认拷贝
    // -------------------------
    // 因为当前结点拥有动态分配的孩子链表，
    // 如果直接浅拷贝，会让两个对象指向同一条链表。
    // 析构时可能发生重复释放。
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;


    // -------------------------
    // 3. 添加孩子结点（尾插法）
    // -------------------------
    // child 是指向真正 TreeNode 的指针。
    // 注意：这里不会创建新的 TreeNode，
    // 而是创建一个 ListNode 保存 child 的地址。
    //
    // 父子关系的合法性由 Tree::AddChild 检查。
    void AddChild(TreeNode<T>* child) {

        // 创建新的链表结点
        // link->data = child
        // link->next = nullptr
        auto* link =
            new ListNode<TreeNode<T>*>(child);

        // 情况一：孩子链表为空
        if (childrenHead == nullptr) {

            // 新结点既是头结点，也是尾结点
            childrenHead = link;
            childrenTail = link;
        }
        else {

            // 情况二：孩子链表不为空

            // 原尾结点连接新结点
            childrenTail->next = link;

            // 更新尾指针
            childrenTail = link;
        }

        // 建立反向的父子关系
        // 使孩子能够找到父结点
        child->parent = this;
    }


    // -------------------------
    // 4. 析构函数
    // -------------------------
    // 负责释放当前树结点的孩子链表。
    //
    // 只删除 ListNode，不删除 ListNode::data
    // 指向的 TreeNode。
    //
    // 因为所有 TreeNode 统一保存在 nodes 数组中，
    // 由 Tree 的析构函数负责释放。
    ~TreeNode() {

        auto* p = childrenHead;

        while (p != nullptr) {

            // 保存下一个链表结点的地址
            // 必须在 delete p 之前保存
            auto* nextNode = p->next;

            // 释放当前链表结点
            delete p;

            // 移动到下一个链表结点
            p = nextNode;
        }
    }
};


// ====================================================
// 三、普通树 Tree
// 作用：统一管理所有树结点及父子关系
// ====================================================

template<typename T>
class Tree {

private:

    // 指向动态数组的第一个树结点
    // 所有 TreeNode 对象都保存在这个数组中
    TreeNode<T>* nodes;

    // 指向根结点
    // root 指向 nodes 数组中的某个元素
    TreeNode<T>* root;

    // nodes 数组的容量
    int capacity;


    // =================================================
    // 1. 根据 ID 获取可修改的树结点
    // =================================================
    TreeNode<T>* getNodeMutable(int id) {

        // 检查数组下标是否合法
        if (id < 0 || id >= capacity) {
            throw out_of_range("Node ID out of range");
        }

        // 返回对应结点的地址
        // 不是创建新结点！
        return &nodes[id];
    }


    // =================================================
    // 2. 判断结点是否连接在当前根结点下
    // =================================================
    // 通过 parent 指针不断向上寻找。
    // 如果最终找到 root，说明属于当前树。
    bool belongsToRoot(const TreeNode<T>* node) const {

        while (node != nullptr) {

            if (node == root) {
                return true;
            }

            node = node->parent;
        }

        return false;
    }


    // =================================================
    // 3. 递归打印树的层次结构
    // =================================================
    void printFrom(const TreeNode<T>* node,
                   int level) const {

        // 递归终止条件
        if (node == nullptr) {
            return;
        }

        // 根据结点的层次输出缩进
        // 每向下一层，多输出两个空格
        for (int i = 0; i < level; ++i) {
            cout << "  ";
        }

        // 输出当前结点的数据
        cout << node->data << endl;

        // 获取当前结点孩子链表的头指针
        auto* p = node->childrenHead;

        // 遍历每一个孩子结点
        while (p != nullptr) {

            // p->data 是 TreeNode<T>* 类型
            // 递归打印该孩子及其所有后代
            printFrom(p->data, level + 1);

            // 移动到下一个孩子
            p = p->next;
        }
    }


    // =================================================
    // 4. 深度优先遍历 DFS（先根遍历）
    // =================================================
    void dfsFrom(const TreeNode<T>* node) const {

        if (node == nullptr) {
            return;
        }

        // 先访问当前结点
        cout << node->data << " ";

        auto* p = node->childrenHead;

        // 再递归访问每一个子树
        while (p != nullptr) {

            dfsFrom(p->data);

            p = p->next;
        }
    }


    // =================================================
    // 5. 递归统计结点数量
    // =================================================
    int sizeFrom(const TreeNode<T>* node) const {

        if (node == nullptr) {
            return 0;
        }

        // 当前结点本身算一个
        int result = 1;

        auto* p = node->childrenHead;

        // 累加每棵子树中的结点数量
        while (p != nullptr) {

            result += sizeFrom(p->data);

            p = p->next;
        }

        return result;
    }


    // =================================================
    // 6. 递归计算树的高度
    // =================================================
    // 约定：
    // 空树高度 = -1
    // 叶子结点高度 = 0
    // 高度按照最长路径上的边数计算
    int heightFrom(const TreeNode<T>* node) const {

        if (node == nullptr) {
            return -1;
        }

        // 用于保存所有子树中最大的高度
        int maxChildHeight = -1;

        auto* p = node->childrenHead;

        while (p != nullptr) {

            // 计算当前子树的高度
            int h = heightFrom(p->data);

            // 更新最大子树高度
            if (h > maxChildHeight) {
                maxChildHeight = h;
            }
            
            p = p->next;
        }

        // 当前结点高度 = 最大子树高度 + 1
        return maxChildHeight + 1;
    }


    // =================================================
    // 7. 递归计算树的度
    // =================================================
    // 树的度 = 所有结点的度中的最大值
    // 结点的度 = 该结点的直接孩子数量
    int degreeFrom(const TreeNode<T>* node) const {

        if (node == nullptr) {
            return 0;
        }

        // 当前结点拥有的孩子数量
        int childrenCount = 0;

        // 所有子树中的最大结点度
        int maxDegree = 0;

        auto* p = node->childrenHead;

        while (p != nullptr) {

            // 当前结点又有一个孩子
            ++childrenCount;

            // 递归计算孩子子树中的最大度
            int degree = degreeFrom(p->data);

            if (degree > maxDegree) {
                maxDegree = degree;
            }

            p = p->next;
        }

        // 树的度是所有结点度的最大值
        return childrenCount > maxDegree
                   ? childrenCount
                   : maxDegree;
    }


public:

    // =================================================
    // 8. 默认构造函数
    // =================================================
    // 委托给带参数构造函数
    // 默认创建容量为 100001 的数组
    Tree() : Tree(100001) {}


    // =================================================
    // 9. 带参数构造函数
    // =================================================
    explicit Tree(int maxNodes)
        : nodes(nullptr),
          root(nullptr),
          capacity(maxNodes) {

        // 保证申请的数组容量合法
        if (capacity <= 0) {
            throw invalid_argument(
                "Capacity must be positive"
            );
        }

        // 创建 capacity 个 TreeNode 对象
        nodes = new TreeNode<T>[capacity];
    }


    // =================================================
    // 10. 禁止 Tree 对象浅拷贝
    // =================================================
    // 如果两个 Tree 对象持有同一个 nodes 地址，
    // 析构时会重复 delete[]。
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;


    // =================================================
    // 11. 析构函数
    // =================================================
    ~Tree() {

        // delete[] 会调用数组中每个 TreeNode
        // 的析构函数，释放对应的孩子链表。
        //
        // 最后释放整个 TreeNode 数组。
        delete[] nodes;

        // 不需要单独 delete root
        // 因为 root 指向 nodes 数组中的元素
    }


    // =================================================
    // 12. 根据 ID 获取树结点（只读接口）
    // =================================================
    const TreeNode<T>* GetTreeNode(int id) const {

        if (id < 0 || id >= capacity) {
            throw out_of_range("Node ID out of range");
        }

        return &nodes[id];
    }


    // =================================================
    // 13. 设置根结点
    // =================================================
    // 本实现要求先设置根结点，再添加孩子。
    // 且每个 Tree 对象只允许设置一次根结点。
    void SetRoot(int rootId) {

        if (root != nullptr) {
            throw logic_error("Root is already set");
        }

        root = getNodeMutable(rootId);
    }


    // =================================================
    // 14. 添加孩子结点
    // =================================================
    // parentId：父结点在 nodes 中的下标
    // childId ：孩子结点在 nodes 中的下标
    void AddChild(int parentId, int childId) {

        // 必须先设置根结点
        if (root == nullptr) {
            throw logic_error(
                "Set root before adding children"
            );
        }

        // 根据 ID 获取两个树结点的地址
        TreeNode<T>* parentNode =
            getNodeMutable(parentId);

        TreeNode<T>* childNode =
            getNodeMutable(childId);

        // 不允许自己成为自己的孩子
        if (parentNode == childNode) {
            throw logic_error(
                "Node cannot be its own child"
            );
        }

        // 父结点必须已经属于根结点所在的树
        if (!belongsToRoot(parentNode)) {
            throw logic_error(
                "Parent must be connected to the root"
            );
        }

        // 根结点不能成为其他结点的孩子
        if (childNode == root) {
            throw logic_error(
                "Root cannot become a child"
            );
        }

        // 一个结点只能有一个父结点
        if (childNode->parent != nullptr) {
            throw logic_error(
                "Child already has a parent"
            );
        }

        // 调用 TreeNode 类中的 AddChild 函数
        // 将 childNode 的地址加入父结点孩子链表
        parentNode->AddChild(childNode);
    }


    // =================================================
    // 15. 修改某个树结点的数据
    // =================================================
    void AssignData(int id, const T& value) {

        getNodeMutable(id)->data = value;
    }


    // =================================================
    // 16. 输出整棵树
    // =================================================
    void Print() const {

        // 从根结点开始，初始层次为 0
        printFrom(root, 0);
    }


    // =================================================
    // 17. 深度优先遍历
    // =================================================
    void DFS() const {

        dfsFrom(root);

        cout << endl;
    }


    // =================================================
    // 18. 获取树的结点数量
    // =================================================
    int GetSize() const {

        return sizeFrom(root);
    }


    // =================================================
    // 19. 获取树的高度
    // =================================================
    int GetHeight() const {

        return heightFrom(root);
    }


    // =================================================
    // 20. 获取树的度
    // =================================================
    int GetDegree() const {

        return degreeFrom(root);
    }
};


// ====================================================
// 四、主函数：测试普通树
// ====================================================

int main() {

    // 创建一棵最多包含 9 个结点的树
    Tree<char> tree(9);

    // 设置 nodes[0] 为根结点
    tree.SetRoot(0);


    // -------------------------
    // 1. 为所有结点赋值
    // -------------------------
    tree.AssignData(0, 'a');
    tree.AssignData(1, 'b');
    tree.AssignData(2, 'c');
    tree.AssignData(3, 'd');
    tree.AssignData(4, 'e');
    tree.AssignData(5, 'f');
    tree.AssignData(6, 'g');
    tree.AssignData(7, 'h');
    tree.AssignData(8, 'i');


    // -------------------------
    // 2. 建立父子关系
    // -------------------------

    // a 的孩子：先 c，后 b
    tree.AddChild(0, 2);
    tree.AddChild(0, 1);

    // b 的孩子：d
    tree.AddChild(1, 3);

    // c 的孩子：先 f，后 e
    tree.AddChild(2, 5);
    tree.AddChild(2, 4);

    // d 的孩子：i、h、g
    tree.AddChild(3, 8);
    tree.AddChild(3, 7);
    tree.AddChild(3, 6);


    // -------------------------
    // 3. 打印树结构
    // -------------------------
    cout << "Tree structure:" << endl;

    tree.Print();


    // -------------------------
    // 4. DFS 遍历
    // -------------------------
    cout << "DFS: ";

    tree.DFS();


    // -------------------------
    // 5. 输出树的基本信息
    // -------------------------
    cout << "Size: "
         << tree.GetSize() << endl;

    cout << "Height (edges): "
         << tree.GetHeight() << endl;

    cout << "Degree: "
         << tree.GetDegree() << endl;


    // main 结束时，tree 自动析构。
    // 析构会释放所有孩子链表及 nodes 数组。
    return 0;
}
