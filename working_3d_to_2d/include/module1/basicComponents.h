#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H
#include <vector>
#include <string>
using namespace std;
struct Vertice
{

// public:
        float first,second,third;
        bool is3d=true;
        char label;

        bool operator<(Vertice other) const
        {

                if(is3d) return make_pair(first,make_pair(second,third)) > make_pair(other.first,make_pair(other.second,other.third));
                else return make_pair(first,second) > make_pair(other.first,other.second);
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



};

struct plane {
        double a,b,c,d;
};


#endif
