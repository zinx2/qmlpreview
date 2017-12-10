#include "widget_explorer.h"
#include "binding_listview.h"
#include "design.h"
WidgetExplorer::WidgetExplorer(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + Design::instance()->c().explorer);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);
	
	mainWidget->setLayout(new QVBoxLayout);
	mainWidget->layout()->setMargin(0);
	blView = new BindingListView;
	mainWidget->layout()->addWidget(blView);
}
