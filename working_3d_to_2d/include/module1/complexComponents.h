/** Some high level components used as intermediates in our algorithms */
#ifndef COMPLEXCOMPONENTS_H
#define COMPLEXCOMPONENTS_H

#include "basicComponents.h"
#include <vector>

/** 
 * a planar closed loop of edges (connected end-to-end)
 */
class EdgeLoop
{

public:
vector<Vertice> vertices;

/** 
 * Function to check whether an edgeLoop is completely contained in another
 */
bool isContained(EdgeLoop a);  
};


class WireFrame
{

public:
vector<Edge> edges;

/** get transformed 3D object */
WireFrame getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff); 

//vector<Edge> & getEdgeList();

};


#endif
