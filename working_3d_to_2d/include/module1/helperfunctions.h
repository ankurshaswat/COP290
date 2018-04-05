#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "basicComponents.h"
#include "complexComponents.h"
#include<vector> 
#include<set>

/// Transforms a vertice (rotation and offset) using matrix multiplication and returns a new Vertice object.
Vertice transform(Vertice v_in,double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff);

/// Finds intersection of two edges (line segments) and also returns error if intersection does not exist.
pair<int,Vertice> get_intersection(Edge a, Edge b);

/// Checks whether a vertice is inside (in 2d) of a face formed by an edge loop.
bool is_inside(Vertice v, set<Edge> edgeSet);

bool isSubset(vector<int> & a, vector<int> & b);

/// Checks if a vertice is present in a vector of vertices.
int verticePresent(vector<Vertice> & a, Vertice b);

///Takes a wireframe and subtracts coordinates of v from  all its edge vertices 
WireFrame modifyWireframe(WireFrame wf, Vertice v) ;

#endif // HELPERFUNCTIONS_H
