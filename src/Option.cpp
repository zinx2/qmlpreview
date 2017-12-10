#include "Option.h"
#include <qdebug>
#include <QQmlEngine>
#include <QQmlComponent>

QHash<QString, QQmlComponent*> Option::compHash;

Option::Option(QQmlEngine* engine , QObject *parent) : QObject(parent)
{
  m_engine = engine;
  m_designMode = true;
  elapsedTimer.start();
  elapsedCheck = 0;
}

void Option::log( QString msg )
{
  qDebug() << msg;
}

void Option::check(QString msg)
{
  qint64 tmp = elapsedCheck;
  qint64 curr = elapsedTimer.elapsed();

  qDebug() << "check:"<< msg << " : " << curr - tmp << " ms";
  elapsedCheck = curr;
}

Q_INVOKABLE QQmlComponent * Option::component(QString qml)
{
  check("1 " + qml);

  QString key = qml;
  key.toUpper();

  if(compHash.contains(key))
  {
    return compHash.value(key);
  }
  else
  {
    QQmlComponent *component = new QQmlComponent(m_engine,QUrl(QStringLiteral("qrc:/qml/")+ qml));
    compHash.insert(key, component);
    return component;
  }
  check("2 " + qml);

  return NULL;

  
  //return component;
}
