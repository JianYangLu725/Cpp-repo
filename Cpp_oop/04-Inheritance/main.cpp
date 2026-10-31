//
// Created by jason on 2026/10/31.
//
#include<iostream>
#include<string>
using namespace std;

//继承中的同名情况
class People {
public:
    string name ;
    string gender ;
    int age ;
    double  tall ;
    People(){name = "none";gender = "male";age = 12;tall = 0.00;}
    People(string name, string gender, int age, double tall):name(name), gender(gender), age(age), tall(tall){}
    ~People() {
        cout<<"People destroyed"<<endl;
    }
    void printInfo() const {
        cout<<name<<"的基本信息是:"<<endl;
        cout<<"gender:"<<gender<<endl;
        cout<<"age:"<<age<<endl;
        cout<<"tall:"<<tall<<endl;
    }
};

class yellowPeople:public People {
public :
    string color = "yellow";
    yellowPeople(){name = "none";gender = "male";age = 12;tall = 0.00;}
    yellowPeople(string name, string gender, int age, double tall):People(name,gender,age,tall){}
   ~yellowPeople() {
        cout<<"yellowPeople destroyed"<<endl;
    }
    void printInfo() const {
        cout<<name<<"的基本信息是:"<<endl;
        cout<<"gender:"<<gender<<endl;
        cout<<"age:"<<age<<endl;
        cout<<"tall:"<<tall<<endl;
        cout<<"color:"<<color<<endl;
    }
};
int main() {
    People yp;
    yellowPeople jason;
    jason.printInfo();
    jason.People::printInfo();
    return 0;
}