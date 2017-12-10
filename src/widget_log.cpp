#include "widget_log.h"
#include "model.h"
#include <sstream>
#include <QTextCodec>

void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(type);
	QByteArray localMsg = msg.toLocal8Bit();
	QString category = QString(context.category);
	if (!category.compare("qml") || !category.compare("default")) {
		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
		QString lmsg = QString::fromLocal8Bit(localMsg.constData());
		if (!lmsg.contains("iCCP")) {
			/* [LINE_NUMBER] FUNCTION_NAME : LOG_MESSAGE */
			
			QString log = 
				"<font color=#007acc>[" + QString::number(context.line) + "] </font>" +
				"<font color=#f39c11>" + QString::fromLocal8Bit(context.function) + " :</font> " +
				"<font color=#FFFFFF>" + lmsg + "</font>";			
			
			Model::instance()->setLog(log);
		}
	}

	//switch (type) {x`
	//case QtDebugMsg: {
	//	fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
	//	break;
	//}
	//case QtInfoMsg:
	//	fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
	//	break;
	//case QtWarningMsg:
	//	fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
	//	break;
	//case QtCriticalMsg:
	//	fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
	//	break;
	//case QtFatalMsg:
	//	fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
	//	abort();
	//}
}
WidgetLog::WidgetLog(QWidget *parent) :
	WWidget(parent)
{	
	qInstallMessageHandler(LogHandler);
	this->setGeometry(parent->geometry());
	this->setLayout(new QVBoxLayout);
	this->layout()->setMargin(0);
	this->layout()->setContentsMargins(5, 5, 5, 5);
	this->layout()->setAlignment(Qt::AlignTop);
	
	logWindow = new QTextEdit;
	logWindow->setSizePolicy(logWindow->sizePolicy().horizontalPolicy(), QSizePolicy::Fixed);
	logWindow->setWordWrapMode(QTextOption::WordWrap);
	logWindow->setStyleSheet("border: 0px;");
	logWindow->setReadOnly(true);
	this->layout()->layout()->addWidget(logWindow);

	connect(d, SIGNAL(logWidthChanged()), this, SLOT(resizeWidth()));
	connect(d, SIGNAL(logHeightChanged()), this, SLOT(resizeHeight()));
	connect(m, SIGNAL(logChanged()), this, SLOT(log()));
	connect(m, SIGNAL(logClear()), this, SLOT(clear()));
}
WidgetLog::~WidgetLog()
{
	//qDeleteAll(this->layout()->children());
	//qDeleteAll(this->children());
	delete d;
}
void WidgetLog::log()
{
	logWindow->append(m->log());
	logWindow->append("<font size='0px'>\n</font>");
	logWindow->verticalScrollBar()->setValue(logWindow->verticalScrollBar()->maximum());
}
void WidgetLog::clear()
{
	logWindow->clear();
}
void WidgetLog::resizeWidth()
{
	logWindow->setFixedWidth(d->logWidth());
}

void WidgetLog::resizeHeight()
{
	logWindow->setFixedHeight(d->logHeight());
}