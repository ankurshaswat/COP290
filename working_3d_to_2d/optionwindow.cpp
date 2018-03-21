#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "objLoader.h"
#include "reconstMethods.h"

optionWindow::optionWindow(QWidget *parent ) :
        QMainWindow(parent),
        ui(new Ui::optionWindow)
{
        ui->setupUi(this);
}


optionWindow::~optionWindow()
{
        delete ui;
}

void optionWindow::on_threeD2_2D_clicked()
{
        QString filePath=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "~",
                "OBJ Files (*.obj)");


        QByteArray ba = filePath.toLatin1();
        const char *path = ba.data();
        w.mode=0;

//        MainWindow w=new MainWindow();

        //    std::vector<Vertice> out_vertices;
        //    std::vector<std::vector<unsigned int>> faces_vertices;
        printf("Starting to read file\n");
        Fig3D loaded_obj=loadOBJ(path);
        printf("Object Loaded Now rendering views\n");

        w.connectSliderandButtons();
        w.setVertices(loaded_obj.vertices,loaded_obj.faces);
        w.renderAllViews(loaded_obj);

        w.show();
//        ~optionWindow();
//QMessageBox::information(this,tr("File Name"),filePath );
}

void optionWindow::on_twoD2_3D_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(
            this,
            tr("Open File"),
            "~",
            "TXT Files (*.txt)");


    QByteArray ba = filePath.toLatin1();
    const char *path = ba.data();

    w.mode=1;
//        MainWindow w=new MainWindow();

    //    std::vector<Vertice> out_vertices;
    //    std::vector<std::vector<unsigned int>> faces_vertices;
    printf("Starting to read file\n");
    WireFrame wf=constUniq3dEdges(readFile(path));
    printf("Object Loaded Now rendering views\n");
    w.setWireFrame(wf);
    w.render2Dto3D(wf);
//        w.setVertices(loaded_obj.vertices,loaded_obj.faces);
//        w.renderAllViews(loaded_obj);

    w.show();
//        ~optionWindow();
//QMessageBox::information(this,tr("File Name"),filePath );
}
