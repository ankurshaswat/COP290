// Edge.h
#ifndef EDGE_H
#define EDGE_H

#include "Vertice.h"

class Edge
{

private:
Vertice vertice[2];

public:
Vertice* endPoints();
bool isPlanar(Edge a, Edge b);


};

#endif
