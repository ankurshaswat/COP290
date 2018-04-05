#include "helperfunctions.h"
#include "basicComponents.h"
#include "complexComponents.h"
#include "math.h"
#include<vector>
#include<algorithm>
#include<set>

#define PI 3.14159265
#define INF 1000000
#define epsilon 0.1

/** get transformed 3D object **/
Vertice transform(Vertice v_in,double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff){
    double sinXrot= sin(Xrot * PI/180 ),cosXrot= cos(Xrot * PI/180 );
    double sinYrot= sin(Yrot * PI/180 ),cosYrot= cos(Yrot * PI/180 );
    double sinZrot= sin(Zrot * PI/180 ),cosZrot= cos(Zrot * PI/180 );

    double transformationMat[4][4]={{cosYrot * cosZrot, cosXrot * sinZrot +sinXrot*sinYrot*cosZrot,sinXrot*sinZrot-cosXrot*sinYrot*cosZrot,Xoff},
                                    {-1*cosYrot*sinZrot,cosXrot*cosZrot-sinXrot*sinYrot*sinZrot,sinXrot*cosZrot+cosXrot*sinYrot*sinZrot,Yoff},
                                    {sinYrot,-1*sinXrot*cosYrot,cosXrot*cosYrot,Zoff},
                                    {0,0,0,1}};

    double matA[4][1],result[4][1];
    matA[3][0]=1;

            matA[0][0]=v_in.first;
            matA[0][1]=v_in.second;
            matA[0][2]=v_in.third;

            for(int i = 0; i < 4; ++i)
                    for(int j = 0; j < 1; ++j)

                    {  result[i][j]=0;
                       for(int k = 0; k < 4; ++k)
                       {
                               result[i][j] += transformationMat[i][k] * matA[k][j];
                       }}
            Vertice v;
            v.first=result[0][0];
            v.second=result[1][0];
            v.third=result[2][0];

            return v;

}


/** returns (1,point of intersection) if intersecting, (0,_) if overlapping and (-1,_) if parallel
   Both edges are 2D edges */
pair<int,Vertice> get_intersection(Edge a, Edge b){

 
        float x1,y1,x2,y2,x3,y3,x4,y4;
        float c2,c1,m2,m1;
        float numerator,denominator;
        Vertice intersection;
        intersection.is3d=false;
        if(a==b) return{0,intersection};
        if(a.vertices.first==b.vertices.first && a.vertices.first==b.vertices.second){ 
                return{1,a.vertices.first};
        }
        else if (a.vertices.second==b.vertices.first && a.vertices.second==b.vertices.second){ 
                return{1,a.vertices.second};
        } 
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

        if(abs(numerator)<epsilon && abs(denominator)<epsilon) {
                return {0,intersection};
        }else if(abs(denominator)<epsilon) {
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


                if (intersection.first-x1g>epsilon || intersection.first-x2g < -epsilon) {
                        return {-2,intersection};

                }
                else if (intersection.first-x3g>epsilon || intersection.first-x4g<-epsilon) {
                        return {-3,intersection};

                }
                else if (intersection.second-y1g>epsilon || intersection.second-y2g<-epsilon) {
                        return {-4,intersection};

                }
                else if (intersection.second-y3g>epsilon || intersection.second-y4g<-epsilon) {
                        return {-5,intersection};

                }else{
                        // cout<<intersection.first<<" "<<intersection.second;
                        return {1,intersection};
                }
        }
        // return intersection;
}

/** Checks if vertex is inside the polygon defined by the edge set **/
bool is_inside(Vertice v, set<Edge> edgeSet){

        Vertice secondVertice;
        secondVertice.first=v.first;
        secondVertice.second=v.second+100000;

        Edge artificalEdge;
        artificalEdge.vertices.first=v;
        artificalEdge.vertices.second=secondVertice;

        int count=0;
        bool correction=false;
        // cout<<"IS_INSIDE --"<<endl;
        // cout<<artificalEdge.vertices.first<<artificalEdge.vertices.second;
        for(auto it:edgeSet) {
                // cout<<"Starting iteration";
                pair<int,Vertice> res=get_intersection(artificalEdge,it);
                // cout<<"INTERSECT"<<endl;
                // cout<<it.vertices.first<<it.vertices.second;
                // cout<<res.first<<endl<<res.second;
                Vertice a=it.vertices.first, b=it.vertices.second;
                if(res.first==1 ) {
                        count++;
                }
                if(( (v.first==a.first && v.second<=a.second) || (v.first==b.first && v.second<=b.second)   ) && !correction) correction=true; //correction for the case of v lying on edge endpoint
        }
        if(correction) count++;
        // cout<<"COUNT- "<<count<<endl;

        // cout<<"count is "<<count;

        if(count%2==0) {
                return false;
        }

        return true;
}




/**A simple helper function to check if a is a subset of b**/
bool isSubset(vector<int> & a, vector<int> & b)
{
        for(auto it: a) if( find(b.begin(),b.end(),it) == b.end() ) return false;
        return true;

}

/**A simple helper function which checks if vertex is already present in vector (allowing for some error correction)**/
int verticePresent(vector<Vertice> & a, Vertice b){
        for(int i=0;i<a.size();i++){
                Vertice it=a[i];
                if(  abs(it.first-b.first)<0.1 && abs(it.second-b.second)<0.1 && (it.is3d==false || abs(it.third-b.third)<0.1   ) ) {
                        // cout<<"VERTICE PRESENT !!!!!!!!!!!!!"<<endl;
                        return i;
                }
        }
        // cout<<"-------"<<endl; 
        return -1;
}


///Takes a wireframe and subtracts coordinates of v from  all its edge vertices 
WireFrame modifyWireframe(WireFrame wf, Vertice v)
{
        WireFrame wfModified;
        for(auto e: wf.edges){
                Edge e_new;
                e_new.vertices={e.vertices.first - v, e.vertices.second - v};
                wfModified.edges.push_back(e_new);
        }
        return wfModified;
};

