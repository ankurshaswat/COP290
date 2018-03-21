#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <set>
#include <QGuiApplication>
#include <QtUiTools>
#include "objLoader.h"
#include "figures.h"
#include "complexComponents.h"
#include "renderMethods.h"
#include "hiddenLines.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{


        ui->setupUi(this);
        connectSliderandButtons();
}


void MainWindow::connectSliderandButtons(){
    connect(ui->x_rotation, &QSlider::valueChanged, this, &MainWindow::setXRotation);
    connect(ui->y_rotation, &QSlider::valueChanged, this, &MainWindow::setYRotation);
    connect(ui->z_rotation, &QSlider::valueChanged, this, &MainWindow::setZRotation);

    connect(this, &MainWindow::xRotationChanged, ui->x_rotation, &QSlider::setValue);
    connect(this, &MainWindow::yRotationChanged, ui->y_rotation, &QSlider::setValue);
    connect(this, &MainWindow::zRotationChanged, ui->z_rotation, &QSlider::setValue);

    connect(ui->xoffseter_inc,  &QPushButton::clicked, this, &MainWindow::incX);
    connect(ui->xoffseter_dec,  &QPushButton::clicked, this, &MainWindow::decX);
    connect(ui->yoffseter_inc,  &QPushButton::clicked, this, &MainWindow::incY);
    connect(ui->yoffseter_dec,  &QPushButton::clicked, this, &MainWindow::decY);
    connect(ui->zoffseter_inc,  &QPushButton::clicked, this, &MainWindow::incZ);
    connect(ui->zoffseter_dec,  &QPushButton::clicked, this, &MainWindow::decZ);
    ui->x_rotation->setRange(0, 360 );
    ui->y_rotation->setRange(0, 360 );
    ui->z_rotation->setRange(0, 360 );
}
MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::setVertices(std::vector<Vertice> & out_vertices,std::vector<std::vector<unsigned int> > & faces_vertices){
        fig.faces=faces_vertices;
        fig.vertices=out_vertices;
}

void MainWindow::setWireFrame(WireFrame wf){
    this->wf=wf;
}
//void MainWindow::render2D(std::vector<Vertice> & out_vertices,std::vector<std::vector<unsigned int>> & faces_vertices,	//Might change this to a Fig3D object later on,
//        QPainter &  painter,int plane // 0- XY, 1-YZ, 2-XZ
//                          ){
//        /** Takes input 3D object information (vertices,faces), QPainter object, othographic plane (XY /YZ/ XZ)
//        and draws the corresponding 2D view on the QPainter object */
//            printf("Rendering 2D");

//            std::set<Edge> edgeSet;
//            bool edges_extracted=get_edges3D(out_vertices,faces_vertices,edgeSet);
//            for(auto it:edgeSet){
//                Vertice u=it.vertices.first;
//                Vertice v=it.vertices.second;
//                if(plane==0){ //XY Plane
//                    painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20);
//                }else if(plane == 1){
//                      painter.drawLine((u.second + 2)*20, (u.third +2)*20, (v.second + 2)*20, (v.third +2)*20);
//                }else if(plane ==2){
//                     painter.drawLine((u.first + 2)*20, (u.third +2)*20, (v.first + 2)*20, (v.third +2)*20);
//                }else if(plane ==3){
//                     Vertice  u_proj,v_proj;
//                    u_proj.first= (std::sqrt(3) * u.first -  std::sqrt(3) * u.third)/ std::sqrt(6);
//                    u_proj.second=  (u.first + 2*u.second + u.third)/ std::sqrt(6);
//                    v_proj.first= (std::sqrt(3) * v.first -  std::sqrt(3) * v.third)/ std::sqrt(6);
//                    v_proj.second=  (v.first + 2*v.second + v.third)/ std::sqrt(6);
//                       painter.drawLine((u_proj.first + 2)*20, (u_proj.second +2)*20, (v_proj.first + 2)*20, (v_proj.second +2)*20);
//                }

//            }


//}

