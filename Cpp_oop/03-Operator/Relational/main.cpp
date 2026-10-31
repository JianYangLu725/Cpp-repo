//
// Created by jason on 2026/10/31.
//
#include<iostream>
using namespace std;

// == < >
class Point {
private:
    int m_x,m_y;
public:
    Point() {
        m_x=0;
        m_y=0;
    }
    Point(int x,int y) : m_x{x},m_y{y} {}
    ~Point() {}

    //==
    bool operator==(const Point& other)const {
        return m_x==other.m_x&&m_y==other.m_y;
    }
    //<
    bool operator<(const Point& other)const {
        int dist = m_x*m_x+m_y*m_y;
        int other_dist = other.m_x*other.m_x+other.m_y*other.m_y;
        return dist<other_dist;
    }
};
int main() {
    Point x(1,2);
    Point y(3,4);
    cout<<(x==y)<<endl;
    cout<<(x<y)<<endl;
    return 0;
}