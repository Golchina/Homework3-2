#include <QtCore/QCoreApplication>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow win(800, 600);
	win.show();

	return a.exec();
}
