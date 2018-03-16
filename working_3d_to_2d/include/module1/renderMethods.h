/** Methods for rendering 3D object and diplaying 2D views (will use OpenGL and GTK libraries)*/
#ifndef RENDERMETHODS_H
#define RENDERMETHODS_H

#include <QtUiTools>


#include "figures.h"


void render(Fig3D a);


void render2D(Fig3D & object3D,
        QPainter & painter,
		int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
		);


#endif
