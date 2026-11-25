//
// Created by jason on 2026/11/25.
//
#include<iostream>
#include<stdexcept>
using namespace std;

#define info -1;

template<class T>
class graph {
private:
    int vertices;
    T** edges;
public:
    graph();
    graph(int n);
    ~graph();

    void addEdge(int u,int v,int w);
    void print() const;
};

template<class T>
graph<T>::graph():graph(101){}

template<class T>
graph<T>::graph(int n) {
    if ( n < 0 ) {
        throw invalid_argument("vertices must be non-negative");
    }
    vertices = n;
    edges = new T*[n];//二级指针指向一个指针数组，每个元素是一个指针
    for (int i = 0 ; i < n ; i++) {
        edges[i] = new T[n];//数组中的每一个元素（指针）指向一个元素类型为T的数组
        for (int j = 0 ; j < n ; j++) {
            edges[i][j] = info;
        }
    }
}

template<class T>
graph<T>::~graph() {
    //先释放每个指针数组中的元素指向的数组所申请的内存
    for (int i = 0 ; i < vertices ; i++) {
        delete [] edges[i];
    }
    //再释放这个指针数组所申请的内存
    delete [] edges;
}

template<class T>
void graph<T>::addEdge(int u,int v,int w) {
    edges[u][v] = w;
}

template<class T>
void graph<T>::print() const {
    for (int i = 0 ; i < vertices ; i++) {
        for (int j = 0 ; j < vertices ; j++) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int vertices = 5;
    graph<int> graph(vertices);

    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 7);
    graph.addEdge(3, 4, 9);
    graph.addEdge(4, 0, 4);
    graph.addEdge(4, 2, 5);

    cout << "邻接矩阵表示的图：" << endl;
    graph.print();

    return 0;
}