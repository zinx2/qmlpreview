#pragma once

#include <QObject>
#include <QSize>
#include <QRect>

class ScreenInfo : public QObject
{
  Q_OBJECT

public:
  ScreenInfo(/*int displayWidth,*/QObject *parent = NULL);
  ~ScreenInfo();

  Q_INVOKABLE QSize  screenSize() const;
  Q_INVOKABLE qreal  pt(double val) const;
  Q_INVOKABLE qreal  px(double val) const;
  Q_INVOKABLE qreal  widthPercent(double proportion) const;
  Q_INVOKABLE qreal  heightPercent(double proportion) const;
	Q_INVOKABLE QString log() const;

private:
  qreal refDpi     ;
  qreal refHeight  ;
  qreal refWidth   ;
  QRect rect       ;
  int   width      ;
  int   height     ;
  qreal dpi        ;
  qreal hdpi       ;
  qreal m_ratio    ;
  qreal m_ratioFont;
  qreal dpiFactor  ;

};

//#endif // SCREENINFO_H

