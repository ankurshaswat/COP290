#include "basicComponents.h"
#include "objLoader.h"
#include <iostream>
#include <vector>
#include <set>
#include<iostream>

int main(){

		std::vector<Vertice> out_vertices;
		std::vector<std::vector<unsigned int>> faces_vertices;
		bool res=loadOBJ("./test.obj",out_vertices,faces_vertices);
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