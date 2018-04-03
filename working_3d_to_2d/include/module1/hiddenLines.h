/** Methods for rendering 3D object and diplaying 2D views (will use OpenGL and GTK libraries)*/
#ifndef HIDDENLINES_H
#define RENDERMETHODS_H

#include <QtUiTools>


#include "figures.h"


/// Renders the figure and also marks lines as hidden where they are hidden by some plane.
void render2DHidden(Fig3D & object3D,QPainter & painter,int plane); // 0- XY, 1-YZ, 2-XZ , 3-isometric

 /** returns true if a and b are on opposite side of plane formed by faceVertices
  * , false otherwise 
  */
bool opposite_side(vector<Vertice> & faceVertices, Vertice a, Vertice b);

/** returns vertex on 3D edge e whose projection is v */
Vertice back_proj(Vertice v, Edge e, int plane);  


                    


#endif
