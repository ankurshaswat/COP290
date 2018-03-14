#include "objLoader.h"
#include "basicComponents.h"
#include<set>
#include<vector>
#include<iterator>
#include<cstring>
#include<iostream>

bool loadOBJ(
	const char * path,
	std::vector<Vertice> & out_vertices,
	std::vector<std::vector<unsigned int>> & faces_vertices
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<Vertice> temp_vertices;
	std::vector<Vertice> temp_normals;


	FILE * file = fopen(path, "r");

	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
			// glm::vec3 vertex;
      Vertice vertex;
			fscanf(file, "%f %f %f\n", &vertex.first, &vertex.second, &vertex.third );
			cout<<endl<<"VERTICE"<<" ";
			cout<<vertex.first<<" "<<vertex.second<<" "<<vertex.third<<endl;
			temp_vertices.push_back(vertex);

		}else if ( strcmp( lineHeader, "vt" ) == 0 ){

      continue;
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){

			// glm::vec3 normal;
      Vertice normal;
			fscanf(file, "%f %f %f\n", &normal.first, &normal.first, &normal.first );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){

			// std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex,  normalIndex;
			std::vector<unsigned int> vertexIndices, normalIndices;

      while(1){
        int matches = fscanf(file, "%d//%d", &vertexIndex,  &normalIndex );
				vertexIndices.push_back(vertexIndex);
        char c = fgetc(file);
        if(c=='\n'){
          break;
        }
        // normalIndices.push_back(normalIndex);
      }


			faces_vertices.push_back(vertexIndices);
		}else{
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each face

	for(unsigned int j=0;j<faces_vertices.size();j++){

		std::vector<unsigned int> vertexIndices;
		vertexIndices=faces_vertices[j];
		printf("%d,\n",j);
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
	
		// Get the attributes thanks to the index
		Vertice vertex = temp_vertices[ vertexIndex-1 ];
		vertex.is3d=true;	//to indicate it is a 3d vertex
		

		// Put the attributes in buffers
		printf("%f,%f,%f,\n",vertex.first,vertex.second,vertex.third);
		out_vertices.push_back(vertex);
		
	}

}

	fclose(file);
	cout<<"loadOBJ done!!"<<endl;
	return true;
};

 bool get_edges3D(
		std::vector<Vertice> & vertices3D,
		std::vector<std::vector<unsigned int>> & faces_vertices,
		std::set<Edge> & edgeSet 
	)
{
	
	for(auto faceList: faces_vertices){
		cout<<faceList.size()<<endl;
		for(auto vertexIndex=faceList.begin(); vertexIndex!=faceList.end();vertexIndex++) {
			unsigned int i=(*vertexIndex), j;
			cout<<"HERE"<<" ";
			cout<<*vertexIndex<<endl;
			if( std::next(vertexIndex,1) != faceList.end() ) j= (*(std::next(vertexIndex,1)));
			else j=(* (faceList.begin()) );
			cout<<"i,j="<<i<<","<<j<<endl;
			Vertice curr=vertices3D[i-1], next=vertices3D[j-1];
			Edge e,e_inv;
			e.vertices={next,curr};
			e_inv.vertices={curr,next};
			if(edgeSet.find(e)==edgeSet.end()) edgeSet.insert(e_inv);
			cout<<"e -"<<edgeSet.size()<<endl;		
		}
		
	}
	cout<<"DONE"<<endl;
	return true;
};
