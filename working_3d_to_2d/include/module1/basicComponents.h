#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#define EPS 0.01
using namespace std;
struct Vertice
{

// public:
        float first,second,third=0;
        bool is3d=true;
        char label;
        Vertice deepCopy(){
                Vertice t;
                t.first=first;
                t.second=second;
                t.third=third;
                t.is3d=is3d;
                return t;
        }
        bool operator<(Vertice other) const
        {

                if(is3d) return make_pair(first*100,make_pair(second*100,third*100)) > make_pair(other.first*100,make_pair(other.second*100,other.third*100));
                else return make_pair(first*100,second*100) > make_pair(other.first*100,other.second*100);
        }

        bool operator ==(Vertice b) {
	return  (abs(first - b.first)<EPS ) && (abs(second - b.second)<EPS ) && ( ( (abs(third - b.third)<EPS ) && b.is3d && is3d) || (!is3d) );
        }
        Vertice operator-(const Vertice& rhs){
                Vertice diff;
                diff.first=first - rhs.first;
                diff.second=second -= rhs.second;
                if(is3d && rhs.is3d) {
                        diff.third=third-=rhs.third;
                        diff.is3d=true;
                }
                else{
                        diff.is3d=false;
                }
                return diff;
        }
        


};

inline ostream& operator<<(std::ostream& os,const Vertice& v)
{
    if(v.is3d)  return os << v.first+50 << ", " << v.second+50 << ", " << v.third+50 << endl;
    else return os << v.first+50 << ", " << v.second+50 <<endl;
}

struct Edge {

// public:
        pair<Vertice,Vertice> vertices;

        bool operator<(Edge other) const
        {
                return vertices > other.vertices;
        }
        bool operator ==(Edge b) {
	return (vertices.first==b.vertices.first && vertices.second==b.vertices.second ) || 
        ( vertices.first==b.vertices.second && vertices.second==b.vertices.first );
        }


};

struct plane {
        double a,b,c,d;
};


#endif
