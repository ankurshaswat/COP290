#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"
#include "hiddenLines.h"
#include "helperfunctions.h"
#include <stdio.h>
 #include <QtUiTools>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#define INF 1000000
#define epsilon 0.1




/** returns true if a and b are on opposite side of plane formed by faceVertices
           , false otherwise **/
bool opposite_side(vector<Vertice> & faceVertices, Vertice e, Vertice f){
        Plane plane(faceVertices[0],faceVertices[1],faceVertices[2]);
        if(plane.distance(e)<0.01 || plane.distance(f)<0.01) return false; //on plane (allow for some error correction)
        float d1=(plane.a*e.first + plane.b*e.second + plane.c*e.third + plane.d);
        float d2=(plane.a*f.first + plane.b*f.second + plane.c*f.third + plane.d); 
        // if( abs(d1/x)<0.01 || abs(d2/x)<0.01) return false;
        if( d1 * d2 <0) return true;
        else return false;


}

/**returns 3D vertex on Edge e whose projection is v**/
Vertice back_proj(Vertice v, Edge e, int plane){
        Vertice a=e.vertices.first, b= e.vertices.second, ans;
        float x1=a.first,x2=b.first, y1=a.second, y2=b.second, z1=a.third, z2=b.third;
        float x,y,z;
        if(plane==0) { //revert XY projection
                cout<<"BACK_PROJ e- "<<endl;
                // cout<<(a.first)<<", "<<(a.second)<<", "<<(a.third)<<endl;
                // cout<<(b.first)<<", "<<(b.second)<<", "<<(b.third)<<endl;
                cout<<a<<b;
                ans.first=v.first;
                ans.second=v.second;
                x=v.first;
                y=v.second;
                if(y1!=y2) {
                        ans.third=(z1*(y2-y) + z2*(y-y1))/(y2-y1);
                }
                else if(x1!=x2) {
                        ans.third=(z1*(x2-x) + z2*(x-x1))/(x2-x1);
                }
                else{
                        ans.third=a.third; //this case means a and b are coinciding in the projection, so does not matter if it is hidden or not
                }
                cout<<"BACK_PROJ v-"<<endl;
                cout<<ans<<endl;
        }
        else if(plane==1) { //revert YZ projection
                ans.second=v.first;
                ans.third=v.second;
                y=v.first;
                z=v.second;
                if(y1!=y2) {
                        ans.first=(x1*(y2-y) + x2*(y-y1))/(y2-y1);
                }
                else if(z1!=z2) {
                        ans.first=(x1*(z2-z) + x2*(z-z1))/(z2-z1);
                }
                else{
                        ans.first=a.first; //this case means a and b are coinciding in the projection, so does not matter if it is hidden or not
                }

        }
        else if(plane==2) { //revert XZ projection
                ans.first=v.first;
                ans.third=v.second;
                x=v.first;
                z=v.second;
                if(x1!=x2) {
                        ans.second=(y1*(x2-x) + y2*(x-x1))/(x2-x1);
                }
                else if(z1!=z2) {
                        ans.second=(y1*(z2-z) + y2*(z-z1))/(z2-z1);
                }
                else{
                        ans.second=a.second; //this case means a and b are coinciding in the projection, so does not matter if it is hidden or not
                }
        }
        else if(plane==3) { //revert isometric projection
                ans=a; //TODO
        }
        return ans;
}

/**Returns Vertex at infinity for the corresponding projection plane (to check if a vertex and our view point lie on opposite side of a face)**/
Vertice get_vertex_inf(Vertice x,int plane){
        Vertice ret;
        ret.is3d=true;
        if(plane==0) { //point from which XY view is taken
                // ret.first=1;
                // ret.second=1;
                ret.first=x.first;
                ret.second=x.second;
                ret.third=-INF;
        }
        else if(plane==1) {//point from which YZ view is taken
                ret.first=-INF;
                ret.second=x.first;
                ret.third=x.second;
        }
        else if(plane==2) {//point from which XZ view is taken
                ret.first=x.first;
                ret.second=-INF;
                ret.third=x.third;
        }
        else if(plane==3) {
                ret.first=-INF;
                ret.second=-INF;
                ret.third=INF;
        }
        return ret;
};


