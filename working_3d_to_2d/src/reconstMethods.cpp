
#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"
#include <map>
#include "reconstMethods.h"
#include <iostream>

std::vector<std::vector<Edge> > readFile(const char * path){
        // the returned vector has corresponding data for 3 views (vector of length 3)

        std::vector<std::vector<Edge> >  edgeSet;

        printf("Loading TXT file %s...\n", path);


        FILE * file = fopen(path, "r");

        if( file == NULL ) {
                printf("Impossible to open the file ! Are you in the right path ?\n");
                getchar();
                return edgeSet;
        }


        std::vector<std::vector<Edge> > allEdges;
        for(int x=0; x<3; x++) {


                int nVertices,nEdges;
                fscanf(file, "%d %d\n",&nVertices,&nEdges);
                cout<<nVertices<<nEdges;
                // std::vector<vertex> firstViewVList;
                std::map<char, Vertice> firstViewVMap;

                for(int i = 0; i<nVertices; i++) {
                        Vertice vertex;
                        fscanf(file, "%f %f %c\n", &vertex.first, &vertex.second, &vertex.label );
                        firstViewVMap[vertex.label]=vertex;
                        // firstViewVList.push_back(vertex);
                }

                std::vector<Edge> edgeList;

                for(int i = 0; i<nEdges; i++) {
                        Edge e;
                        char v1,v2;
                        fscanf(file,"%c %c\n",&v1,&v2);
                        e.vertices.first=firstViewVMap[v1];
                        e.vertices.second=firstViewVMap[v2];
                        edgeList.push_back(e);
                }

                allEdges.push_back(edgeList);
                cout<<"edgeList size"<<edgeList.size()<<endl;
        }


        fclose(file);
        printf("Loading TXT file completed");
        return allEdges;
}


WireFrame constUniq3dEdges(vector<vector<Edge> > edgeSet){

        std::vector<Edge> final3dSet;

        for(unsigned int i=0; i<edgeSet[0].size(); i++) {

                Edge e,e1,e2,finalEdge;

                string l11,l12,l21,l22,l31,l32;

                bool b1=false,b2=false;
                e=edgeSet[0][i];
                l11=e.vertices.first.label;
                l12=e.vertices.second.label;

                for(unsigned int j=0; j<edgeSet[1].size(); j++) {
                        e1=edgeSet[1][j];
                        l21=e1.vertices.first.label;
                        l22=e1.vertices.second.label;

                        if(l11==l21 && l12==l22) {
                                b1=true;
                                finalEdge.vertices.first.is3d=true;
                                finalEdge.vertices.first.first=e.vertices.first.first;
                                finalEdge.vertices.first.second=e.vertices.first.second;
                                finalEdge.vertices.first.third=e1.vertices.first.second;

                                finalEdge.vertices.second.is3d=true;
                                finalEdge.vertices.second.first=e.vertices.second.first;
                                finalEdge.vertices.second.second=e.vertices.second.second;
                                finalEdge.vertices.second.third=e1.vertices.second.second;
                                break;
                        }else if(l11==l22 && l12==l21) {
                                b1=true;
                                finalEdge.vertices.first.is3d=true;
                                finalEdge.vertices.first.first=e.vertices.first.first;
                                finalEdge.vertices.first.second=e.vertices.first.second;
                                finalEdge.vertices.first.third=e1.vertices.second.second;

                                finalEdge.vertices.second.is3d=true;
                                finalEdge.vertices.second.first=e.vertices.second.first;
                                finalEdge.vertices.second.second=e.vertices.second.second;
                                finalEdge.vertices.second.third=e1.vertices.first.second;
                                break;
                        }else{
                                continue;
                        }

                }

                for(unsigned int j=0; j<edgeSet[2].size(); j++) {
                        e2=edgeSet[2][j];
                        l31=e2.vertices.first.label;
                        l32=e2.vertices.second.label;

                        if(l11==l31 && l12==l32) {
                                b2=true;
                                finalEdge.vertices.first.is3d=true;
                                finalEdge.vertices.first.first=e.vertices.first.first;
                                finalEdge.vertices.first.second=e.vertices.first.second;
                                finalEdge.vertices.first.third=e2.vertices.first.second;

                                finalEdge.vertices.second.is3d=true;
                                finalEdge.vertices.second.first=e.vertices.second.first;
                                finalEdge.vertices.second.second=e.vertices.second.second;
                                finalEdge.vertices.second.third=e2.vertices.second.second;
                                break;
                        }else if(l11==l32 && l12==l31) {
                                b2=true;
                                finalEdge.vertices.first.is3d=true;
                                finalEdge.vertices.first.first=e.vertices.first.first;
                                finalEdge.vertices.first.second=e.vertices.first.second;
                                finalEdge.vertices.first.third=e2.vertices.second.second;

                                finalEdge.vertices.second.is3d=true;
                                finalEdge.vertices.second.first=e.vertices.second.first;
                                finalEdge.vertices.second.second=e.vertices.second.second;
                                finalEdge.vertices.second.third=e2.vertices.first.second;
                                break;
                        }else{
                                continue;
                        }

                }

                if(b1 && b2) {
                        final3dSet.push_back(finalEdge);
                }

        }
        WireFrame wf;
        wf.edges=final3dSet;
        return wf;

}

// vector< vector<int> >  CoplanarEdges (vector<Edge> & edges){
//         vector< vector<int> > Coplanarlist;
//         for(int i=0;i<edges.size();i++){
//                 for(int j=i+1;j<edges.size();j++){
//                         if( coplanar(edges[i],edges[j]) ){
//                                 vector<int> coplanar;
//                                 coplanar.push_back(i);
//                                 coplanar.push_back(j);
//                                 for(int k=j+1;k<edges.size();k++){
//                                         if(coplanar(edges[i],edges[j],edges[k])
//                                 }
//                         };
//                 }
//         }


// };

