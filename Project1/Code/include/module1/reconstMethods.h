// Defines methods required for 3D reconstruction process
#ifndef RECONSTMETHODS_H
#define RECONSTMETHODS_H

#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"

Edge** partition(Edge* a); //partitions a given list of edges into coplanar sets
EdgeLoop* getEdgeLoops(Edge* a);//takes input a set of coplanar edges and returns a list of edgeLoops formed using these edges
partialOrder constructPoset(EdgeLoop* a);//takes input a set of edgeLoops and returns a partial order defined on isContained relation
EdgeLoop* getValidEdgeLoops(EdgeLoop* a, partialOrder b) //takes input a poset (set + partial order on the set) and returns a list of edgeLoops that qualify to be labelled as faces



#endif
