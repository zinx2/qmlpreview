#include "widget_statusbar.h"

WidgetStatusbar::WidgetStatusbar(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + d->c().selected);

	mainHBox = new QHBoxLayout;
	mainHBox->addWidget(mainWidget);
	mainHBox->setMargin(0);
	this->setLayout(mainHBox);

	mainWidget->setLayout(new QHBoxLayout);
	mainWidget->layout()->setMargin(0);
	mainWidget->layout()->setAlignment(Qt::AlignLeft);
		
	lbStatus = new QLabel("", mainWidget);
	lbStatus->setFixedWidth(this->size().width() * 0.5);
	lbStatus->setFixedHeight(this->size().height());
	lbStatus->setContentsMargins(10, 0, 0, 0);
	lbStatus->setStyleSheet("color: white;");
	mainWidget->layout()->addWidget(lbStatus);

	lbDate = new QLabel;
	lbDate->setFixedWidth(this->size().width() * 0.5);
	lbDate->setFixedHeight(this->size().height());
	lbDate->setContentsMargins(0, 0, 10, 0);
	lbDate->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	lbDate->setStyleSheet("color: white;");
	mainWidget->layout()->addWidget(lbDate);
	
	connect(m, SIGNAL(messageChanged()), this, SLOT(update()));
	connect(d, SIGNAL(statusbarWidthChanged()), this, SLOT(resize()));
}

void WidgetStatusbar::resize()
{
	lbStatus->setFixedWidth(d->statusbarWidth() * 0.5);
	lbDate->setFixedWidth(d->statusbarWidth() * 0.5);
}
void WidgetStatusbar::update() {
	lbStatus->setText(m->message());
	lbDate->setText(m->date());
}