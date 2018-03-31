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
vector< vector<int> >  CoplanarEdges (vector<Edge> & edges);

/** takes input a set of coplanar edges and returns a list of edgeLoops formed using these edges*/
vector<EdgeLoop>  getEdgeLoops(vector<Edge> & a);

partialOrder constructPoset(EdgeLoop* a);
/** takes input a set of edgeLoops and returns a partial order defined on isContained relation*/

EdgeLoop* getValidEdgeLoops(EdgeLoop* a, partialOrder b);
/** takes input a poset (set + partial order on the set) and returns a list of edgeLoops that qualify to be labelled as faces*/




#endif
