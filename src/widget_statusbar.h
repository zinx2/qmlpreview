#pragma once
#include "wrapped_widget.h"

class WidgetStatusbar : public WWidget
{
	Q_OBJECT
public:
	explicit WidgetStatusbar(QWidget *parent = 0);

	public slots:
	void update();
	void resize();

private:
	QHBoxLayout* mainHBox;
	QWidget* mainWidget;
	QLabel* lbStatus;	
	QWidget* dateWidget;
	QLabel* lbDate;
};