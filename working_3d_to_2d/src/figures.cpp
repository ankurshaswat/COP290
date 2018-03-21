#include "figures.h"
#include <math.h>
#include <set>
#include "basicComponents.h"
#include <vector>
#include "objLoader.h"
#include "stdio.h"
#include "helperfunctions.h"

void Fig3D::getProjections(int plane, set<Edge> & edgeSet2D) {
        /** get XY, YZ , XZ and isometric projections  of the 3D object*/
        set<Edge> edgeSet3D;
        get_edges3D(this->vertices, this->faces,edgeSet3D);
        for(auto it:edgeSet3D) {
                Vertice u=it.vertices.first, v=it.vertices.second, u_proj, v_proj;
                u_proj.is3d=false;
                v_proj.is3d=false;
                double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
                Edge e;
                if(plane==0) { //XY Plane
                        u_proj.first=ux;
                        u_proj.second=uy;
                        v_proj.first=vx;
                        v_proj.second=vy;
                }
                else if(plane==1) { //YZ Plane
                        u_proj.first=uy;
                        u_proj.second=uz;
                        v_proj.first=vy;
                        v_proj.second=vz;
                }
                else if(plane==2) { //XZ Plane
                        u_proj.first=ux;
                        u_proj.second=uz;
                        v_proj.first=vx;
                        v_proj.second=vz;
                }
                else if(plane==3) { //isometric view
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

void Fig3D::getAxes(int plane, set<Edge> & edgeSet2D) {
        /** get XY, YZ , XZ and isometric projections  of the 3D object*/
        set<Edge> edgeSet3D;
        get_edges3D(this->vertices, this->faces,edgeSet3D);
//    for(auto it:edgeSet3D){
        Vertice u_proj, v_proj;
        u_proj.is3d=false;
        v_proj.is3d=false;
//                double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
        double ux=0, uy=0, uz=0, vx=0, vy=0, vz=100;
        Edge e;
        if(plane==0) {        //XY Plane
                u_proj.first=ux;
                u_proj.second=uy;
                v_proj.first=vx;
                v_proj.second=vy;
        }
        else if(plane==1) {    //YZ Plane
                u_proj.first=uy;
                u_proj.second=uz;
                v_proj.first=vy;
                v_proj.second=vz;
        }
        else if(plane==2) {    //XZ Plane
                u_proj.first=ux;
                u_proj.second=uz;
                v_proj.first=vx;
                v_proj.second=vz;
        }
        else if(plane==3) {    //isometric view
                u_proj.first= (std::sqrt(3) * ux -  std::sqrt(3) * uz)/ std::sqrt(6);
                u_proj.second=  (ux + 2*uy + uz)/ std::sqrt(6);
                v_proj.first= (std::sqrt(3) * vx -  std::sqrt(3) * vz)/ std::sqrt(6);
                v_proj.second=  (vx + 2*vy + vz)/ std::sqrt(6);
        }
        e.vertices.first=u_proj;
        e.vertices.second=v_proj;
//                edgeSet2D.insert(u,v);
        edgeSet2D.insert(e);

//  u=it.vertices.first, v=it.vertices.second, u_proj, v_proj;
        u_proj.is3d=false;
        v_proj.is3d=false;
// double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
        ux=0; uy=0; uz=0; vx=0; vy=100; vz=0;
// Edge e;
        if(plane==0) { //XY Plane
                u_proj.first=ux;
                u_proj.second=uy;
                v_proj.first=vx;
                v_proj.second=vy;
        }
        else if(plane==1) { //YZ Plane
                u_proj.first=uy;
                u_proj.second=uz;
                v_proj.first=vy;
                v_proj.second=vz;
        }
        else if(plane==2) { //XZ Plane
                u_proj.first=ux;
                u_proj.second=uz;
                v_proj.first=vx;
                v_proj.second=vz;
        }
        else if(plane==3) { //isometric view
                u_proj.first= (std::sqrt(3) * ux -  std::sqrt(3) * uz)/ std::sqrt(6);
                u_proj.second=  (ux + 2*uy + uz)/ std::sqrt(6);
                v_proj.first= (std::sqrt(3) * vx -  std::sqrt(3) * vz)/ std::sqrt(6);
                v_proj.second=  (vx + 2*vy + vz)/ std::sqrt(6);
        }
        e.vertices.first=u_proj;
        e.vertices.second=v_proj;
//                edgeSet2D.insert(u,v);
        edgeSet2D.insert(e);

//Vertice u=it.vertices.first, v=it.vertices.second, u_proj, v_proj;
        u_proj.is3d=false;
        v_proj.is3d=false;
//double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
        ux=0; uy=0; uz=0; vx=100; vy=0; vz=0;
//Edge e;
        if(plane==0) { //XY Plane
                u_proj.first=ux;
                u_proj.second=uy;
                v_proj.first=vx;
                v_proj.second=vy;
        }
        else if(plane==1) { //YZ Plane
                u_proj.first=uy;
                u_proj.second=uz;
                v_proj.first=vy;
                v_proj.second=vz;
        }
        else if(plane==2) { //XZ Plane
                u_proj.first=ux;
                u_proj.second=uz;
                v_proj.first=vx;
                v_proj.second=vz;
        }
        else if(plane==3) { //isometric view
                u_proj.first= (std::sqrt(3) * ux -  std::sqrt(3) * uz)/ std::sqrt(6);
                u_proj.second=  (ux + 2*uy + uz)/ std::sqrt(6);
                v_proj.first= (std::sqrt(3) * vx -  std::sqrt(3) * vz)/ std::sqrt(6);
                v_proj.second=  (vx + 2*vy + vz)/ std::sqrt(6);
        }
        e.vertices.first=u_proj;
        e.vertices.second=v_proj;
//                edgeSet2D.insert(u,v);
        edgeSet2D.insert(e);
//            }
}

Fig3D Fig3D::getTransformation(double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff){
        /** get transformed 3D object */
        Fig3D newFig;

        newFig.faces = this->faces;

        for(unsigned int m=0; m<vertices.size(); m++) {

                newFig.vertices.push_back(transform(vertices[m],Xrot,Yrot,Zrot,Xoff,Yoff,Zoff));

        }

        return newFig;
}
