#include "qml_viewer.h"
#include "model.h"
#include "design.h"
#include "model.h"
#include <qqml.h>
#include "Option.h"
#include "screeninfo.h"
#include <QTime>
#include <QQmlContext>
#include <QQuickItem>

QmlViewer* QmlViewer::m_instance = nullptr;
QmlViewer* QmlViewer::instance(QWidget *parent) {
	if (m_instance == nullptr) {
		m_instance = new QmlViewer(parent);
	}
	return m_instance;
}
QmlViewer::QmlViewer(QWidget *parent) :
	QQuickWidget(parent)
{
	//dg.start();

	d = Design::instance();
	m = Model::instance();
	m->setScale(1);	
	connect(d, SIGNAL(previewWidthChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(previewHeightChanged()), this, SLOT(resize()));
	connect(m, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
	connect(m, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
	connect(m, SIGNAL(scaleChanged()), this, SLOT(resize()));

	this->setClearColor(QColor(Design::instance()->c().preview));
	this->setSource(QUrl::fromLocalFile("D:/dev/qt/qmlpreview/desk.qml"));

}

void QmlViewer::initialize()
{		
	if (this->rootObject() != nullptr) {
		this->engine()->clearComponentCache();	/* CLEAR THE EXISTING QML. */
		delete this->rootObject();
	}
	
	this->setSource(QUrl::fromLocalFile(QFileInfo(Model::instance()->path()).absoluteFilePath()));
	
	/* ONLY THE CASE THAT CAN CREATE OBJECT EXECUTE.  */
	if (this->rootObject() != nullptr) {		
		this->rootObject()->setTransformOrigin(QQuickItem::TransformOrigin::TopLeft);		
		
		resize();

		QString message = "Loaded Successfully.";
		if (this->rootObject()->width() == 0 || this->rootObject()->height() == 0)
			message = "Loaded, But please confirm SIZE of the component.";
		m->setMessage(message);
	}
	
}

/*
	 OVERRIDEN 'resizeEvent' FUNCTION IS STRETCH CHILD WITH PARENT.
	 SO, PLEASE DON'T DEFINE THE FUNCTION.
*/
void QmlViewer::resize()
{
	if (this->rootObject() == nullptr) return;

	int itemWidth = this->rootObject()->width();
	int itemHeight = this->rootObject()->height();

	if (itemWidth == 0 || itemHeight == 0) {
		itemWidth = m->itemFixedWidth();
		itemHeight = m->itemFixedHeight();
		this->rootObject()->parentItem()->setWidth(itemWidth);
		this->rootObject()->parentItem()->setHeight(itemHeight);
	}
	this->rootObject()->setScale(m->scale());
	itemWidth = this->rootObject()->width() * m->scale();
	if(itemWidth == 0)
		itemWidth = m->itemFixedWidth();
	
	itemHeight = this->rootObject()->height() * m->scale();
	if (itemHeight == 0)
		itemHeight = m->itemFixedHeight();
		
	m->setScaledItemWidth(itemWidth);
	m->setScaledItemHeight(itemHeight);
	this->setFixedSize(itemWidth, itemHeight);
}
QmlViewer::~QmlViewer()
{	
	//if (this->rootObject() != nullptr) {
	//	qDeleteAll(this->rootObject()->children());
	//	delete this->rootObject();
	//}
	//delete this->rootObject();
	if (m != nullptr) m = nullptr;
	if (d != nullptr) d = nullptr;
}

void QmlViewer::removeObj()
{
	//if (this->rootObject() != nullptr) {
		//qDeleteAll(this->rootObject()->children());
		//QString ss = this->rootObject()->objectName();
		//QQuickItem * i = this->rootObject();
		//qDebug() << "TYPE:: " << i->metaObject()->className();
		//qDebug() << this->rootObject()->objectName();
		//delete this->rootObject();
	//}
}
void QmlViewer::zoomIn()
{
	if (m->scale() >= 3.0) m->setScale(3.0);
	m->setScale(m->scale() + 0.1);
	resize();
}
void QmlViewer::zoomOut()
{
	if (m->scale() <= 0.3) m->setScale(0.3);
	m->setScale(m->scale() - 0.1);
	resize();
}
