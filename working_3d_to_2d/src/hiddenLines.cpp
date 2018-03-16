#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"

// #include <QtUiTools>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

pair<int,Vertice> get_intersection(Edge a, Edge b){
     /** returns (1,point of intersection) if intersecting, (0,_) if overlapping and (-1,_) if parallel
	Both edges are 2D edges */

}


bool opposite_side(vector<Vertice> & faceVertices, Vertice a, Vertice b){
     /** returns true if a and b are on opposite side of plane formed by faceVertices
      , false otherwise **/ 
    

}

Vertice back_proj(Vertice v , Edge e){

}

Edge projected(Edge a, int plane){ /** 2D projection of edge (might include as an Edge member function) **/
    Vertice u=a.vertices.first, v=a.vertices.second, u_proj, v_proj;
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
        return e;
}

void render2DHidden(Fig3D & object3D,QPainter & painter,int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		){
        set<Edge> edgeSet3D;
        get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);
        for (auto e: edgeSet3D){
            for(auto face: object3D.faces){
                Edge e_proj= projected(e,plane);
                set<Edge> faceEdgeSet3D;
                vector< vector<unsigned int> > tmpfaces;
                tmpfaces.push_back(face);
                get_edges3D(object3D.vertices,tmpfaces,faceEdgeSet3D);
                vector<Vertice> overlapEndPoints;
                for(auto faceEdge: faceEdgeSet3D){
                    pair<int,Vertice> ret= get_intersection(e_proj, projected(faceEdge,plane));    
                    if(ret.first==1) overlapEndPoints.push_back(ret.second);
                    else if(ret.first==0) {
                        overlapEndPoints.clear();
                        break;
                    }
                }
                if(overlapEndPoints.size()==2){
                    Vertice u=overlapEndPoints[0],v=overlapEndPoints[1];
                    //check if back_proj(u,e) and (v.first,v.second,inf) are on opposite sides of plane or not
                    //if they are, u-v edge is obstructed from view
                    //if u<v set add <u,START> and <v,END> to hiddenEdgeset (vice versa for v<u)
                }
                else if(overlapEndPoints.size()==1){
                    //find the end point that lies in the interior of the face
                    //repeat the previous procedure
                }


            }
        }



    }
