#include "mainwindow.h"
#include <QApplication>
#include "basicComponents.h"
#include "objLoader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    std::vector<Vertice> out_vertices;
//    std::vector<std::vector<unsigned int>> faces_vertices;
    printf("Starting to read file\n");
    Fig3D loaded_obj=loadOBJ("./test.obj");
    printf("Object Loaded Now rendering views");

    w.setVertices(loaded_obj.vertices,loaded_obj.faces);
    w.renderAllViews(loaded_obj);

    w.show();

    return a.exec();
}
