#include "figures.h"
#include <math.h>
#include <set>
#include "basicComponents.h"
#include <vector>
#include "objLoader.h"
#include "stdio.h"
#define PI 3.14159265

void Fig3D::getProjections(int plane, set<Edge> & edgeSet2D) {
  /** get XY, YZ , XZ and isometric projections  of the 3D object*/
    set<Edge> edgeSet3D;
    get_edges3D(this->vertices, this->faces,edgeSet3D);
    for(auto it:edgeSet3D){
                Vertice u=it.vertices.first, v=it.vertices.second, u_proj, v_proj;
                u_proj.is3d=false;
                v_proj.is3d=false;
                double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
                Edge e;
                if(plane==0){ //XY Plane
                  u_proj.first=ux;
                  u_proj.second=uy;
                  v_proj.first=vx;
                  v_proj.second=vy;
            }
            else if(plane==1){ //YZ Plane
              u_proj.first=uy;
                  u_proj.second=uz;
                  v_proj.first=vy;
                  v_proj.second=vz;
            }
            else if(plane==2){ //XZ Plane
              u_proj.first=ux;
                  u_proj.second=uz;
                  v_proj.first=vx;
                  v_proj.second=vz;
            }
            else if(plane==3){ //isometric view
              u_proj.first= (std::sqrt(3) * ux -  std::sqrt(3) * uz)/ std::sqrt(6);
              u_proj.second=  (ux + 2*uy + uz)/ std::sqrt(6);
              v_proj.first= (std::sqrt(3) * vx -  std::sqrt(3) * vz)/ std::sqrt(6);
              v_proj.second=  (vx + 2*vy + vz)/ std::sqrt(6);
            }
            e.vertices.first=u_proj;
            e.vertices.second=v_proj;
//                edgeSet2D.insert(u,v);
 edgeSet2D.insert(e);
            }


}

Fig3D Fig3D::getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff){
        /** get transformed 3D object */
        Fig3D newFig;

        double sinXrot= sin(Xrot * PI/180 ),cosXrot= cos(Xrot * PI/180 );
        double sinYrot= sin(Yrot * PI/180 ),cosYrot= cos(Yrot * PI/180 );
        double sinZrot= sin(Zrot * PI/180 ),cosZrot= cos(Zrot * PI/180 );

        double transformationMat[4][4]={{cosYrot * cosZrot, cosXrot * sinZrot +sinXrot*sinYrot*cosZrot,sinXrot*sinZrot-cosXrot*sinYrot*cosZrot,Xoff},
                                        {-1*cosYrot*sinZrot,cosXrot*cosZrot-sinXrot*sinYrot*sinZrot,sinXrot*cosZrot+cosXrot*sinYrot*sinZrot,Yoff},
                                        {sinYrot,-1*sinXrot*cosYrot,cosXrot*cosYrot,Zoff},
                                        {0,0,0,1}};

        printf("TEST");
        for(int i = 0; i < 4; ++i){

            for(int j = 0; j < 4; ++j){
                printf ("%f ",transformationMat[i][j]);
            }
            printf("\n");
        }


        double matA[4][1],result[4][1];
        matA[3][0]=1;
        newFig.faces = this->faces;

        for(int m=0; m<vertices.size(); m++) {

              matA[0][0]=vertices[m].first;
              matA[0][1]=vertices[m].second;
              matA[0][2]=vertices[m].third;

                for(int i = 0; i < 4; ++i)
                        for(int j = 0; j < 1; ++j)

                                {  result[i][j]=0;
                                for(int k = 0; k < 4; ++k)
                                {
                                        result[i][j] += transformationMat[i][k] * matA[k][j];
                                }
                        }
              Vertice v;
              v.first=result[0][0];
              v.second=result[1][0];
              v.third=result[2][0];
              newFig.vertices.push_back(v);

//              printf ("v first is %f",result[0][0]);
        }

        return newFig;
}

