#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <basicComponents.h>
#include <glm/glm.hpp>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
	const char * path,
	std::vector<Vertice> & out_vertices,
	// std::vector<Vertice2D> & out_uvs,
	std::vector<Vertice> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
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
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
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
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			// std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex,  normalIndex;

      while(1){
        int matches = fscanf(file, "%d//%d", &vertexIndex,  &normalIndex );
        char c = fgetc(fp);
        if(c=='\n'){
          break;
        }
        vertexIndices.push_back(vertexIndex);
        normalIndices.push_back(normalIndex);
      }
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
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vertice vertex = temp_vertices[ vertexIndex-1 ];
		// glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		Vertice normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		// out_uvs     .push_back(uv);
		out_normals .push_back(normal);

	}
	fclose(file);
	return true;
}
