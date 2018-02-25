// Edge.h
#ifndef EDGELOOP_H
#define EDGELOOP_H

#include "Edge.h"

class EdgeLoop
{

private:
Edge edgeList[10];

public:
Edge* getEdgeList();
bool isContained(EdgeLoop a);



};

#endif
