/********************************************************************************
** Form generated from reading UI file 'optionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONWINDOW_H
#define UI_OPTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionWindow
{
public:
    QWidget *centralwidget;
    QPushButton *threeD2_2D;
    QPushButton *twoD2_3D;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *optionWindow)
    {
        if (optionWindow->objectName().isEmpty())
            optionWindow->setObjectName(QStringLiteral("optionWindow"));
        optionWindow->resize(287, 215);
        centralwidget = new QWidget(optionWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        threeD2_2D = new QPushButton(centralwidget);
        threeD2_2D->setObjectName(QStringLiteral("threeD2_2D"));
        threeD2_2D->setGeometry(QRect(80, 40, 89, 25));
        twoD2_3D = new QPushButton(centralwidget);
        twoD2_3D->setObjectName(QStringLiteral("twoD2_3D"));
        twoD2_3D->setGeometry(QRect(80, 100, 89, 25));
        optionWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(optionWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 287, 22));
        optionWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(optionWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        optionWindow->setStatusBar(statusbar);

        retranslateUi(optionWindow);

        QMetaObject::connectSlotsByName(optionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *optionWindow)
    {
        optionWindow->setWindowTitle(QApplication::translate("optionWindow", "MainWindow", nullptr));
        threeD2_2D->setText(QApplication::translate("optionWindow", "3D to 2D", nullptr));
        twoD2_3D->setText(QApplication::translate("optionWindow", "2D to 3D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optionWindow: public Ui_optionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONWINDOW_H
