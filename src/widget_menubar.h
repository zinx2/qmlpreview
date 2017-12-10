#pragma once
#include "wrapped_widget.h"

class WidgetMenubar : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetMenubar(QWidget *parent = 0);	
	QPushButton* btnAdd() { return m_btnAdd; }
	QPushButton* btnRemove() { return m_btnRemove; }
	QPushButton* btnRefresh() { return m_btnRefresh;  }
	QPushButton* btnClearLog() { return m_btnClearLog; }
	QPushButton* btnZoomIn() { return m_btnZoomIn; }
	QPushButton* btnZoomOut() { return m_btnZoomOut; }
	QPushButton* btnFullScreen() { return m_btnFullScreen; }
	//QPushButton* btnFullScreenExit() { return m_btnFullScreenExit; }

	public slots:
	void full();
	void setItemWidth(QString value);
	void setItemHeight(QString value);
	
private:
	QHBoxLayout* mainHBox;
	QWidget* mainWidget;

	QPushButton* m_btnRefresh;
	QPushButton* m_btnAdd;
	QPushButton* m_btnRemove;
	QPushButton* m_btnClearLog;
	QPushButton* m_btnZoomIn;
	QPushButton* m_btnZoomOut;
	QPushButton* m_btnFullScreen;
	//QPushButton* m_btnFullScreenExit;
	
	QPushButton* createButton(QString iconPath);
	QWidget* createSizeArea(QLineEdit* edit, QString name, int value);

	QLineEdit* m_editWidth;
	QLineEdit* m_editHeight;
};