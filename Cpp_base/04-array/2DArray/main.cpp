#include <iostream>
using namespace std;

int main() {
    //数组的数组：数组中的每一个元素是一个数组，其在内存中连续存储
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "a[" << i << "][" << j << "] = "
                 << a[i][j]
                 << " 地址: " << &a[i][j]
                 << endl;
        }
    }

    cout << "数组总大小: " << sizeof(a) << endl;

    return 0;
}