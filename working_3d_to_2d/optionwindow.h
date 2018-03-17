#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class optionWindow;
}

class optionWindow : public QMainWindow
{
Q_OBJECT

public:
explicit optionWindow(QWidget *parent = 0);
~optionWindow();
MainWindow w;

private slots:
void on_threeD2_2D_clicked();

private:
Ui::optionWindow *ui;
};

#endif // OPTIONWINDOW_H
