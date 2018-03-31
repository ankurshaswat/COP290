#include "helperfunctions.h"
#include "basicComponents.h"
#include "math.h"
#include<vector>
#include<algorithm>

#define PI 3.14159265

Vertice transform(Vertice v_in,double Xrot,double Yrot,double Zrot,double Xoff,double Yoff,double Zoff){
    /** get transformed 3D object */

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

bool isSubset(vector<int> & a, vector<int> & b)
{
        for(auto it: a) if( find(b.begin(),b.end(),it) == b.end() ) return false;
        return true;

}