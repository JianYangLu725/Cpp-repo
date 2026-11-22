//
// Created by jason on 2026/11/22.
//
#include<iostream>
#include<stdexcept>
#include<queue>
using namespace std;

template<typename T>
struct treeNode {
    T val;
    treeNode<T>* left;
    treeNode<T>* right;

    treeNode(): val(), left(nullptr), right(nullptr) {}
    treeNode(T d):val(d), left(nullptr), right(nullptr) {}
};

template<typename T>
class binaryTree {
private:
    treeNode<T>* nodes;
    treeNode<T>* root;
    size_t nodeSize;

    treeNode<T>* create(T a[],int size,int nodeId,T nullNode);
    void visit(treeNode<T>* node) const;
    void preOrder(treeNode<T>* node) const;//前序遍历
    void inOrder(treeNode<T>* node) const;//中序遍历
    void postOrder(treeNode<T>* node) const;//后序遍历
   // void levelOrder(treeNode<T>* node) const;
public:
    binaryTree();
    explicit binaryTree(int maxCapacity);
    ~binaryTree();

    treeNode<T>* getNode(int idx);
    void createTree(T a[],int size,T nullNode);
    void preOrderTraversal()const;
    void inOrderTraversal()const;
    void postOrderTraversal()const;
};

template<typename T>
binaryTree<T>::binaryTree() {
    nodeSize = 100001;
    root = nullptr;
    nodes = new treeNode<T>[nodeSize];
}

template<typename T>
binaryTree<T>::binaryTree(int maxCapacity) {
    nodes = new treeNode<T>[maxCapacity];
    nodeSize = maxCapacity;
    root = nullptr;
}

template<typename T>
binaryTree<T>::~binaryTree() {
    delete[] nodes;
}

template<typename T>
void binaryTree<T>::visit(treeNode<T>* node) const {
    cout<<node->val<<" ";
}

template<typename T>
treeNode<T>* binaryTree<T>::getNode(int idx) {
    return &nodes[idx];
}

/*
 前序遍历：根->左->右
 */
template<typename T>
void binaryTree<T>::preOrder(treeNode<T>* node) const {
    if (node) {
        visit(node);
        preOrder(node->left);
        preOrder(node->right);
    }
}

/*
 中序遍历：左->根->右
 */
template<typename T>
void binaryTree<T>::inOrder(treeNode<T> *node) const {
    if (node) {
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

/*
 后序遍历：左->右->根
 */
template<typename T>
void binaryTree<T>::postOrder(treeNode<T> *node) const {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}

template<typename T>
treeNode<T>* binaryTree<T>::create(T a[],int size,int nodeId,T nullNode) {
    //递归退出条件，nodeId是下标，是去找数组a对应数据的，如果超出范围，或者数组在该位置的元素是nullNode，直接返回nullptr，
    //表示此时序号为nodeId的树节点是空的！
    if (nodeId>=size||a[nodeId] == nullNode) {
        return nullptr;
    }

    //创建一个treeNode<T>类型的指针，指向nodeId的地址，这是一个树节点
    auto* nowNode = getNode(nodeId);
    //数据赋值给这个树节点内部的数据域
    nowNode->val = std::move(a[nodeId]);

    //开始递归
    /*
     先nowNode->left = create(a,size,nodeId*2,nullNode);
     nodeId*2，会不断往下指定左子树，达到最下面的左子树，再nodeId*2,a[nodeId] == nullNode就会退出递归
     这一级创建的nowNode返回给上一级并赋值给上一级nowNode->left。（设此时是倒数1层返回给倒数2层）
     倒数2层随后开始nowNode->right = create(a,size,nodeId*2+1,nullNode);的递归
     同样正常执行判断，先创建左子树再创建右子树，这里因为假设已是倒数一层，所以nodeId*2+1也会退出递归，返回nowNode给上一级的nowNode->right
     这样倒数2层的这个节点它的左右子树就创建完成。而这个节点可能是倒数3层的左子树节点，倒数3层的节点随后开始它的右子树递归创建。
     */
    nowNode->left = create(a,size,nodeId*2,nullNode);
    nowNode->right = create(a,size,nodeId*2+1,nullNode);

    return nowNode;
}

template<typename T>
void binaryTree<T>::createTree(T a[],int size,T nullNode) {
    root = create(a,size,1,nullNode);
}

template<typename T>
void binaryTree<T>::preOrderTraversal()const{
    preOrder(root);
}

template<typename T>
void binaryTree<T>::inOrderTraversal() const{
    inOrder(root);
}

template<typename T>
void binaryTree<T>::postOrderTraversal() const{
    postOrder(root);
}

int main() {
    const char nullNode = '-';
    char a[15] = {
        nullNode, 'a', 'b', 'c', 'd',
        nullNode, 'e', 'f', 'g', 'h',
        nullNode, nullNode, nullNode, nullNode, 'i'
    };

    binaryTree<char> T(15);
    T.createTree(a, 15, nullNode);
    T.preOrderTraversal(); cout << endl;
    T.inOrderTraversal(); cout << endl;
    T.postOrderTraversal(); cout << endl;
    return 0;
}