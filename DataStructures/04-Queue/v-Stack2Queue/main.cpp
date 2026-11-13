//
// Created by jason on 2026/11/13.
//
#include<iostream>
#include<stack>
using namespace std;

class stk2queue {
    stack<int> s1;
    stack<int> s2;
public:
    stk2queue() {}
    void push(int val) {
        s1.push(val);
    }
    int pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int tmp = s2.top();
        s2.pop();
        return tmp;
    }
    int peek() {
        if (s2.empty()) {
            while (s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    bool empty() {
        return s1.empty()&&s2.empty();
    }
};

int main() {
    stk2queue q;
    for (int i = 1;i<6;i++) {
        q.push(i);
    }
    cout<<q.pop()<<endl;
    cout<<q.peek()<<endl;
    return 0;
}