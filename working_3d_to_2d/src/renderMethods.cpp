#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"

#include <QtUiTools>

#include <iostream>
#include <vector>
#include <set>
#include <cmath>



void render2D(Fig3D & object3D,
        QPainter & painter,
		int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		){	
		/** Takes input 3D object , QPainter object, othographic plane (XY /YZ/ XZ/isometric) 
		and draws the corresponding 2D view on the QPainter object */
		std::set<Edge> edgeSet2D;
        object3D.getProjections(plane,edgeSet2D);
		// getProjections(object3D,plane,edgeSet)

//		bool edges_extracted=get_edges3D(object3D.vertices,object3D.faces,edgeSet);
		int count=0;
        for(auto it:edgeSet2D){
			Vertice u=it.vertices.first;
			Vertice v=it.vertices.second;
			painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20); //will have to change this to fit any size of pixmap
			// cout<<u.first<<" "<<u.second<<" "<<u.third<<endl;
			// cout<<v.first<<" "<<v.second<<" "<<v.third<<endl<<endl;

			}


}