void render2DHidden(Fig3D & object3D,QPainter & painter,int plane ){// 0- XY, 1-YZ, 2-XZ , 3-isometric
        set<Edge> edgeSet3D;
        get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);
        bool istesting=false;
        for (auto e: edgeSet3D) {
                vector< pair<Vertice,int> > hiddenEdgeSet;
                Edge e_proj= e.projected(plane);
                for(auto face: object3D.faces) {
                        if(plane==0 && !istesting) cout<<"START"<<endl;
                        set<Edge> faceEdgeSet3D;
                        vector< vector<unsigned int> > tmpfaces;
                        tmpfaces.push_back(face);
                        get_edges3D(object3D.vertices,tmpfaces,faceEdgeSet3D);
                        vector<Vertice> overlapEndPoints;
                        bool is_overlapping=false;
                        for(auto faceEdge: faceEdgeSet3D) {
                                pair<int,Vertice> ret= get_intersection(e_proj, faceEdge.projected(plane) );
                                if(ret.first==1){ 
                                        overlapEndPoints.push_back(ret.second);
                                        if(plane==0 && !istesting) cout<<"OVERLAP ###### "<<(ret.second.first)<<", "<<(ret.second.second)<<endl;
                                }
                                else if(ret.first==0) { //overlapping
                                        if(faceEdge==e) {
                                                is_overlapping=true;
                                                if(plane==0 && !istesting) cout<<"SAME FACE, SKIP!!!!!"<<endl;
                                        }
                                        overlapEndPoints.clear();
                                        break;
                                }
                        }
                        if(is_overlapping) continue;
                        set<Vertice> removeDuplicates;
                        for(auto it: overlapEndPoints){
                                removeDuplicates.insert(it.deepCopy());
                        }
                        overlapEndPoints.clear();
                        for(auto it: removeDuplicates){
                                if(verticePresent(overlapEndPoints, it)==-1){ 
                                        if(plane==0 && !istesting) cout<<"FINAL OVERLAP #####"<<it;
                                        overlapEndPoints.push_back(it.deepCopy());
                                }
                        }

                        set<Edge> faceEdgeSet2D;
                        for(auto it: faceEdgeSet3D){
                                faceEdgeSet2D.insert(it.projected(plane));
                            }
                        
                        vector<Vertice> faceVertices;
                        faceVertices.push_back(object3D.vertices[face[0]-1]);
                        faceVertices.push_back(object3D.vertices[face[1]-1]);
                        faceVertices.push_back(object3D.vertices[face[2]-1]);
                       
                        // set< pair<Vertice,int> > hiddenEdgeSet;
                        if(overlapEndPoints.size()==2) {
                                if(plane==0 && !istesting) cout<<"2 points"<<endl;
                                Vertice u=overlapEndPoints[0],v=overlapEndPoints[1];
                                u.is3d=false;
                                v.is3d=false;
                                Vertice u_corr=back_proj(u,e,plane), v_corr=back_proj(v,e,plane);
                                if (opposite_side(faceVertices,u_corr,get_vertex_inf(u_corr,plane))  ||  opposite_side(faceVertices,v_corr,get_vertex_inf(v_corr,plane)) ){
                                    if(u<v){
                                        // hiddenEdgeSet.insert({u,0});
                                        // hiddenEdgeSet.insert({v,1});
                                        hiddenEdgeSet.push_back({u,0});
                                        hiddenEdgeSet.push_back({v,1});
                                    }
                                    else{
                                        // hiddenEdgeSet.insert({u,1});
                                        // hiddenEdgeSet.insert({v,0});
                                        hiddenEdgeSet.push_back({u,1});
                                        hiddenEdgeSet.push_back({v,0});

                                    }
                                if(plane==0 && !istesting) {
                                          cout<<"2 points OPPOSITE SIDE!!"<<endl;
                                          cout<<faceVertices[0]<<faceVertices[1]<<faceVertices[2]<<endl;
                                }
                                //check if back_proj(u,e) and (v.first,v.second,inf) are on opposite sides of plane or not
                                //if they are, u-v edge is obstructed from view
                                //if u<v set add <u,START> and <v,END> to hiddenEdgeSet (vice versa for v<u)
                                    }
                                else{
                                     if(plane==0 && !istesting){
                                                cout<<"2 points SAME SIDE!!"<<endl;
                                                cout<<faceVertices[0]<<faceVertices[1]<<faceVertices[2]<<endl;
                                     }
                                }
                        }
                        else if(overlapEndPoints.size()==1) {
                            if(plane==0 && !istesting) cout<<"1 point"<<endl;
                            Vertice u=overlapEndPoints[0],v;
                            Vertice u_corr=back_proj(u,e,plane);
                            u.is3d=false;
                            v.is3d=false;
                            if(is_inside(e_proj.vertices.first,faceEdgeSet2D) && !(u==e_proj.vertices.first) ) {
                                    v=e_proj.vertices.first;
                                    if(plane==0 && !istesting){
                                    cout<<"VERTEX INSIDE!!"<<endl;
                                    cout<<v.first+50<<", "<<v.second+50<<endl<<endl;
                                    for(auto it: faceEdgeSet2D){
                                                std::cout<<(it.vertices.first)<<(it.vertices.second)<<endl;
                                        }
                                     cout<<endl;
                                   }
                            }
                            else if (is_inside(e_proj.vertices.second,faceEdgeSet2D) && !(u==e_proj.vertices.second) ){
                                    v=e_proj.vertices.second;
                                    if(plane==0 && !istesting){
                                    cout<<"VERTEX INSIDE!!"<<endl;
                                    cout<<v.first+50<<", "<<v.second+50<<endl<<endl;
                                    for(auto it: faceEdgeSet2D){
                                                std::cout<<(it.vertices.first)<<(it.vertices.second)<<endl;
                                        }
                                     cout<<endl;
                                   }
                            }
                            else{
                                    continue;
                            }
                            Vertice v_corr=back_proj(v,e,plane);
                            if ( !opposite_side(faceVertices,v_corr,get_vertex_inf(v,plane)) ){
                                if(plane==0 && !istesting){
                                         cout<<"SAME SIDE :(:(:(:(:(:(:("<<endl; 
                                         cout<<"Point 2D- "<<v<<endl;
                                         cout<<"Point 3D- "<<v_corr<<endl;
                                         cout<<"Vertices- "<<endl;
                                         for(auto it: faceVertices){
                                                 cout<<it<<endl;
                                         }       
                                }
                                
                                break;
                            }
                            else{
                                    if(plane==0 && !istesting){
                                        cout<<"OPPOSITE SIDE !_!_!_!_!_!_!_"<<endl;
                                        cout<<"Point 2D- "<<v<<endl;
                                        cout<<"Point 3D- "<<v_corr<<endl;
                                        cout<<"Vertices- "<<endl;
                                        for(auto it: faceVertices){
                                                cout<<it<<endl;
                                        }   
                                    }
                            }
                            if(u<v){
                            // hiddenEdgeSet.insert({u,0});
                            // hiddenEdgeSet.insert({v,1});
                                hiddenEdgeSet.push_back({u,0});
                                hiddenEdgeSet.push_back({v,1});
                            }
                            else{
                        //     hiddenEdgeSet.insert({u,1});
                        //     hiddenEdgeSet.insert({v,0});
                                hiddenEdgeSet.push_back({u,1});
                                hiddenEdgeSet.push_back({v,0});
                            }
                        }
                        else if(overlapEndPoints.size()==0){
                                if(plane==0 && !istesting) cout<<"0 points"<<endl;
                                Vertice u=e_proj.vertices.first.deepCopy(),v= e_proj.vertices.second.deepCopy();
                                Vertice midpoint;
                                midpoint.first=(u.first+v.first)/2;
                                midpoint.second=(u.second+v.second)/2;
                                midpoint.is3d=false;
                                if( is_inside(midpoint,faceEdgeSet2D) ){
                                        if (opposite_side(faceVertices,e.vertices.first,get_vertex_inf(e.vertices.first,plane))  
                                        &&  opposite_side(faceVertices,e.vertices.second,get_vertex_inf(e.vertices.second,plane)) ){
                                                if(u<v){
                                                // hiddenEdgeSet.insert({u,0});
                                                // hiddenEdgeSet.insert({v,1});
                                                hiddenEdgeSet.push_back({u,0});
                                                hiddenEdgeSet.push_back({v,1});
                                                }
                                                else{
                                                //     hiddenEdgeSet.insert({u,1});
                                                //     hiddenEdgeSet.insert({v,0});
                                                hiddenEdgeSet.push_back({u,1});
                                                hiddenEdgeSet.push_back({v,0});
                                                }       
                                                if(plane==0 && !istesting) cout<<"Inside, OPPOSITE"<<endl;
                                        }
                                        else{
                                                if(plane==0 && !istesting) cout<<"Inside, SAME"<<endl;
                                        }

                                }
                                else{
                                        if(plane==0 && !istesting) cout<<"Not inside"<<endl;
                                }
                        }
                        if(plane==0 && !istesting){
                                Vertice e_proj1=e_proj.vertices.first, e_proj2=e_proj.vertices.second;
                                cout<<"Edge proj-------------------------------------------------------"<<endl;
                                cout<<e_proj1<<endl;
                                cout<<e_proj2<<endl;
                        }
                        
                        if(hiddenEdgeSet.size()!=0 && plane==0 && !istesting){
                            cout<<"hiddenEdgeSet size for plane xxxxxxxxxxxxxxxxxxxxxxxxx "<<plane<<" "<<hiddenEdgeSet.size()<<endl;
                            for(auto it: hiddenEdgeSet){
                                // Vertice u=it.first;
                                cout<<it.first<<" "<<it.second<<endl;
                            }
                        
                            cout<<"Face edges-"<<endl;
                        }
                        // if(plane==0) cout<<"Face edges- "<<endl;
                        // Vertice u=e_proj.vertices.first;
                        // Vertice v=e_proj.vertices.second;
                        // painter.drawLine((u.first + 2)*20, (u.second ), (v.first + 2)*20, (v.second ));
                        for(auto it:faceEdgeSet2D) {
                            Vertice u=it.vertices.first;
                            Vertice v=it.vertices.second;
                        //     painter.drawLine((u.first + 2)*20, (u.second ), (v.first + 2)*20, (v.second )); //will have to change this to fit any size of pixmap
                            if(plane==0 && !istesting){
                                    cout<<u<<endl;
                                    cout<<v<<endl;
                            }
                        }
                    }
                    if(plane==0 && !istesting) cout<<"EDGE DONE!!!"<<endl;
                     
                    Vertice u=e_proj.vertices.first;
                    Vertice v=e_proj.vertices.second;
                //     painter.drawLine((u.first + 2)*20, (u.second ), (v.first + 2)*20, (v.second ));
                    if(v<u){
                        u=e_proj.vertices.second;
                        v=e_proj.vertices.first;
                    }
                    int startCount=0, endCount=0;
                    QPen Plain((QColor(255,0,0)),1);
                    Plain.setStyle(Qt::SolidLine);
                    QPen Hidden((QColor(255,0,0)),1);
                    Hidden.setStyle(Qt::DotLine);
                    painter.setPen(Plain);
                    QPen linepen(Qt::blue);
                    linepen.setCapStyle(Qt::RoundCap);
                    linepen.setWidth(5);
                    std::sort(hiddenEdgeSet.begin(),hiddenEdgeSet.end());
                    for(auto it: hiddenEdgeSet){    
                        Vertice temp=it.first;
                        painter.setPen(linepen);
                        //  if(plane==0 && !istesting){
                        //         painter.drawPoint((temp.first+50), (temp.second+50) );
                        //  }
                        if(endCount>=startCount) { 
                                if(plane==0 && !istesting){
                                    cout<<"SOLID ***********************************"<<endl;
                                    cout<<u<<endl;
                                    cout<<temp<<endl;
                                }
                                painter.setPen(Plain);
                                painter.drawLine((u.first+50), (u.second +50), (temp.first+50), (temp.second +50));
                        }
                        else{
                              if(plane==0 && !istesting){
                                  cout<<"HIDDEN ***********************************"<<endl;
                                  cout<<u<<endl;
                                  cout<<temp<<endl;
                               }

                              painter.setPen(Hidden);
                              painter.drawLine((u.first + 50), (u.second + 50 ), (temp.first + 50), (temp.second + 50  ));  
                        }
                        if(it.second==0){    
                        startCount++;
                        }                    
                        else{
                        endCount++;        
                        }
                        u=temp;
                    }
                    if(plane==0 && !istesting){
                    cout<<"Final :::"<<endl;
                    cout<<u<<endl;
                    cout<<v<<endl;
                    }
                    painter.setPen(Plain);
                    painter.drawLine((u.first)+50, (u.second)+50, (v.first)+50, (v.second )+50);
                //     istesting=true;    

                }
};

