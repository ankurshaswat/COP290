#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include<QApplication>
#include <QtUiTools>

#include "helperFunctions/include/module1/basicComponents.h"
#include "helperFunctions/include/module1/objLoader.h"

#include <iostream>
#include <vector>
#include <set>



QWidget* loadUiFile()
{
    QUiLoader loader;

    QFile file("/home/sushant/Desktop/courses/cop290/COP290/qtapp/mainwindow.ui");
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load(&file);
    file.close();

    return formWidget;
}

void render2D(std::vector<Vertice> & out_vertices,
        std::vector<std::vector<unsigned int>> & faces_vertices,	//Might change this to a Fig3D object later on,
        QPainter &  painter,
        int plane // 0- XY, 1-YZ, 2-XZ
        ){
        /** Takes input 3D object information (vertices,faces), QPainter object, othographic plane (XY /YZ/ XZ)
        and draws the corresponding 2D view on the QPainter object */

            std::set<Edge> edgeSet;
            bool edges_extracted=get_edges3D(out_vertices,faces_vertices,edgeSet);
            for(auto it:edgeSet){
                Vertice u=it.vertices.first;
                Vertice v=it.vertices.second;
                if(plane==0){ //XY Plane
//                    cout<<"XY coordinates: "<<(u.first+2)*20<<","<<(u.second+2)*20<<" "<<(v.first+2)*20<<","<<(v.second+2)*20<<endl;
                    painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20);
                }


            }


}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    const QString labelName= "Label1";
//    QGuiApplication app(argc, argv);
    QApplication app(argc,argv);
    QWidget *mainWindow=loadUiFile();
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
    std::vector<Vertice> out_vertices;
    std::vector<std::vector<unsigned int>> faces_vertices;
    bool res=loadOBJ("./test.obj",out_vertices,faces_vertices);

    QPixmap pixmap(200,200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen Red((QColor(255,0,0)),1);
    painter.setPen(Red);
    render2D(out_vertices, faces_vertices, painter, 0);//render XY projection
//    painter.drawLine(0,0,100,100);
    mainWindow->findChild<QLabel *>("label1")->setPixmap(pixmap);
    mainWindow->show();
    return app.exec();
}
