#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "basicComponents.h"
#include<vector> 
#include<set>

Vertice transform(Vertice v_in,double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff);

pair<int,Vertice> get_intersection(Edge a, Edge b);

bool is_inside(Vertice v, set<Edge> edgeSet);

bool isSubset(vector<int> & a, vector<int> & b);

int verticePresent(vector<Vertice> & a, Vertice b);


#endif // HELPERFUNCTIONS_H
