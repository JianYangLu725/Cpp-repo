//
// Created by jason on 2026/11/17.
//
#include<iostream>
#include<cstring>
using namespace std;

class String {
private:
    char* str;
    size_t length;
public:
    String();//构造函数
    String(const char* s);//构造函数，初始化为传参值
    String(const String& other);//拷贝构造
    ~String();//析构

    size_t getLength() const;//获取长度
    char operator[](size_t index) const;//重载[]，获取index索引字符
    String& operator=(const String& other);//重载=，将字符串赋值给当前字符串
    bool operator==(const String& other)const;//重载==，比较两字符串是否相等
    bool operator!=(const String& other)const;//重载！=，比较两字符串是否不等
    String copy()const;//字符串拷贝函数
    String operator+(const String& other)const;//重载+，字符串拼接

    friend ostream& operator<<(ostream& out,const String& other);//连续输出

};

String::String() {
    str = new char[1];
    str[0] = '\0';
    length = 0;
}

String::String(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str,s);
}

String::String(const String& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy(str,other.str);
}

String::~String() {
    delete [] str;
}

size_t String::getLength() const {
    return length;
}

char String::operator[](size_t index) const {
    return str[index];
}

String& String::operator=(const String& other) {
    if (this!=&other) {
        delete [] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str,other.str);
    }

    return *this;
}

bool String::operator==(const String& other)const{
    return strcmp(str,other.str) == 0;
}

bool String::operator!=(const String& other) const{
    return strcmp(str,other.str) != 0;
}

String String::copy() const {
    String s = *this;
    return s;
}

String String::operator+(const String& other)const {
    String res;
    delete[] res.str;
    res.length = length + other.length;
    res.str = new char[res.length + 1];
    strcpy(res.str,str);
    strcat(res.str,other.str);
    return res;

}

ostream& operator<<(ostream& out,const String& other) {
    out<<other.str;
    return out;
}

int main() {
    String s("12345d");
    cout << s << endl;
    cout << s + "445" << endl;
    cout << s[5] << endl;
    cout << (s == "12345d") << endl;
    cout << (s != "12345d") << endl;
    s = s + "asd";
    String a, b, c;
    a = b = c = s;
    cout << s << endl;
    cout << a << b << c << s << endl;
    String x = s.copy();
    cout << x << endl;
    return 0;
}