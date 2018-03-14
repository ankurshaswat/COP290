/** Defines classes for representing 2D views and 3D objects*/
#ifndef FIG3D_H
#define FIG3D_H

#include "basicComponents.h"
#include<set>



class Fig3D
{

private:

public:

Vector<Face> faces;

void getProjections(int plane, set<Edge> & edgeSet); /** get XY, YZ , XZ and isometric projections  of the 3D object*/

Fig3D getTransformation(vector<double> matrix); /** get transformed 3D object */

//void AddOffset(double x,double y,double z);
//void AddRoll(double r);
//void AddYaw(double y);
//void AddPitch(double p);


};


#endif