void MainWindow::render2DinLabel(Fig3D & fig_to_render,unsigned int plane){
// 0- XY, 1-YZ, 2-XZ
//    string label;


        QPixmap pixmap(200,200);
        pixmap.fill(Qt::white);
        QPainter painter(&pixmap);
//    QPen Red((QColor(255,0,0)),1);
//    painter.setPen(Red);
//    render2D(out_vertices, faces_vertices, painter, plane);
        renderAxes(fig_to_render, painter,plane);
        QPen Red((QColor(255,0,0)),1);
        painter.setPen(Red);
        render2DHidden(fig_to_render, painter,plane);

        switch (plane) {
        case 0:
                // printf("setting xyDisplay");

                ui->xyDisplay->setPixmap(pixmap);
                break;
        case 1:
                // printf("setting yzDisplay");
                ui->yzDisplay->setPixmap(pixmap);
                break;
        case 2:
                // printf("setting xzDisplay");
                ui->xzDisplay->setPixmap(pixmap);
                break;

        case 3:
                ui->isometricView->setPixmap(pixmap);
                break;
        default:
                // printf("Ended up in default");
                break;
        }



}




void MainWindow::renderAllViews(Fig3D & fig_to_render){
        // printf("Rendering All views\n");

        render2DinLabel(fig_to_render,0);
        render2DinLabel(fig_to_render,1);
        render2DinLabel(fig_to_render,2);
        render2DinLabel(fig_to_render,3);
}

void qNormalizeAngle(int &angle)
{

        // printf("angle=%d\n",angle);
        while (angle < 0)
                angle += 360;
        while (angle > 360 )
                angle -= 360;
}
void MainWindow::setXRotation(int angle)
{
        qNormalizeAngle(angle);
        if (angle != x_rot) {

                x_rot = angle;
                emit xRotationChanged(angle);

                update();
        }
}

void MainWindow::setYRotation(int angle)
{
        qNormalizeAngle(angle);
        if (angle != y_rot) {
                y_rot = angle;
                emit yRotationChanged(angle);

                update();
        }
}

void MainWindow::setZRotation(int angle)
{
        qNormalizeAngle(angle);
        if (angle != z_rot) {
                z_rot = angle;
                emit zRotationChanged(angle);

                update();
        }
}

void MainWindow::incX()
{
        x_off+=0.1;
        update();
}
void MainWindow::incY()
{
        y_off+=0.1;
        update();
}
void MainWindow::incZ()
{
        z_off+=0.1;
        update();
}
void MainWindow::decX()
{
        x_off-=0.1;
        update();
}
void MainWindow::decY()
{
        y_off-=0.1;
        update();
}
void MainWindow::decZ()
{
        z_off-=0.1;
        update();
}


void MainWindow::update(){

//        x=fig.getTransformation(0,0,0,10000,10000,10000);
        if(mode==0){
            Fig3D x;
            // printf("offset %f\n",x_off);
            x=fig.getTransformation(x_rot,y_rot,z_rot,x_off,y_off,z_off);
            renderAllViews(x);
        }else{
            WireFrame wf2;
            wf2=wf.getTransformation(x_rot,y_rot,z_rot,x_off,y_off,z_off);
            render2Dto3D(wf2);
        }
//       renderAllViews(fig.vertices,fig.faces);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
        m_lastPos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
        int dx = event->x() - m_lastPos.x();
        int dy = event->y() - m_lastPos.y();

        if (event->buttons() & Qt::LeftButton) {
                setXRotation(x_rot +  dy);
                setYRotation(y_rot +  dx);
        } else if (event->buttons() & Qt::RightButton) {
                setXRotation(x_rot +  dy);
                setZRotation(z_rot +  dx);
        }
        m_lastPos = event->pos();
}

void MainWindow::renderFromEdges(vector<Edge> edges,int plane){

    QPixmap pixmap(200,200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen Red((QColor(255,0,0)),1);
    painter.setPen(Red);

    for (unsigned int i=0;i<edges.size();i++){
        Edge e=projected(edges[i],plane);
        Vertice u=e.vertices.first;
        Vertice v=e.vertices.second;
        painter.drawLine((u.first + 2)*20, (u.second +2)*20, (v.first + 2)*20, (v.second +2)*20);
    }
switch (plane) {
case 0:
        // printf("setting xyDisplay");

        ui->xyDisplay->setPixmap(pixmap);
        break;
case 1:
        // printf("setting yzDisplay");
        ui->yzDisplay->setPixmap(pixmap);
        break;
case 2:
        // printf("setting xzDisplay");
        ui->xzDisplay->setPixmap(pixmap);
        break;

case 3:
        ui->isometricView->setPixmap(pixmap);
        break;
default:
        // printf("Ended up in default");
    break;
}


}

void MainWindow::render2Dto3D(WireFrame wf){
    vector<Edge> edges=wf.edges;
    renderFromEdges(edges,0);
    renderFromEdges(edges,1);
    renderFromEdges(edges,2);
    renderFromEdges(edges,3);
}
