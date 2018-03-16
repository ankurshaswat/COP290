#ifndef OBJLOADER_H
#define OBJLOADER_H
#include<set>
#include<vector>
#include "basicComponents.h"
#include "figures.h"

Fig3D  loadOBJ(
        const char * path
//        std::vector<Vertice> & out_vertices,
//        std::vector<std::vector<unsigned int>> & faces_vertices
);
bool get_edges3D(
        std::vector<Vertice> & out_vertices,
        std::vector<std::vector<unsigned int>> & faces_vertices,
        // int plane, //0-XY, 1-YZ, 2-XZ
        std::set<Edge>& edgeSet
    );

#endif
