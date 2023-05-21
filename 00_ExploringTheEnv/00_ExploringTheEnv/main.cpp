//#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

//#include <QLocale>
//#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QWidget Part
    QWidget* widget = new QWidget();
    widget->setWindowTitle("this is my program");
    widget->setGeometry(100,200,400,400);

    // QLabel Part
    QLabel* name_label = new QLabel("this is sparta: ",widget);
    name_label->move(50,50);

    // fonts
    QFont font("Arial", 15, QFont::Bold);
    name_label->setFont(font);

    // fonts using like CSS
    name_label->setStyleSheet("color:red; font:bold 20px;");

    // in arabic
    //auto text = name_label->text();
    //name_label->setText(u8"الاسم");




    /*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "00_ExploringTheEnv_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    */
    widget->show();
    return a.exec();
}
