#include "basicComponents.h"
#include "objLoader.h"

#include <QtUiTools>

#include <iostream>
#include <vector>
#include <set>



void render2D(std::vector<Vertice> & out_vertices,
		std::vector<std::vector<unsigned int>> & faces_vertices,	//Might change this to a Fig3D object later on,
		QPainter painter,
		int plane // 0- XY, 1-YZ, 2-XZ 
		){	
		/** Takes input 3D object information (vertices,faces), QPainter object, othographic plane (XY /YZ/ XZ) 
		and draws the corresponding 2D view on the QPainter object */
		if(res){
			std::set<Edge> edgeSet;
			bool edges_extracted=get_edges3D(out_vertices,faces_vertices,edgeSet);
			int count=0;
			for(auto it:edgeSet){
				Vertice u=it.vertices.first;
				Vertice v=it.vertices.second;
				cout<<u.first<<" "<<u.second<<" "<<u.third<<endl;
				cout<<v.first<<" "<<v.second<<" "<<v.third<<endl<<endl;
			}
		}
	return 0;


}