#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"
#include "hiddenLines.h"
#include <stdio.h>
 #include <QtUiTools>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#define INF 1000000

/** returns (1,point of intersection) if intersecting, (0,_) if overlapping and (-1,_) if parallel
   Both edges are 2D edges */
pair<int,Vertice> get_intersection(Edge a, Edge b){


        float x1,y1,x2,y2,x3,y3,x4,y4;
        float c2,c1,m2,m1;
        float numerator,denominator;
        Vertice intersection;
        intersection.is3d=false;

        x1=a.vertices.first.first;
        y1=a.vertices.first.second;
        x2=a.vertices.second.first;
        y2=a.vertices.second.second;
        x3=b.vertices.first.first;
        y3=b.vertices.first.second;
        x4=b.vertices.second.first;
        y4=b.vertices.second.second;


        c2=(x2-x1)*(y3*(x4-x3)-x3*(y4-y3));
        c1=(x4-x3)*(y1*(x2-x1)-x1*(y2-y1));
        m1=(y2-y1)*(x4-x3);
        m2=(y4-y3)*(x2-x1);

        numerator=c2-c1;
        denominator=m1-m2;

        if(numerator==0 && denominator==0) {
                return {0,intersection};
        }else if(denominator==0) {
                return {-1,intersection};
        }else{
                intersection.first=(1.0*numerator)/denominator;
                if((x2-x1)!=0) {
                        intersection.second=((1.0*(y2-y1))/(x2-x1))*intersection.first + y1-x1*((1.0*(y2-y1)))/(x2-x1);
                }else{
                        intersection.second=((1.0*(y4-y3))/(x4-x3))*intersection.first + y3-x3*((1.0*(y4-y3)))/(x4-x3);
                }
                float x1g,x2g,x3g,x4g,y1g,y2g,y3g,y4g;

                if(x1>x2) {
                        x1g=x1;
                        x2g=x2;
                }else{
                        x1g=x2;
                        x2g=x1;
                }

                if(x3>x4) {
                        x3g=x3;
                        x4g=x4;
                }else{
                        x3g=x4;
                        x4g=x3;
                }

                if(y1>y2) {
                        y1g=y1;
                        y2g=y2;
                }else{
                        y1g=y2;
                        y2g=y1;
                }

                if(y3>y4) {
                        y3g=y3;
                        y4g=y4;
                }else{
                        y3g=y4;
                        y4g=y3;
                }


                if (intersection.first>x1g || intersection.first<x2g) {
                        return {-1,intersection};

                }
                else if (intersection.first>x3g || intersection.first<x4g) {
                        return {-1,intersection};

                }
                else if (intersection.second>y1g || intersection.second<y2g) {
                        return {-1,intersection};

                }
                else if (intersection.second>y3g || intersection.second<y4g) {
                        return {-1,intersection};

                }else{
                        // cout<<intersection.first<<" "<<intersection.second;
                        return {1,intersection};
                }
        }
        // return intersection;
}


bool opposite_side(vector<Vertice> & faceVertices, Vertice e, Vertice f){
        /** returns true if a and b are on opposite side of plane formed by faceVertices
           , false otherwise **/
        Vertice u=faceVertices[0],v=faceVertices[1],w=faceVertices[2];
        Vertice uv= v-u, uw=w-u;
        float a= uv.second*uw.third - uv.third*uw.second;
        float b= -uv.first*uw.third + uv.third*uw.first;
        float c= uv.first*uw.second - uv.second*uw.first;
        float d= -(a*u.first + b*u.second + c*u.third);
        if( (a*e.first + b*e.second + c*e.third + d) * (a*f.first + b*f.second + c*f.third + d) <0) return true;
        else return false;


}

