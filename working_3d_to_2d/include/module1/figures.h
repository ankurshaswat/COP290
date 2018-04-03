#ifndef FIGURES_H
#define FIGURES_H

#include "basicComponents.h"


#include <set>


/** Defines classes for representing 2D views and 3D objects*/
class Fig3D
{

private:

public:
vector<Vertice> vertices;
vector<vector<unsigned int> > faces;

/** get XY, YZ , XZ and isometric projections  of the 3D object*/
void getProjections(int plane, set<Edge> & edgeSet2D); 

 /** get XY, YZ , XZ and isometric projections  of the 3D object*/
void getAxes(int plane, set<Edge> & edgeSet2D);

/** get transformed 3D object */
Fig3D getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff); 


};


#endif // FIGURES_H
