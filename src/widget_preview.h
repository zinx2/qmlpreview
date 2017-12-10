#pragma once
#include "wrapped_widget.h"

class WidgetViewer;
class QmlViewer;
class WidgetPreview : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetPreview(QWidget *parent = 0);
	~WidgetPreview();

private:
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	WidgetViewer* viewer;
	//QmlViewer* q = nullptr;
};