#include "mainwindow.h"
#include <QApplication>
#include "basicComponents.h"
#include "objLoader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::vector<Vertice> out_vertices;
    std::vector<std::vector<unsigned int>> faces_vertices;
    printf("Starting to read file\n");
    bool res=loadOBJ("./test.obj",out_vertices,faces_vertices);
    printf("Object Loaded Now rendering views");

    w.setVertices(out_vertices,faces_vertices);

    w.renderAllViews(out_vertices,faces_vertices);

    w.show();

    return a.exec();
}
