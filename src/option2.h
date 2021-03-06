#pragma once
#include <QObject>

class Option2 : public QObject
{
Q_OBJECT
	Q_PROPERTY(bool ds    READ ds    WRITE setDs  NOTIFY dsChanged)

public:
	Option2(QObject* parent = 0) : QObject(parent) { }

	bool ds() { return m_designMode; }
	void setDs(bool val) { m_designMode = val; emit dsChanged(); }

signals:
	void dsChanged();

private:
	bool m_designMode;
};