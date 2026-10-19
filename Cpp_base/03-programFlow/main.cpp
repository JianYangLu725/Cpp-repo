//
// Created by jason on 2026/10/19.
//
#include <iostream>
using namespace std;

int main() {
    int a = 0;
    cin >> a;
    switch (a) {
        case 0:
            cout << "Zero" << endl;
            break;
        case 1:
            cout << "One" << endl;
            break;
        case 2:
            cout << "Two" << endl;
            break;
        case 3:
            cout << "Three" << endl;
            break;
        default:
            cout << "Beyond three or below zero" << endl;
    }

    for (int i=0;i<10;i++) {
        if (i<3){continue;}
        cout << i << endl;
    }

    return 0;
}