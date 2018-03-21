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
WireFrame getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff); /** get transformed 3D object */

//vector<Edge> & getEdgeList();

};


#endif
