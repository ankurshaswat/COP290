//#include "objloader.h"

//objLoader::objLoader()
//{

//}

#include "objLoader.h"
#include "figures.h"
//#include "basicComponents.h"
#include <set>
#include <vector>
#include <iterator>
#include <cstring>
#include <iostream>

Fig3D  loadOBJ(
        const char * path
        ){
        std::vector<Vertice> out_vertices;
        std::vector<std::vector<unsigned int> >  faces_vertices;
        Fig3D loaded_obj;
        printf("Loading OBJ file %s...\n", path);

        std::vector<Vertice> temp_vertices;
        std::vector<Vertice> temp_normals;


        FILE * file = fopen(path, "r");

        if( file == NULL ) {
                printf("Impossible to open the file ! Are you in the right path ?\n");
                getchar();
                return loaded_obj;
        }

        while( 1 ) {

                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                        break; // EOF = End Of File. Quit the loop.

                // else : parse lineHeader

                if ( strcmp( lineHeader, "v" ) == 0 ) {
                        // glm::vec3 vertex;
                        Vertice vertex;
                        fscanf(file, "%f %f %f\n", &vertex.first, &vertex.second, &vertex.third );
                        cout<<endl<<"VERTICE"<<" ";
                        cout<<vertex.first<<" "<<vertex.second<<" "<<vertex.third<<endl;
                        temp_vertices.push_back(vertex);

                }else if ( strcmp( lineHeader, "vt" ) == 0 ) {

                        continue;
                }else if ( strcmp( lineHeader, "vn" ) == 0 ) {

                        // glm::vec3 normal;
                        Vertice normal;
                        fscanf(file, "%f %f %f\n", &normal.first, &normal.first, &normal.first );
                        temp_normals.push_back(normal);
                }else if ( strcmp( lineHeader, "f" ) == 0 ) {

                        // std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex;
    unsigned int normalIndex;
                        std::vector<unsigned int> vertexIndices, normalIndices;

                        while(1) {
         fscanf(file, "%d//%d", &vertexIndex,  &normalIndex );
                                vertexIndices.push_back(vertexIndex);
                                char c = fgetc(file);
                                if(c=='\n') {
                                        break;
                                }
                                 normalIndices.push_back(normalIndex);
                        }


                        faces_vertices.push_back(vertexIndices);
                }else{
                        char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
                }

        }

        // For each vertex of each face

        for(unsigned int j=0; j<faces_vertices.size(); j++) {

                std::vector<unsigned int> vertexIndices;
                vertexIndices=faces_vertices[j];
                printf("%d,\n",j);
                for( auto it:temp_vertices ) {

                        // // Get the indices of its attributes
                        // unsigned int vertexIndex = vertexIndices[i];

                        // // Get the attributes thanks to the index
                        // Vertice vertex = temp_vertices[ vertexIndex-1 ];
                        // vertex.is3d=true;	//to indicate it is a 3d vertex


                        // // Put the attributes in buffers
                        // printf("%f,%f,%f,\n",vertex.first,vertex.second,vertex.third);
                        out_vertices.push_back(it);

                }

        }

        fclose(file);
        cout<<"loadOBJ done!!"<<endl;
        loaded_obj.vertices=out_vertices;
        loaded_obj.faces=faces_vertices;
        return loaded_obj;
}

bool get_edges3D(
        std::vector<Vertice> & vertices3D,
        std::vector<std::vector<unsigned int> > & faces_vertices,
        std::set<Edge> & edgeSet
        )
{

        for(auto faceList: faces_vertices) {
                // cout<<endl<<faceList.size()<<endl;
                for(auto vertexIndex=faceList.begin(); vertexIndex!=faceList.end(); vertexIndex++) {
                        unsigned int i=(*vertexIndex), j;
                        if( std::next(vertexIndex,1) != faceList.end() ) j= (*(std::next(vertexIndex,1)));
                        else j=(*(faceList.begin()) );
                        Vertice curr=vertices3D[i-1], next=vertices3D[j-1];
                        // printf("after");
                        Edge e,e_inv;
                        e.vertices={next,curr};
                        e_inv.vertices={curr,next};
                        if(edgeSet.find(e)==edgeSet.end() && edgeSet.find(e_inv)==edgeSet.end()) {
                                edgeSet.insert(e_inv);
                                // cout<<i<<" "<<j<<endl<<endl;
                        }
                }

        }
        return true;
};
