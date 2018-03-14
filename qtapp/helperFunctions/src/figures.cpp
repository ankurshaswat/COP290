#include "figures.h"
#include <math.h>
#define PI 3.14159265
class Fig3D {

void getProjections(int plane, set<Edge> & edgeSet){
        /** get XY, YZ , XZ and isometric projections  of the 3D object*/

};

Fig3D getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff){
        /** get transformed 3D object */
        Fig3D newFig;

        double sinXrot= sin(Xrot * PI/180 ),cosXrot= cos(Xrot * PI/180 );
        double sinYrot= sin(Yrot * PI/180 ),cosYrot= cos(Yrot * PI/180 );
        double sinZrot= sin(Zrot * PI/180 ),cosZrot= cos(Zrot * PI/180 );

        double transformationMat[4][4]={{cosYrot * cosZrot, cosXrot * sinZrot +sinXrot*sinYrot*cosZrot,sinXrot*sinZrot-cosXrot*sinYrot*cosZrot,Xoff},
                                        {-1*cosYrot*sinZrot,cosXrot*cosZrot-sinXrot*sinYrot*sinZrot,sinXrot*cosZrot+cosXrot*sinYrot*sinZrot,Yoff},
                                        {sinYrot,-1*sinXrot*cosYrot,cosXrot*cosYrot,Zoff},
                                        {0,0,0,1}};
        double matA[1][4],result[1][4];
        matA[0][4]=1;
        newFig.faces = this.faces;

        for(int m=0; m<vertices.size(); m++) {

              matA[0][0]=vertices[m].x;
              matA[0][1]=vertices[m].y;
              matA[0][2]=vertices[m].z;

                for(i = 0; i < 1; ++i)
                        for(j = 0; j < 4; ++j)
                                for(k = 0; k < 4; ++k)
                                {
                                        result[i][j] += matA[i][k] * transformationMat[k][j];
                                }
              Vertice v;
              v.x=result[0][0];
              v.y=result[0][1];
              v.z=result[0][2];
              newFig.vertices.push_back(v);
        }

        return newFig;
};

}
