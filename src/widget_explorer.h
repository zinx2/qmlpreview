#pragma once
#include "wrapped_widget.h"

class BindingListView;
class WidgetExplorer : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetExplorer(QWidget *parent = 0);	

private:
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	BindingListView* blView;
};