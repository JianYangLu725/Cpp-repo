//
// Created by jason on 2026/10/19.
//
#include <iostream>
using namespace std;

int main() {
    int a[]={1,2,3,4,5,6,7,8,9,10};

    //访问
    for(int i=0;i<size(a);i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    //逆序数处
    for (int i=size(a)-1;i>=0;i--) {
        cout<<a[i]<<" ";
    }
    return 0;
}