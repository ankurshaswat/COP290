#include "complexComponents.h"
#include "helperfunctions.h"
#define PI 3.14159265



WireFrame WireFrame::getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff) /** get transformed 3D object */
{

WireFrame newWf;

for(int i=0;i<this->edges.size();i++){
    Edge prev=this->edges[i];
    Vertice a1=prev.vertices.first;
    Vertice a2=prev.vertices.second;

    Vertice b1=transform(a1,Xrot,Yrot,Zrot,Xoff,Yoff,Zoff);
    Vertice b2=transform(a2,Xrot,Yrot,Zrot,Xoff,Yoff,Zoff);

    Edge newE;
    newE.vertices={b1,b2};

    newWf.edges.push_back(newE);
}

return newWf;


}