Vertice back_proj(Vertice v, Edge e, int plane){
        Vertice a=e.vertices.first, b= e.vertices.second, ans;
        float x1=a.first,x2=b.first, y1=a.second, y2=b.second, z1=a.third, z2=b.third;
        float x,y,z;
        if(plane==0) { //revert XY projection
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

Edge projected(Edge a, int plane){ /** 2D projection of edge (might include as an Edge member function) **/
        Vertice u=a.vertices.first, v=a.vertices.second, u_proj, v_proj;
        u_proj.is3d=false;
        v_proj.is3d=false;
        double ux=u.first, uy=u.second, uz=u.third, vx=v.first, vy=v.second, vz=v.third;
        Edge e;
        if(plane==0) { //XY Plane
                u_proj.first=ux;
                u_proj.second=uy;
                v_proj.first=vx;
                v_proj.second=vy;
        }
        else if(plane==1) { //YZ Plane
                u_proj.first=uy;
                u_proj.second=uz;
                v_proj.first=vy;
                v_proj.second=vz;
        }
        else if(plane==2) { //XZ Plane
                u_proj.first=ux;
                u_proj.second=uz;
                v_proj.first=vx;
                v_proj.second=vz;
        }
        else if(plane==3) { //isometric view
                u_proj.first= (std::sqrt(3) * ux -  std::sqrt(3) * uz)/ std::sqrt(6);
                u_proj.second=  (ux + 2*uy + uz)/ std::sqrt(6);
                v_proj.first= (std::sqrt(3) * vx -  std::sqrt(3) * vz)/ std::sqrt(6);
                v_proj.second=  (vx + 2*vy + vz)/ std::sqrt(6);
                //for reversing the projection
                // u_proj.third=(ux-uy+uz)/std::sqrt(3);
                // v_proj.third=(vx-vy+vz)/std::sqrt(3);
        }
        e.vertices.first=u_proj;
        e.vertices.second=v_proj;
        return e;
}

Vertice get_vertex_inf(int plane){
        Vertice ret;
        ret.is3d=true;
        if(plane==0) { //point from which XY view is taken
                ret.first=1;
                ret.second=1;
                ret.third=INF;
        }
        else if(plane==1) {//point from which YZ view is taken
                ret.first=-INF;
                ret.second=1;
                ret.third=1;
        }
        else if(plane==2) {//point from which XZ view is taken
                ret.first=1;
                ret.second=-INF;
                ret.third=1;
        }
        else if(plane==3) {
                ret.first=-INF;
                ret.second=-INF;
                ret.third=INF;
        }
        return ret;
};

void render2DHidden(Fig3D & object3D,QPainter & painter,int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
                    ){
        set<Edge> edgeSet3D;
        get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);
        for (auto e: edgeSet3D) {
                Edge e_proj= projected(e,plane);
                for(auto face: object3D.faces) {
                        if(plane==0) cout<<"START"<<endl;
                        set<Edge> faceEdgeSet3D;
                        vector< vector<unsigned int> > tmpfaces;
                        tmpfaces.push_back(face);
                        get_edges3D(object3D.vertices,tmpfaces,faceEdgeSet3D);
                        vector<Vertice> overlapEndPoints;
                        bool is_overlapping=false;
                        for(auto faceEdge: faceEdgeSet3D) {
                                pair<int,Vertice> ret= get_intersection(e_proj, projected(faceEdge,plane));
                                if(ret.first==1){ 
                                        overlapEndPoints.push_back(ret.second);
                                        if(plane==0) cout<<"OVERLAP ###### "<<(ret.second.first+2)*20<<", "<<(ret.second.second+2)*20<<endl;
                                }
                                else if(ret.first==0) { //overlapping
                                        if(faceEdge==e) {
                                                is_overlapping=true;
                                                if(plane==0) cout<<"SAME FACE, SKIP!!!!!"<<endl;
                                        }
                                        overlapEndPoints.clear();
                                        break;
                                }
                        }
                        set<Vertice> removeDuplicates;
                        for(auto it: overlapEndPoints){
                                removeDuplicates.insert(it);
                        }
                        overlapEndPoints.clear();
                        for(auto it: removeDuplicates){
                                overlapEndPoints.push_back(it);
                        }
                        if(is_overlapping) continue;
                        set<Edge> faceEdgeSet2D;
                        for(auto it: faceEdgeSet3D){
                                faceEdgeSet2D.insert(projected(it,plane));
                            }
                        
                        vector<Vertice> faceVertices;
                        faceVertices.push_back(object3D.vertices[face[0]]);
                        faceVertices.push_back(object3D.vertices[face[1]]);
                        faceVertices.push_back(object3D.vertices[face[2]]);
                        Vertice proj_inf= get_vertex_inf(plane);
                        set< pair<Vertice,int> > hiddenEdgeSet;
                        if(overlapEndPoints.size()==2) {
                                if(plane==0) cout<<"2 points"<<endl;
                                Vertice u=overlapEndPoints[0],v=overlapEndPoints[1];
                                u.is3d=false;
                                v.is3d=false;
                                Vertice u_corr=back_proj(u,e,plane), v_corr=back_proj(v,e,plane);
                                if (opposite_side(faceVertices,u_corr,get_vertex_inf(plane))  ||  opposite_side(faceVertices,v_corr,get_vertex_inf(plane)) ){
                                    if(u<v){
                                        hiddenEdgeSet.insert({u,0});
                                        hiddenEdgeSet.insert({v,1});
                                    }
                                    else{
                                        hiddenEdgeSet.insert({u,1});
                                        hiddenEdgeSet.insert({v,0});
                                    }
                           
                                //check if back_proj(u,e) and (v.first,v.second,inf) are on opposite sides of plane or not
                                //if they are, u-v edge is obstructed from view
                                //if u<v set add <u,START> and <v,END> to hiddenEdgeSet (vice versa for v<u)
                                    }
                        }
                        else if(overlapEndPoints.size()==1) {
                            if(plane==0) cout<<"1 point"<<endl;
                            Vertice u=overlapEndPoints[0],v;
                            Vertice u_corr=back_proj(u,e,plane);
                            u.is3d=false;
                            v.is3d=false;
                            if ( opposite_side(faceVertices,u_corr,get_vertex_inf(plane)) ){
                                if(plane==0) cout<<"OPPOSITE SIDE !_!_!_!_!_!_!_!_!_!_!_"<<endl;
                                if(is_inside(e_proj.vertices.first,faceEdgeSet2D) && !(e_proj.vertices.first==u) ){ 
                                        v=e_proj.vertices.first;  
                                //find the end point that lies in the interior of the face
                                //repeat the previous procedure
                                }
                                else  {//if(is_inside(e_proj.vertices.second,faceEdgeSet2D)){
                                        v=e_proj.vertices.second;
                                }
                            }
                            else{
                                if(plane==0){
                                         cout<<"SAME SIDE :(:(:(:(:(:(:("<<endl; 
                                         cout<<"Point 2D- "<<(u.first+2)*20<<", "<<(u.second+2)*20<<endl;
                                         cout<<"Point 3D- "<<(u_corr.first+2)*20<<", "<<(u_corr.second+2)*20<<", "<<(u_corr.third+2)*20<<endl;
                                         cout<<"Vertices- "<<endl;
                                         for(auto it: faceVertices){
                                                 cout<<(it.first+2)*20<<", "<<(it.second+2)*20<<", "<<(it.third+2)*20<<endl;
                                         }       
                                }
                                
                                break;
                            }
                            Vertice v_corr=back_proj(v,e,plane);
                            if(u<v){
                            hiddenEdgeSet.insert({u,0});
                            hiddenEdgeSet.insert({v,1});
                            }
                            else{
                            hiddenEdgeSet.insert({u,1});
                            hiddenEdgeSet.insert({v,0});
                            }
                        }
                        if(plane==0){
                                Vertice e_proj1=e_proj.vertices.first, e_proj2=e_proj.vertices.second;
                                cout<<"Edge proj-------------------------------------------------------"<<endl;
                                cout<<(e_proj1.first+2)*20<<", "<<(e_proj1.second+2)*20<<endl;
                                cout<<(e_proj2.first+2)*20<<", "<<(e_proj2.second+2)*20<<endl;
                        }
                        
                        if(hiddenEdgeSet.size()!=0 && plane==0){
                            cout<<"hiddenEdgeSet size for plane xxxxxxxxxxxxxxxxxxxxxxxxx "<<plane<<" "<<hiddenEdgeSet.size()<<endl;
                            for(auto it: hiddenEdgeSet){
                                Vertice u=it.first;
                                cout<<(u.first+2)*20<<", "<<(u.second+2)*20<<endl;
                                // cout<<(v.first+2)*20<<", "<<(v.second+2)*20<<endl;
                            }
                        
                            cout<<"Face edges-"<<endl;
                        }
                        // if(plane==0) cout<<"Face edges- "<<endl;
                        // Vertice u=e_proj.vertices.first;
                        // Vertice v=e_proj.vertices.second;
                        // painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20);
                        for(auto it:faceEdgeSet2D) {
                            Vertice u=it.vertices.first;
                            Vertice v=it.vertices.second;
                        //     painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20); //will have to change this to fit any size of pixmap
                            if(plane==0){
                                    cout<<(u.first+2)*20<<", "<<(u.second+2)*20<<endl;
                                    cout<<(v.first+2)*20<<", "<<(v.second+2)*20<<endl<<endl;
                            }
                        }
                    }
                    Vertice u=e_proj.vertices.first;
                        Vertice v=e_proj.vertices.second;
                        painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20);                        



                }
        }


bool is_inside(Vertice v, set<Edge> edgeSet){

        Vertice secondVertice;
        secondVertice.first=v.first;
        secondVertice.second=v.second+100000;

        Edge artificalEdge;
        artificalEdge.vertices.first=v;
        artificalEdge.vertices.second=secondVertice;

        int count=0;

        for(auto it:edgeSet) {
                cout<<"Starting iteration";
                pair<int,Vertice> res=get_intersection(artificalEdge,it);
                 cout<<"Result of get_intersection is "<<res.first<<" "<<res.second.first<<" "<<res.second.second<<endl;
                if(res.first==1) {
                        count++;
                }
        }

        cout<<"count is "<<count;

        if(count%2==0) {
                return false;
        }

        return true;
}
