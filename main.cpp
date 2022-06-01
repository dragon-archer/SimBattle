#include "pch.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator qtTranslator, appTranslator;
	if(qtTranslator.load(":/localisation/qtbase_zh_CN")) {
		qDebug() << "Load Qt Translation";
		a.installTranslator(&qtTranslator);
	}
	if(appTranslator.load(":/localisation/SimBattle_zh_CN")) {
		qDebug() << "Load SimBattle Translation";
		a.installTranslator(&appTranslator);
	}
	MainWindow w;
	w.show();
	return a.exec();
}
