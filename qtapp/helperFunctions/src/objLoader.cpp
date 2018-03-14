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
	// std::vector<Vertice2D> & out_uvs,
	// std::vector<Vertice> & out_normals
	std::vector<std::vector<unsigned int>> & faces_vertices
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<Vertice> temp_vertices;
	// std::vector<glm::vec2> temp_uvs;
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
			temp_vertices.push_back(vertex);

		}else if ( strcmp( lineHeader, "vt" ) == 0 ){

      continue;
			// glm::vec2 uv;
			// fscanf(file, "%f %f\n", &uv.x, &uv.y );
			// uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			// temp_uvs.push_back(uv);
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
			// if (matches != 9){
			// 	printf("File can't be read by our simple parser :-( Try exporting with other options\n");
			// 	fclose(file);
			// 	return false;
			// }
			// vertexIndices.push_back(vertexIndex[1]);
			// vertexIndices.push_back(vertexIndex[2]);
			// uvIndices    .push_back(uvIndex[0]);
			// uvIndices    .push_back(uvIndex[1]);
			// uvIndices    .push_back(uvIndex[2]);
			// normalIndices.push_back(normalIndex[1]);
			// normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle

	for(unsigned int j=0;j<faces_vertices.size();j++){

		std::vector<unsigned int> vertexIndices;
		vertexIndices=faces_vertices[j];
		printf("%d,\n",j);
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		// unsigned int uvIndex = uvIndices[i];
		// unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vertice vertex = temp_vertices[ vertexIndex-1 ];
		vertex.is3d=true;
		// glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		// Vertice normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		printf("%f,%f,%f,\n",vertex.first,vertex.second,vertex.third);
		out_vertices.push_back(vertex);
		// out_uvs     .push_back(uv);
		// out_normals .push_back(normal);

	}

}

	fclose(file);

	return true;
};

std::set<Edge>& get_edges2D(
		std::vector<Vertice> & out_vertices,
		std::vector<std::vector<unsigned int>> & faces_vertices,
		int plane //0-XY, 1-YZ, 2-XZ
	)
{
	if(plane!=0 && plane!=1 && plane!=2){ //raise exception
		plane=0; 
	}
	std::vector<Vertice> vertices2D;
	for (auto it: out_vertices){
		Vertice temp= it;
		if (plane==0) vertices2D.push_back({temp.first,temp.second}); //XY
		else if(plane==1)	vertices2D.push_back({temp.second,temp.third}); //YZ
		else if(plane==2)	vertices2D.push_back({temp.first,temp.third}); //XZ
	}
	std::set<Edge> edgeSet;
	for(auto faceList: faces_vertices){
		for(auto vertexIndex=faceList.begin(); vertexIndex!=faceList.end();vertexIndex++) {
			unsigned int i=(*vertexIndex), j;
			if(vertexIndex!=faceList.end()) j= (*(std::next(vertexIndex,1)));
			else j=(* (faceList.begin()) );
			Vertice curr=vertices2D[i-1], next=vertices2D[j-1];
			Edge e,e_inv;
			e.vertices={next,curr};
			e_inv.vertices={curr,next};
			if(edgeSet.find(e)==edgeSet.end()) edgeSet.insert(e_inv);
			
		}

	}
	return edgeSet;
};
int main(){
	return 0;
}