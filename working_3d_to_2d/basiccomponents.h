#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H
#include<vector>
using namespace std;
struct Vertice
{

// public:
float first,second,third;
bool is3d;

bool operator<(Vertice other) const
    {

        if(is3d) return make_pair(first,make_pair(second,third)) > make_pair(other.first,make_pair(other.second,other.third));
        else return make_pair(first,second) > make_pair(other.first,other.second);
    }



};

struct Edge{

// public:
pair<Vertice,Vertice> vertices;

bool operator<(Edge other) const
    {
        return vertices > other.vertices;
    }



};


#endif
