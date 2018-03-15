#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basiccomponents.h"
#include "figures.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void render2D(std::vector<Vertice> & out_vertices,std::vector<std::vector<unsigned int>> & faces_vertices, QPainter &  painter,int plane );
    void render2DinLabel(std::vector<Vertice> out_vertices,std::vector<std::vector<unsigned int>> faces_vertices,unsigned int plane);
    void renderAllViews(std::vector<Vertice> out_vertices,std::vector<std::vector<unsigned int>> faces_vertices);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void incX();
    void incY();
    void incZ();
    void decX();
    void decY();
    void decZ();
    void update();
//    void setFig3D()
private:
    Ui::MainWindow *ui;
    double x_rot=0,y_rot=0,z_rot=0;
    double x_off=0,y_off=0,z_off=0;
    Fig3D fig;
};

#endif // MAINWINDOW_H
