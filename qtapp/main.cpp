//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include<QApplication>
#include <QtUiTools>

QWidget* loadUiFile()
{
    QUiLoader loader;

    QFile file("/home/sushant/Desktop/courses/cop290/COP290/qtapp/mainwindow.ui");
    file.open(QFile::ReadOnly);

    QWidget *formWidget = loader.load(&file);
    file.close();

    return formWidget;
}

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    const QString labelName= "Label1";
//    QGuiApplication app(argc, argv);
    QApplication app(argc,argv);
    QWidget *mainWindow=loadUiFile();
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
    QPixmap pixmap(200,200);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    QPen Red((QColor(255,0,0)),1);
    painter.setPen(Red);
    painter.drawLine(50,50,100,100);
    mainWindow->findChild<QLabel *>("Label1")->setPixmap(pixmap);
    mainWindow->show();
    return app.exec();
}
