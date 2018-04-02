
#include "basicComponents.h"
#include "complexComponents.h"
#include "figures.h"
#include "structs.h"
#include "reconstMethods.h"
#include "helperfunctions.h"
#include <map>
#include <iostream>
#include <algorithm>

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
                        vertex.first*=20;
                        vertex.second*=20;
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

/** Returns coplanar sets of edges  of size>=3 (each coplanar set is represented as a list of edge indices) */
vector< vector<int> >  coplanarEdges (vector<Edge> & edges){
        vector< vector<int> > ans;
        for(int i=0;i<edges.size();i++){
                Vertice i1=edges[i].vertices.first.deepCopy(), i2= edges[i].vertices.second.deepCopy();
                for(int j=i+1;j<edges.size();j++){
                        Vertice j1=edges[j].vertices.first.deepCopy(),j2=edges[j].vertices.second.deepCopy(),z;
                        if(!(j1==i1) && !(j1==i2)) z=j1;     //Pick the vertice not in common with the edge
                        else z=j2;
                        Plane plane(i1,i2,z);
                        if(plane.onPlane(edges[j]) ){
                                vector<int> coplanar;
                                coplanar.push_back(i);
                                coplanar.push_back(j);
                                for(int k=j+1;k<edges.size();k++){
                                        if(plane.onPlane(edges[k])) coplanar.push_back(k);
                                }
                                if(coplanar.size()>=3){ 
                                        bool skip=false;
                                        for(auto it: ans) if (isSubset(coplanar, it)){
                                                                skip=true;
                                                                break;
                                                                };
                                        if(skip) continue;
                                        ans.push_back(coplanar);
                                }
                        };
                }
        }
        cout<<"EDGES-"<<endl;
        for (auto i: edges){
                cout<<i.vertices.first<<i.vertices.second<<endl;
        }
        for(auto i:ans){        //debugging
                cout<<"NEXT"<<endl;
                for(auto j:i){
                        cout<<j<<" ";
                }
                cout<<endl;
                vector< vector<int> > edgeCycles= getEdgeLoops(edges, i);
                cout<<"EDGE CYCLE"<<endl;
                for(auto j:edgeCycles){
                        for(auto k:j) cout<<k<<" ";
                        cout<<endl;
                }

        }
        return ans;
};

/** takes input a set of coplanar edges (as edges + indices) and returns a list of edge loops(candidate faces) 
 formed using these edges (each edgeLoop is represented by a list of indices)*/
vector< vector<int>>  getEdgeLoops(vector<Edge> & edges, vector<int> coplanarIndices){
        //Construct graph represented as an adjacency list
        vector< vector<int> > adjlist;
        int n=coplanarIndices.size();
        adjlist.resize(n);
        cout<<n<<endl;
        for(int i=0;i<n;i++){
                Edge e=edges[coplanarIndices[i]];
                Vertice e1=e.vertices.first, e2=e.vertices.second;
                for(int j=0;j<n;j++){
                        if(j==i) continue;
                        Edge f= edges[coplanarIndices[j]];
                        Vertice f1=f.vertices.first, f2=f.vertices.second; 
                        if(e1==f1 || e1 == f2 || e2==f1 || e2==f2 ){ //Check if edges e and f are connected
                                adjlist[i].push_back(j);
                        }
                }
        }
        cout<<"ADJ LIST"<<endl;
        for(auto it:adjlist){
                for(auto j:it){
                        cout<<j<<" ";
                }
                cout<<endl;
        }

        /*Assuming every edge in the graph is a part of a cycle (disjoint from other cycles), 
         a simple traversal to find connected components will give us the cycles in order*/
        vector< bool > visited;
        visited.resize(n,false);
        vector< vector<int> > ans;
        for(int i=0;i<n;i++){
                if(!visited[i]){
                        visited[i]=true;
                        vector<int> cycle;
                        cycle.push_back( coplanarIndices[i] );
                        int j= adjlist[i][0];
                        int count=1;
                        while(j!=i){
                                visited[j]=true;
                                cycle.push_back( coplanarIndices[j] );
                                count++;
                                int temp=j;
                                for(auto it: adjlist[temp]){
                                        if(!visited[it] || (it==i && count>2) ){
                                                j=it;
                                                break;
                                        }
                                }
                        }
                        ans.push_back(cycle);
                }
        }
         
        return ans;
};

Fig3D wireframeTo3D(WireFrame a){
        vector< vector<int> > coplanarSets= coplanarEdges(a.edges);
        vector< pair<int,int> > edge2vertexMap;
        edge2vertexMap.resize(a.edges.size());
        vector<Vertice> vertices;
        vector< vector<unsigned int> > faces;
        cout<<"PRINTING VERTICES"<<endl;
        for(int index=0;index<a.edges.size();index++){
                Edge e=a.edges[index];
                cout<<e.vertices.first<<e.vertices.second<<endl;
                int pos1= verticePresent(vertices, e.vertices.first);
                int pos2= verticePresent(vertices, e.vertices.second);
                if(pos1==-1){
                        vertices.push_back(e.vertices.first.deepCopy());
                        pos1=vertices.size()-1;
                }
                if(pos2==-1){
                        vertices.push_back(e.vertices.second.deepCopy());
                        pos2=vertices.size()-1;
                }
                edge2vertexMap[index]={pos1+1,pos2+1}; //1-indexing
        }
        for(auto it: coplanarSets){
                vector< vector<int>> edgeLoops=getEdgeLoops(a.edges, it );
                for(auto loop: edgeLoops){
                        vector<unsigned int>  faceVertices;
                        int v1,v2;
                        v1=edge2vertexMap[0].first;
                        v2=edge2vertexMap[0].second;
                        if(v1==edge2vertexMap[1].first || v2==edge2vertexMap[1].second){ //to ensure the vertices are in cyclic order
                                faceVertices.push_back(v2);
                                faceVertices.push_back(v1);
                        }
                        else{
                             faceVertices.push_back(v1);
                             faceVertices.push_back(v2);   
                        }
                        for(int i=2;i<loop.size();i++){
                                int index=loop[i];
                                Edge e=a.edges[index];
                                v1=edge2vertexMap[index].first;
                                v2=edge2vertexMap[index].second;
                                if( find(faceVertices.begin(), faceVertices.end(),v1)==faceVertices.end()  ) faceVertices.push_back(v1);
                                else if( find(faceVertices.begin(), faceVertices.end(),v2)==faceVertices.end()  ) faceVertices.push_back(v2);
                        }
                        faces.push_back(faceVertices);
                }
        }

        Fig3D ans;
        ans.vertices=vertices;
        ans.faces=faces;
        cout<<"3D object debugging"<<endl<<"VERTICES"<<endl;
        for(auto it:vertices){
                cout<<it;
        }
        cout<<"FACES"<<endl;
        for(auto it:faces){
                cout<<endl;
                for(auto j: it) cout<<j<<" ";
        }
        return ans;
};




