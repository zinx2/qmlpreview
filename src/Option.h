#pragma once
#include <qqml.h>
#include <QElapsedTimer>

#include <QQmlEngine>

class Option : public QObject
{
  Q_OBJECT    
    Q_PROPERTY(bool ds    READ ds    WRITE setDs  NOTIFY dsChanged)

public:
  Option(QQmlEngine* engine=NULL ,QObject *parent = NULL);
  Q_INVOKABLE void log(QString msg);
  Q_INVOKABLE void check(QString msg);
  Q_INVOKABLE QQmlComponent * component(QString qml);

  bool ds() { return m_designMode; }
  void setDs(bool val) { m_designMode = val; emit dsChanged(); }

signals:
  void dsChanged();

private:
  bool m_designMode;
	QQmlEngine * m_engine;
  QElapsedTimer elapsedTimer;
  qint64        elapsedCheck;

  static QHash<QString, QQmlComponent*> compHash;
};
