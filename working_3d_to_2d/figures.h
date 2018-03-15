#ifndef FIGURES_H
#define FIGURES_H

#include "basiccomponents.h"

/** Defines classes for representing 2D views and 3D objects*/
#include <set>



class Fig3D
{

private:

public:
vector<Vertice> vertices;
vector<vector<unsigned int> > faces;

void getProjections(int plane, set<Edge> edgeSet2D); /** get XY, YZ , XZ and isometric projections  of the 3D object*/

Fig3D getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff); /** get transformed 3D object */


};


#endif // FIGURES_H
