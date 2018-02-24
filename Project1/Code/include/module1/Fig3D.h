// Fig3D.h
#ifndef FIG3D_H
#define FIG3D_H

#include "Face.h"
#include "Edge.h"
#include "Vertice.h"

class Fig3D
{

private:
double XOffset,YOffset,ZOffset;
Face face[10];
Edge edge[10];
Vertice vertice[10];

public:
void Render();
void AddOffset(double x,double y,double z);
void AddRoll(double r);
void AddYaw(double y);
void AddPitch(double p);


};

#endif
