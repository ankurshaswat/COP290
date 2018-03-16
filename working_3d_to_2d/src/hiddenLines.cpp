#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"

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
void render2DHidden(Fig3D & object3D,
        QPainter & painter,
		int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		){
        set<Edge> edgeSet3D;
        get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);
        



    }
