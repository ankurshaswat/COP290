/** Defines classes for representing 2D views and 3D objects*/
#ifndef FIG3D_H
#define FIG3D_H

#include "basicComponents.h"


class Fig2D
{

private:
vector<Edge> edges;

public:
bool isEdgePresent(Edge a){
    /** helper function needed for wireframe construction*/
};

class Fig3D
{

private:
double XOffset,YOffset,ZOffset;
vector<Face> faces;
vector<Edge> edges;
Vector<Vertice> vertices;

public:
Fig2D* getProjections(){
    /** get XY, YZ and XZ projections (3 2D figures) of the 3D object*/
};
void AddOffset(double x,double y,double z);
void AddRoll(double r);
void AddYaw(double y);
void AddPitch(double p);

};


#endif
