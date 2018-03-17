/** Methods for rendering 3D object and diplaying 2D views (will use OpenGL and GTK libraries)*/
#ifndef HIDDENLINES_H
#define RENDERMETHODS_H

#include <QtUiTools>


#include "figures.h"



pair<int,Vertice> get_intersection(Edge a, Edge b); /** returns (1,point of intersection) if intersecting, (0,_) if overlapping and (-1,_) if parallel
													Both edges are 2D edges */

bool opposite_side(vector<Vertice> & faceVertices, Vertice a, Vertice b); /** returns true if a and b are on opposite side of plane formed by faceVertices
																		, false otherwise **/ 

Vertice back_proj(Vertice v , Edge e, int plane); /** returns vertex on 3D edge e whose projection is v */

Edge projected(Edge a, int plane); /** 2D projection of edge **/
void render2DHidden(Fig3D & object3D,
        QPainter & painter,
		int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		);
bool is_inside(Vertice v, set<Edge> edgeSet);


#endif
