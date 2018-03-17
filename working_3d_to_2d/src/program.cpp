/** @file program.cpp
   @author Lastname:Firstname:A00123456:cscxxxxx
   @version Revision 1.0
   @brief Main file documentation.
   @details Main File
   @date Monday, March 5, 2018
 */

/**
   @mainpage
   This is the main file of the program. This will be used to launch the interface to select files and other things. Refer to class list
   for detailed description of other classes.
 */



#include <iostream>
using namespace std;
#include "basicComponents.h"
#include <vector>
#include <set>
#include <iostream>
int main2()
{
								std::vector<Vertice> & out_vertices;
								std::vector<std::vector<unsigned int> > & faces_vertices;
								bool res=loadOBJ(out_vertices,faces_vertices,"./test.obj");
								if(res) {
																std::set<Edge> edgeSet;
																edgeSet=get_edges2D(out_vertices,faces_vertices,0);
																for(auto it:edgeSet) {
																								Vertice u=it.vertices.first;
																								Vertice v=it.vertices.second;
																								cout<<u.first<<" "<<u.second<<endl;
																								cout<<v.first<<" "<<v.second<<endl<<endl;
																}
								}

								return 0;
}
