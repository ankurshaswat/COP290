#include "basicComponents.h"
#include "objLoader.h"
#include "figures.h"

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

pair<int,Vertice> get_intersection(Edge a, Edge b){
        /** returns (1,point of intersection) if intersecting, (0,_) if overlapping and (-1,_) if parallel
           Both edges are 2D edges */

        int x1,y1,x2,y2,x3,y3,x4,y4;
        int c2,c1,m2,m1;
        int numerator,denominator;
        Vertice intersection;

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
                return (0,intersection);
        }else if(denominator==0) {
                return (-1,intersection);
        }else{
                intersection.first=(1.0*numerator)/denominator;
                if((x2-x1)!=0) {
                        intersection.second=((1.0*(y2-y1))/(x2-x1))*intersection.first + y1-x1*((1.0*(y2-y1)))/(x2-x1);
                }else{
                        intersection.second=((1.0*(y4-y3))/(x4-x3))*intersection.first + y3-x3*((1.0*(y4-y3)))/(x4-x3);
                }
                int x1g,x2g,x3g,x4g,y1g,y2g,y3g,y4g;

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
                        return (-1,intersection);

                }
                else if (intersection.first>x3g || intersection.first<x4g) {
                        return (-1,intersection);

                }
                else if (intersection.second>y1g || intersection.second<y2g) {
                        return (-1,intersection);

                }
                else if (intersection.second>y3g || intersection.second<y4g) {
                        return (-1,intersection);

                }else{
                        // cout<<intersection.first<<" "<<intersection.second;
                        return intersection;
                }
        }
        // return intersection;
}


bool opposite_side(vector<Vertice> & faceVertices, Vertice a, Vertice b){
        /** returns true if a and b are on opposite side of plane formed by faceVertices
           , false otherwise **/


}
void render2DHidden(Fig3D & object3D,
                    QPainter & painter,
                    int plane // 0- XY, 1-YZ, 2-XZ , 3-isometric
                    ){
        set<Edge> edgeSet3D;
        get_edges3D(object3D.vertices, object3D.faces,edgeSet3D);




}



int main(){




        return 0;
}
