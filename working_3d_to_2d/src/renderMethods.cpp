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
              int plane, // 0- XY, 1-YZ, 2-XZ , 3-isometric,
              double scale_factor){
        /** Takes input 3D object , QPainter object, othographic plane (XY /YZ/ XZ/isometric)
           and draws the corresponding 2D view on the QPainter object */
        std::set<Edge> edgeSet2D;
        object3D.getProjections(plane,edgeSet2D);
        // getProjections(object3D,plane,edgeSet)

//		bool edges_extracted=get_edges3D(object3D.vertices,object3D.faces,edgeSet);
//		int count=0;
        for(auto it:edgeSet2D) {
                Vertice u=it.vertices.first;
                Vertice v=it.vertices.second;
                painter.drawLine((u.first )*scale_factor+ 150, (u.second )*scale_factor+150, (v.first )*scale_factor+ 150, (v.second )*scale_factor+150); //will have to change this to fit any size of pixmap
                // cout<<u.first<<" "<<u.second<<" "<<u.third<<endl;
                // cout<<v.first<<" "<<v.second<<" "<<v.third<<endl<<endl;

        }


}


void renderAxes(Fig3D & object3D,
                QPainter & painter,
                int plane, // 0- XY, 1-YZ, 2-XZ , 3-isometric
                double scale_factor){

        QPen Green((QColor(0,255,0)),1);
        painter.setPen(Green);
        std::set<Edge> edgeSet2D;
        object3D.getAxes(plane,edgeSet2D);
//    int count=0;
        for(auto it:edgeSet2D) {
                Vertice u=it.vertices.first;
                Vertice v=it.vertices.second;
                painter.drawLine((u.first + 150)*scale_factor, (u.second +150)*scale_factor, (v.first + 150)*scale_factor, (v.second +150)*scale_factor); //will have to change this to fit any size of pixmap
                // cout<<u.first<<" "<<u.second<<" "<<u.third<<endl;
                // cout<<v.first<<" "<<v.second<<" "<<v.third<<endl<<endl;

        }

}
