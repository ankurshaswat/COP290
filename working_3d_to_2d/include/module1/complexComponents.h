/** Some high level components used as intermediates in our algorithms */
#ifndef COMPLEXCOMPONENTS_H
#define COMPLEXCOMPONENTS_H

#include "basicComponents.h"
#include <vector>

class EdgeLoop
{
/** a planar closed loop of edges (connected end-to-end)*/
public:
vector<Vertice> vertices;
bool isContained(EdgeLoop a);  /** to check whether an edgeLoop is completely contained in another */
};
class WireFrame
{

public:
vector<Edge> edges;
vector<Edge> & getEdgeList();

};


#endif
