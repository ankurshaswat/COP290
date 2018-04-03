#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basicComponents.h"
#include "figures.h"
#include "complexComponents.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:

/// Required constructor to setup UI
explicit MainWindow(QWidget *parent = 0);

/// Required Destructor
~MainWindow();

/// Function used to set Vertices of the 3d figure (Used for 3d to 2d views).
void setVertices(std::vector<Vertice> &out_vertices,std::vector<std::vector<unsigned int> > &faces_vertices);

/// Function used to set the Wireframe object generated from labelled 2d Views.
void setWireFrame(WireFrame wf);

//    void render2D(std::vector<Vertice> & out_vertices,std::vector<std::vector<unsigned int>> & faces_vertices, QPainter &  painter,int plane );

/// Function used to render the view in a specific label according to number set by plane.
void render2DinLabel(Fig3D & fig_to_render,unsigned int plane);

/// Function used to render all views of a 3d figure.
void renderAllViews(Fig3D & fig_to_render);

/// Function used to increase X offset of displayed figure.
void incX();

/// Function used to increase Y offset of displayed figure.
void incY();

/// Function used to increase Z offset of displayed figure.
void incZ();

/// Function used to decrease X offset of displayed figure.
void decX();

/// Function used to decrease Y offset of displayed figure.
void decY();

/// Function used to decrease Z offset of displayed figure.
void decZ();

/// Function triggered to reconstruct views whenever offset or rotation of object changed.
void update();

/// Function to handle mouse press events.
void mousePressEvent(QMouseEvent *event) override;

/// Function to handle movement of mouse after clicking.
void mouseMoveEvent(QMouseEvent *event) override;

/// Function used to render views from the given edges.
void renderFromEdges(vector<Edge> edges,int plane);

/// Function used to render the views from the provided wireframe (in case of 2d to 3d)
void render2Dto3D(WireFrame wf,Fig3D fig);

int mode;

/// Function to connect all sliders and buttons to appropriate functions on initializing view.
void connectSliderandButtons();

public slots:

/// Slot to set Xrotation angle (either from slider or mouse hold and drag movement).
void setXRotation(int angle);

/// Slot to set Yrotation angle (either from slider or mouse hold and drag movement).
void setYRotation(int angle);

/// Slot to set Zrotation (either from slider or mouse hold and drag movement).
void setZRotation(int angle);

signals:

/// Signal to inform slider that x rotation angle has been changed by mouse hold and drag movement.
void xRotationChanged(int angle);

/// Signal to inform slider that y rotation angle has been changed by mouse hold and drag movement.
void yRotationChanged(int angle);

/// Signal to inform slider that z rotation angle has been changed by mouse hold and drag movement.
void zRotationChanged(int angle);

//    void setFig3D()

private:
Ui::MainWindow *ui;
double x_rot=0,y_rot=0,z_rot=0;
QPoint m_lastPos;
double x_off=0,y_off=0,z_off=0;

Fig3D fig;
WireFrame wf;
};

#endif // MAINWINDOW_H
