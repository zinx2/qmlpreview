#include "widget_preview.h"
#include "widget_viewer.h"
#include <QQmlContext>
#include "Option.h"
#include "screeninfo.h"
#include "qml_viewer.h"
WidgetPreview::WidgetPreview(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout);
	this->layout()->setMargin(0);
	this->layout()->setAlignment(Qt::AlignCenter);

	viewer = new WidgetViewer(this);
	this->layout()->addWidget(viewer);	

}
WidgetPreview::~WidgetPreview()
{

}
