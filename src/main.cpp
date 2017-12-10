#include "mainwindow.h"
#include <QApplication>
#include "qml_viewer.h"
#include "screeninfo.h"
#include "screeninfo2.h"
#include "Option.h"
#include "model.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ScreenInfo scrInfo;
	ScreenInfo2 scrInfo2;


	QmlViewer* qViewer = QmlViewer::instance();    
	qViewer->rootContext()->setContextProperty("scr", &scrInfo);
	qViewer->rootContext()->setContextProperty("di", &scrInfo2);

	Option* option = new Option(qViewer->engine(), qViewer);
	qmlRegisterType<Option>("option", 1, 0, "Option");
	qViewer->rootContext()->setContextProperty("opt", option);


	//qViewer->show();



	MainWindow w;
	w.show();

	//qViewer->show();
	//QQuickWidget *view = new QQuickWidget;
	//view->setSource(QUrl::fromLocalFile("D:/dev/qt/qmlpreview/Tt.qml"));
	//view->rootContext()->setContextProperty("applicationData", &data);

	//view->show();




	return a.exec();
}
