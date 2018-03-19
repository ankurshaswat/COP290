#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H
#include <vector>
#include <string>
using namespace std;
struct Vertice
{

// public:
        float first,second,third=0;
        bool is3d=true;
        char label;

        bool operator<(Vertice other) const
        {

                if(is3d) return make_pair(first,make_pair(second,third)) > make_pair(other.first,make_pair(other.second,other.third));
                else return make_pair(first,second) > make_pair(other.first,other.second);
        }

        bool operator ==(Vertice b) {
	return (first == b.first) && (second == b.second) && ( (third==b.third && b.is3d && is3d) || (!is3d) );
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
