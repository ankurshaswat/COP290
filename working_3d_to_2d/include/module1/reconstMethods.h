/** Defines methods required for 3D reconstruction process*/
#ifndef RECONSTMETHODS_H
#define RECONSTMETHODS_H

#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"

WireFrame constUniq3dEdges(vector<vector<Edge> > edgeSet);
std::vector<std::vector<Edge> > readFile(const char *);

/** Returns coplanar sets of edges  of size>=3 (each coplanar set is represented as a list of edge indices) */
vector< vector<int> >  coplanarEdges (vector<Edge> & edges);

/** takes input a set of coplanar edges (as edges + indices) and returns a list of edge loops(candidate faces) formed using these edges (each edgeLoop is represented by a list of indices)*/
vector< vector<int>>  getEdgeLoops(vector<Edge> & edges, vector<int> coplanarIndices);

// partialOrder constructPoset(EdgeLoop* a);
// /** takes input a set of edgeLoops and returns a partial order defined on isContained relation*/

// EdgeLoop* getValidEdgeLoops(EdgeLoop* a, partialOrder b);
// /** takes input a poset (set + partial order on the set) and returns a list of edgeLoops that qualify to be labelled as faces*/

vector< vector<int> > getValidFaces(vector<Edge> & edges , vector< vector<int> >  candidateFaces);



#endif
