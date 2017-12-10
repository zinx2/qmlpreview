#include "widget_menubar.h"

WidgetMenubar::WidgetMenubar(QWidget *parent) :
	WWidget(parent)
{
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	mainWidget->setStyleSheet("background-color:" + d->c().background);

	mainHBox = new QHBoxLayout;
	mainHBox->addWidget(mainWidget);
	mainHBox->layout()->setMargin(0);
	mainHBox->layout()->setContentsMargins(7, 0, 0, 0);
	this->setLayout(mainHBox);

	mainWidget->setLayout(new QHBoxLayout);
	mainWidget->layout()->setMargin(0);
	mainWidget->layout()->setAlignment(Qt::AlignLeft);

	m_btnAdd = createButton(":/imgs/btn_add.png");
	m_btnRemove = createButton(":/imgs/btn_remove.png");
	m_btnRefresh = createButton(":/imgs/btn_refresh.png");
	m_btnClearLog = createButton(":/imgs/btn_clear.png");
	m_btnZoomIn = createButton(":/imgs/btn_zoom_in.png");
	m_btnZoomOut = createButton(":/imgs/btn_zoom_out.png");
	m_btnFullScreen = createButton(":/imgs/btn_fullscreen.png");

	QWidget* widgetEdit = new QWidget;
	widgetEdit->setLayout(new QVBoxLayout);
	widgetEdit->setContentsMargins(0, -7, 0, 0);
	widgetEdit->layout()->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	
	m_editWidth = new QLineEdit;
	m_editHeight = new QLineEdit;
	widgetEdit->layout()->addWidget(createSizeArea(m_editWidth, "width  :", m->itemFixedWidth()));
	widgetEdit->layout()->addWidget(createSizeArea(m_editHeight, "height :", m->itemFixedHeight()));
	mainWidget->layout()->addWidget(widgetEdit);

	connect(m, SIGNAL(fullChanged()), this, SLOT(full()));
	connect(m_editWidth, SIGNAL(textChanged(QString)), this, SLOT(setItemWidth(QString)));
	connect(m_editHeight, SIGNAL(textChanged(QString)), this, SLOT(setItemHeight(QString)));
}
void WidgetMenubar::setItemWidth(QString value)
{
	m->setItemFixedWidth(value.toInt());
}
void WidgetMenubar::setItemHeight(QString value)
{
	m->setItemFixedHeight(value.toInt());
}

QPushButton* WidgetMenubar::createButton(QString iconPath) {
	QPushButton* btn = new QPushButton(mainWidget);
	btn->setFixedSize(48, 48);

	QPixmap pixmap(iconPath);
	QIcon icon(pixmap);
	btn->setIcon(icon);
	btn->setIconSize(pixmap.rect().size() / 2);

	//QFont font = btn->font();
	//font.setPointSize(15);
	//btn->setFont(font);

	btn->setStyleSheet("color: white;");
	mainWidget->layout()->addWidget(btn);

	return btn;
}
QWidget* WidgetMenubar::createSizeArea(QLineEdit* edit, QString name, int value)
{
	QWidget* wdEdit = new QWidget;
	wdEdit->setFixedSize(150, 30);
	//wdEdit->setStyleSheet("background-color:blue");
	wdEdit->setLayout(new QHBoxLayout);
	wdEdit->layout()->setMargin(0);
	wdEdit->layout()->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	edit->setStyleSheet("background-color: white");
	edit->setMaxLength(4);
	edit->setFixedHeight(20);
	edit->setFixedWidth(50);
	edit->setText(QString::number(value));

	QLabel* lbName = new QLabel(name);
	lbName->setFixedSize(50, 25);
	lbName->setStyleSheet("color:white");

	QLabel* lbPx = new QLabel("px");
	lbPx->setFixedSize(50, 25);
	lbPx->setStyleSheet("color:white");

	wdEdit->layout()->addWidget(lbName);
	wdEdit->layout()->addWidget(edit);
	wdEdit->layout()->addWidget(lbPx);
	
	
	return wdEdit;
}

void WidgetMenubar::full()
{
	/* BECAME FULL MODE */
	if (m->full()) {
		QPixmap pixmap(":/imgs/btn_fullscreen_exit.png");
		QIcon icon(pixmap);
		m_btnFullScreen->setIcon(icon);
		m_btnFullScreen->setIconSize(pixmap.rect().size() / 2);
	}
	else {
		QPixmap pixmap(":/imgs/btn_fullscreen.png");
		QIcon icon(pixmap);
		m_btnFullScreen->setIcon(icon);
		m_btnFullScreen->setIconSize(pixmap.rect().size() / 2);
	}
}
