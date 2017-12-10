#pragma once

#include <QTime>
#include <QDebug>
class Debug {
public:	
	void start() { m_time.start(); }
	void elapsed(QString h = "") {		
		qDebug() << h << m_time.elapsed();
	}

private:
	QTime m_time;
};