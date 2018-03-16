/** Some high level components used as intermediates in our algorithms */
#ifndef COMPLEXCOMPONENTS_H
#define COMPLEXCOMPONENTS_H

#include "basicComponents.h"

class EdgeLoop: public Face 
{
/** a planar closed loop of edges (connected end-to-end), basically a face extended with other methods*/
public:
bool isContained(EdgeLoop a){
        /** to check whether an edgeLoop is completely contained in another */
    };
};
class WireFrame
{

private:
Edge edgeList[100];

public:
Edge* getEdgeList();
 
};


#endif
