#include "widget_viewer.h"
#include "qml_viewer.h"
#include "screeninfo.h"
#include <QQmlContext>
#include <QQmlEngine>
#include "Option.h"
#include "screeninfo.h"
#include "qml_viewer.h"

WidgetViewer::WidgetViewer(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);
	this->layout()->setSpacing(0);
	this->layout()->setAlignment(Qt::AlignCenter);	
	
	wdInfo1 = new QWidget(this);
	wdInfo1->setFixedSize(d->previewWidth(), 30);
	//wdInfo1->setStyleSheet("background-color:rgb(0,255,0)");
	wdInfo1->setLayout(new QHBoxLayout);
	wdInfo1->layout()->setMargin(0);
	wdInfo1->setContentsMargins(0, 0, 0, 0);
	wdInfo1->setEnabled(false);
	this->layout()->addWidget(wdInfo1);

	/* SHOW FILE PATH */
	lbPath = new QLabel(wdInfo1);
	lbPath->setStyleSheet("color: white; background-color:rgba(0,0,0,0)");
	lbPath->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	lbPath->setContentsMargins(10, 0, 0, 0);
	wdInfo1->layout()->addWidget(lbPath);

	/* SHOW VIEW SIZE */
	lbSize = new QLabel(wdInfo1);
	lbSize->setStyleSheet("color: white; background-color:rgba(0,0,0,0)");
	lbSize->setAlignment(Qt::AlignCenter);
	wdInfo1->layout()->addWidget(lbSize);

	/* SHOW CURRENT SCALE */
	lbScale = new QLabel(wdInfo1);
	lbScale->setStyleSheet("color: white; background-color:rgba(0,0,0,0)");
	lbScale->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	lbScale->setContentsMargins(0, 0, 30, 0);
	wdInfo1->layout()->addWidget(lbScale);

	scrollArea = new QScrollArea(this);
	this->layout()->addWidget(scrollArea);

	mainWidget = new QWidget(this);
	mainWidget->setLayout(new QVBoxLayout);	
	mainWidget->layout()->setMargin(0);
	mainWidget->layout()->setAlignment(Qt::AlignCenter);
	mainWidget->layout()->addWidget(QmlViewer::instance());
	
	scrollArea->setWidget(mainWidget);
	scrollArea->setStyleSheet("border: 0px");	

	connect(m, SIGNAL(pathChanged()), this, SLOT(load()));
	connect(m, SIGNAL(pressedCtrlChanged()), this, SLOT(scroll()));
	connect(m, SIGNAL(scaleChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(previewWidthChanged()), this, SLOT(resize()));
	connect(d, SIGNAL(previewHeightChanged()), this, SLOT(resize()));
}

WidgetViewer::~WidgetViewer()
{
	//delete QmlViewer::instance();
	//if (lbScale != nullptr) {
	//	delete lbScale;
	//	lbScale = nullptr;
	//}

	//if (lbSize != nullptr) {
	//	delete lbSize;
	//	lbSize = nullptr;
	//}

	//if (wdInfo1 != nullptr)
	//{
	//	qDeleteAll(wdInfo1->layout()->children());
	//	qDeleteAll(wdInfo1->children());
	//	delete wdInfo1;
	//	qDeleteAll(this->layout()->children());
	//}

	//qDeleteAll(mainWidget->layout()->children());
	//delete mainWidget;

	//delete scrollArea;

	//qDeleteAll(this->layout()->children());
	//qDeleteAll(this->children());
}
void WidgetViewer::resize()
{
	wdInfo1->setFixedSize(d->previewWidth(), 30);

	int mWidth = d->previewWidth(); 
	if (d->previewWidth() < m->scaledItemWidth()) {
		mWidth = m->scaledItemWidth();
	}

	int mHeight = d->previewHeight();
	if (d->previewHeight() < m->scaledItemHeight()) {
		mHeight = m->scaledItemHeight();
	}
	
	mainWidget->setFixedSize(mWidth, mHeight - 30);

	setInfo();
	update();
}
void WidgetViewer::load()
{
	qDeleteAll(mainWidget->layout()->children());

//	QmlViewer::instance()->removeObj();
	QmlViewer::instance()->initialize();
	
	resize();
}

void WidgetViewer::scroll() {
	if (m->pressedCtrl()) {
		scrollArea->verticalScrollBar()->setEnabled(false);
		scrollArea->horizontalScrollBar()->setEnabled(false);
	}
	else {
		scrollArea->verticalScrollBar()->setEnabled(true);
		scrollArea->horizontalScrollBar()->setEnabled(true);
	}
}

void WidgetViewer::wheelEvent(QWheelEvent *event)
{
	if (!m->pressedCtrl())
		return;

	/* 30% ~ 300% */
	if (m->scale() <= 0.3) m->setScale(0.3);
	else if (m->scale() >= 3.0) m->setScale(3.0);
	m->setScale(m->scale() + event->delta() / 1200.0);
}

void WidgetViewer::setInfo()
{
	lbPath->setText("<font color=" + d->c().selected + ">PATH: </font>" + m->path());
	lbScale->setText("<font color=" + d->c().selected + ">SCALE: </font>" +
		QString("%1%").arg(m->scale() * 100));
	lbSize->setText("<font color=" + d->c().selected + ">SIZE: </font>" +
		QString("%1 X %2").arg(m->scaledItemWidth()).arg(m->scaledItemHeight()));
}
