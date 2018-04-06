#include "mainwindow.h"
#include <QApplication>
#include "basicComponents.h"
#include "objLoader.h"
#include "optionwindow.h"
#include "hiddenLines.h"
#include "helperfunctions.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);

        MainWindow three2two;

        Vertice a1;
        a1.first=(15.9466-40);
        a1.second=(23.7768-40);
        a1.is3d=false;

        Vertice b;
        b.first=(55.2117-40);
        b.second=(23.7768-40);
        b.is3d=false;

        Vertice c;
        c.first=(56.537-40);
        c.second=(63.1691-40);
        c.is3d=false;

        Vertice d;
        d.first=(17.2719-40);
        d.second=(63.1691-40);
        d.is3d=false;

        Edge ab,bc,cd,da;

        ab.vertices={a1,b};
        bc.vertices={b,c};
        cd.vertices={c,d};
        da.vertices={d,a1};

        set<Edge> edges;
        edges.insert(ab);
edges.insert(bc);
edges.insert(cd);
    edges.insert(da);

        Vertice inn;
        inn.first=(23.463-40);
        inn.second=(16.8309-40);
        inn.is3d=false;

        bool res=is_inside(inn,edges);
        if(res){

            cout<<"Result of is_inside is true";
        }else{
                        cout<<"Result of is_inside is false";
        }

        optionWindow w;
        w.show();

        return a.exec();
}
