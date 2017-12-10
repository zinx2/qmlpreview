#pragma once
#include "wrapped_widget.h"

class WidgetLog : public WWidget
{
	Q_OBJECT

public:
	explicit WidgetLog(QWidget *parent = 0);
	~WidgetLog();

	public slots:
	void log();
	void resizeWidth();
	void resizeHeight();
	void clear();

private:
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	QTextEdit* logWindow;
	//void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};