/** Defines methods required for 3D reconstruction process*/
#ifndef RECONSTMETHODS_H
#define RECONSTMETHODS_H

#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"

WireFrame constUniq3dEdges(vector<vector<Edge> > edgeSet);

std::vector<std::vector<Edge> > readFile(const char *);

Fig3D wireframeTo3D(WireFrame a);

/** Returns coplanar sets of edges  of size>=3 (each coplanar set is represented as a list of edge indices) */
vector< vector<int> >  coplanarEdges (vector<Edge> & edges);

/** takes input a set of coplanar edges (as edges + indices) and returns a list of edge loops(candidate faces) formed using these edges (each edgeLoop is represented by a list of indices)*/
vector< vector<int>>  getEdgeLoops(vector<Edge> & edges, vector<int> coplanarIndices);





#endif
