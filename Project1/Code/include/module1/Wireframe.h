// WIREFRAME.h
#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "Edge.h"
#include "Vertice.h"

class Face
{

private:
Edge edge[10];

public:
Edge* getEdges();
vector< vector<Edge> > planarPartitions(); //partitions the edges into coplanar sets


};

#endif
