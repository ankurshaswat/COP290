#include "optionwindow.h"
#include "ui_optionwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "objLoader.h"

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


//        MainWindow w=new MainWindow();

    //    std::vector<Vertice> out_vertices;
    //    std::vector<std::vector<unsigned int>> faces_vertices;
        printf("Starting to read file\n");
        Fig3D loaded_obj=loadOBJ(path);
        printf("Object Loaded Now rendering views");

        w.setVertices(loaded_obj.vertices,loaded_obj.faces);
        w.renderAllViews(loaded_obj);

        w.show();
//        ~optionWindow();
//QMessageBox::information(this,tr("File Name"),filePath );
}
