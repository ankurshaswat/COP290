// Defines all the low-level components needed to decribe our objects
#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H


class Plane //Plane represented by equation ax+by+cz+d=0
{
public:
double a,b,c,d;
};
class Vertex
{
public:
double x,y,z;
char* label; //vertex label, required when finding matching vertices between 2 views
};

class Edge
{

private:
Vertex vertice[2];

public:
Vertex* endPoints();
bool isPlanar(Edge a); //whether the edge is planar with a given edge (needed in partitioning) 


};

class Face
{

private:
Edge edge[10];
Vertex vertice[10];

public:
Edge* getEdgeList(); 
Vertex* getVertices();
Plane getPlane();
bool intersects(Edge a); //whether the face intersects a given edge

};

#endif
