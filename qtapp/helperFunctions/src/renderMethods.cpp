#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"

#include <QtUiTools>

#include <iostream>
#include <vector>
#include <set>
#include <cmath>



void render2D(Fig3D object3D,
		QPainter painter,
		int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		){	
		/** Takes input 3D object , QPainter object, othographic plane (XY /YZ/ XZ/isometric) 
		and draws the corresponding 2D view on the QPainter object */
		std::set<Edge> edgeSet2D;
		// object3D.getProjections(plane,edgeSet);
		getProjections(object3D,plane,edgeSet)

		bool edges_extracted=get_edges3D(out_vertices,faces_vertices,edgeSet);
		int count=0;
		for(auto it:edgeSet){
			Vertice u=it.vertices.first;
			Vertice v=it.vertices.second;
			painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20); //will have to change this to fit any size of pixmap
			// cout<<u.first<<" "<<u.second<<" "<<u.third<<endl;
			// cout<<v.first<<" "<<v.second<<" "<<v.third<<endl<<endl;

			}


}

void getProjections(Fig3D object3D,int plane, set<Edge> & edgeSet2D) {
		set<Edge> edgeSet3D;
		get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);	
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
      			}
                e.vertices.first=u_proj;
      			e.vertices.second=v_proj;
               	edgeSet2D.insert(u,v);

            }


}