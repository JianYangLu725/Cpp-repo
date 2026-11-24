//
// Created by jason on 2026/11/23.
//
#include<iostream>
#include<stdexcept>

using namespace std;


template<typename T>
struct treeNode {
    T val;

    treeNode* left;
    treeNode* right;

    treeNode(const T& data) : val(data), left(nullptr), right(nullptr) {}

};

template<typename T>
class binarySearchTree {
private:
    treeNode<T>* root;
    treeNode<T>* nodes;

    size_t size;

    treeNode<T>* findNode( treeNode<T>* root,const T& target) ;
    treeNode<T>* insertNode(treeNode<T>* root,const T& data);
    treeNode<T>* deleteNode(treeNode<T>* root,const T& target);
    void inOrder(treeNode<T>* root) const;
    //从当前子树的根节点开始，沿左孩子一直走，直到某个节点没有左孩子，该节点就是最小节点。
    treeNode<T>* findMin(treeNode<T>* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
public:
    binarySearchTree():root(nullptr),nodes(nullptr),size(0){}
    ~binarySearchTree() {
        clear(root);
    }
    binarySearchTree(const binarySearchTree&) = delete;

    binarySearchTree& operator=(const binarySearchTree&) = delete;

    treeNode<T>* find(const T& target) {
        return findNode(root,target);
    }

    size_t getSize() const {
        return size;
    }
    //释放整棵树，后序遍历
    void clear(treeNode<T>* root) {
        if (!root) {
            return ;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }

    void insert(const T& data) {
       root =  insertNode(root,data);//注意使用root来接受递归返回的根指针
    }

    void remove(const T& target) {
        /*
         同样注意root接受递归删除函数返回的根节点指针
         如果BST：
         50
         \
         60
         删除50，deleteNode会删除50返回60
         如果不接收它返回的根节点指针，root仍然指向50，而50已经被删除，这使得当前对象的root指针成为悬空指针
         */
        root = deleteNode(root,target);
    }

    void inOrderTraversal() {
        inOrder(root);
    }

};

template<typename T>
treeNode<T>* binarySearchTree<T>::findNode(treeNode<T>* root,const T& target) {
    if (root == nullptr) {
        throw std::out_of_range("NO this value");
    }

    if (target > root->val) {
        return findNode(root->right,target);
    }
    if (target < root->val) {
        return findNode(root->left,target);
    }
    return root;
}

template<typename T>
treeNode<T>* binarySearchTree<T>::insertNode(treeNode<T>* root,const T& data) {
    //当前传入节点为空，说明找到了插入位置，新建一个节点并返回给上一层
    if (root == nullptr) {
        size++;
        return new treeNode<T>(data);
    }

    //插入值大于当前节点值，递归右子树
    if (data > root->val) {
        root->right = insertNode(root->right,data);
    }

    //插入值小于当前节点值，递归左子树
    if (data < root->val) {
        root->left = insertNode(root->left,data);
    }

    //既不大于也不小于直接返回root
    //执行完毕也返回root
    return root;
}

template<typename T>
treeNode<T>* binarySearchTree<T>::deleteNode(treeNode<T>* root,const T& target) {
    //递归到空节点，证明没有目标值
    if (root == nullptr) {
        throw std::out_of_range("NO this value");
    }

    //递归查找目标节点
    //大于当前节点，递归右子树，注意要有接受返回值的左值
    if (target > root -> val) {
        root->right=deleteNode(root -> right,target);
    }
    //小于当前节点，递归左子树，同样注意要有接受返回值的左值
    else if (target < root -> val) {
        root->left=deleteNode(root-> left,target);
    }
    else {
        //既不大于也不小于，那就是等于
        //判断三种情况
        //1.没有左孩子
        if (root -> left == nullptr ) {
            auto* tmp = root -> right;
            delete root;
            size--;
            return tmp;
        }
        //2.没有右孩子
        if (root -> right == nullptr ) {
            auto* tmp = root -> left;
            delete root;
            size--;
            return tmp;
        }

        //3.有两个孩子
        auto* tmp = findMin(root->right);
        root->val = tmp->val;
        root->right = deleteNode(root->right,tmp->val);
    }

    return root;
}

template<typename T>
void binarySearchTree<T>::inOrder(treeNode<T>* root) const {
    if (root) {
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
}

int main() {
    binarySearchTree<int> bst;

    int arr[] = {50, 30, 70, 20, 40, 60, 80, 65};

    for (int x : arr) {
        bst.insert(x);
    }

    cout << "初始中序遍历：";
    bst.inOrderTraversal();

    cout << "节点数量：" << bst.getSize() << endl;

    // 测试重复插入
    bst.insert(65);
    cout << "重复插入后：" << bst.getSize() << endl;

    // 测试三种删除情况
    bst.remove(20); // 删除叶子节点
    bst.remove(60); // 删除单孩子节点
    bst.remove(50); // 删除双孩子节点

    cout << "删除后：";
    bst.inOrderTraversal();

    cout << "剩余节点：" << bst.getSize() << endl;

    return 0;
}