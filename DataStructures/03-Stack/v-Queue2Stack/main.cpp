//
// Created by jason on 2026/11/13.
//
#include<iostream>
#include<queue>

using namespace std;

class Queue2Stk {
    queue<int> q1;
    queue<int> q2;
public:
    Queue2Stk(){}

    void push(int val) {
        q1.push(val);
    }

    int pop() {
        while (q1.size()>1) {
            int val = q1.front();
            q2.push(val);
            q1.pop();
        }
        const int res = q2.front();
        q2.pop();
        while (!q2.empty()) {
            int val = q2.front();
            q1.push(val);
            q2.pop();
        }
        return res;
    }

    int peek() {
        while (q1.size()>1) {
            int val = q1.front();
            q2.push(val);
            q1.pop();
        }
        int res = q2.front();
        q2.pop();
        q1.push(res);
        while (!q2.empty()) {
            int val = q2.front();
            q1.push(val);
            q2.pop();
        }
        return res;
    }
};

int main() {
    Queue2Stk q;
    for (int i = 0 ; i < 10;i++) {
        q.push(i);
    }
    q.pop();
    cout<<q.peek()<<endl;
    return 0;
}