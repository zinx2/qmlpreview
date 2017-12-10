#pragma once
#include "wrapped_widget.h"

class QmlViewer;

class WidgetViewer : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetViewer(QWidget *parent = 0);
	~WidgetViewer();

	public slots:
	void load();
	void scroll();
	void resize();
	
protected:
	void wheelEvent(QWheelEvent *event);
private:
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	//QmlViewer* qmlViewer = nullptr;
	QScrollArea* scrollArea;
	Debug dg;

	QWidget* wdInfo1 = nullptr;
	QLabel* lbScale = nullptr;
	QLabel* lbSize = nullptr;
	QLabel* lbPath = nullptr;	
	
	QmlViewer* qViewer = nullptr;

	void setInfo();
};