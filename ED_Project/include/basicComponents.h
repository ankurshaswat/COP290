#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#define EPS 0.01
using namespace std;
struct Vertice
{

// public:
        float first,second,third=0;
        bool is3d=true;
        char label;

        /** \return Vertice that is the generated copy
      * 
      * This method generates a copy of the Vertice object
      * from which it is called to create a new Vertice object
      * with the same values but free from any reference to original.
      */
        Vertice deepCopy(){
                Vertice t;
                t.first=first;
                t.second=second;
                t.third=third;
                t.is3d=is3d;
                return t;
        }

        /// Less than operator defined for faster comparisons between different vertices.
        bool operator<(Vertice other) const
        {

                if(is3d) return make_pair(first*100,make_pair(second*100,third*100)) > make_pair(other.first*100,make_pair(other.second*100,other.third*100));
                else return make_pair(first*100,second*100) > make_pair(other.first*100,other.second*100);
        }

        /// Equality operator defined for faster comparisons between different vertices.
        bool operator ==(Vertice b) {
	return  (abs(first - b.first)<EPS ) && (abs(second - b.second)<EPS ) && ( ( (abs(third - b.third)<EPS ) && b.is3d && is3d) || (!is3d) );
        }

        /// Difference operator defined for faster comparisons between different vertices.        
        Vertice operator-(const Vertice& rhs){
                Vertice diff;
                diff.first=first - rhs.first;
                diff.second=second -= rhs.second;
                if(is3d && rhs.is3d) {
                        diff.third=third-=rhs.third;
                        diff.is3d=true;
                }
                else{
                        diff.is3d=false;
                }
                return diff;
        }
        


};

/// Function to print shifted co-ordiantes of vertices for debugging.
inline ostream& operator<<(std::ostream& os,const Vertice& v)
{
    if(v.is3d)  return os << v.first+50 << ", " << v.second+50 << ", " << v.third+50 << endl;
    else return os << v.first+50 << ", " << v.second+50 <<endl;
}

struct Edge {

// public:
        pair<Vertice,Vertice> vertices;

        /// Less than operator defined for faster comparisons between Edges.
        bool operator<(Edge other) const
        {
                return vertices > other.vertices;
        }

        /// Equality operator defined for faster comparisons between Edges.        
        bool operator ==(Edge b) {
	return (vertices.first==b.vertices.first && vertices.second==b.vertices.second ) || 
        ( vertices.first==b.vertices.second && vertices.second==b.vertices.first );
        }

        /**
        * Generates the 2D projection of a of the edge on a plane
        * \param plane The plane on which projection is to be taken is passed through this
        * 
        * plane = 0 -> XY plane
        * plane = 1 -> YZ plane
        * plane = 2 -> XZ plane
        * plane = 3 -> Isometric View
        */
        Edge projected(int plane){ /** 2D projection of edge **/
        Vertice u=vertices.first, v=vertices.second, u_proj, v_proj;
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


};


/// Structured Defined to represent Planes
struct Plane {
        float a,b,c,d;

        /// Constructor to define plane using 3 vertices.
        Plane(Vertice u, Vertice v, Vertice w){
                Vertice uv= v-u, uw=w-u;
                a= uv.second*uw.third - uv.third*uw.second;
                b= -uv.first*uw.third + uv.third*uw.first;
                c= uv.first*uw.second - uv.second*uw.first;
                d= -(a*u.first + b*u.second + c*u.third);
        }

        float distance(Vertice u){
                float x= sqrt(a*a +b*b +c*c);
                float d1=(a*u.first + b*u.second + c*u.third + d);
                return abs(d1/x);
        }

        /// Function used to check whether an Edge lies on the plane or not.
        bool onPlane(Edge e){
                Vertice u=e.vertices.first, v=e.vertices.second;
                if(distance(u)<EPS && distance(v)<EPS) return true;
                else return false;
        }
};


#endif
