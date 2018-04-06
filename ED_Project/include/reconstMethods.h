/** Defines methods required for 3D reconstruction process*/
#ifndef RECONSTMETHODS_H
#define RECONSTMETHODS_H

#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"

/// Function to construct 3d edges from 2d edges by checking the possibility of the edges being projections of each other.
WireFrame constUniq3dEdges(vector<vector<Edge> > edgeSet);

/// Function to read txt file contatining labelled data of xy , yz and xz views and returns the result as a vector of vector of edges.
std::vector<std::vector<Edge> > readFile(const char *);

/// Takes a wireframe object and converts it into a 3d object by creating faces by forming edge loops.
Fig3D wireframeTo3D(WireFrame a);

/** Returns coplanar sets of edges  of size>=3 (each coplanar set is represented as a list of edge indices) */
vector< vector<int> >  coplanarEdges (vector<Edge> & edges);

/** takes input a set of coplanar edges (as edges + indices) and returns a list of edge loops(candidate faces) formed using these edges (each edgeLoop is represented by a list of indices)*/
vector< vector<int>>  getEdgeLoops(vector<Edge> & edges, vector<int> coplanarIndices);





#endif
