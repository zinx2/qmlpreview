#include "screeninfo.h"
#include <QScreen>
#include <QGuiApplication>

#if defined(Q_OS_ANDROID)
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

ScreenInfo::ScreenInfo(/*int dpWidth,*/QObject *parent)
  : QObject(parent)
{
  refDpi      = 96;
  refHeight   = 1776.;
  refWidth    = 1080.;
  rect        = qApp->primaryScreen()->geometry();
  width       = qMin(rect.width(), rect.height());
  height      = qMax(rect.width(), rect.height());
  dpi         = qApp->primaryScreen()->logicalDotsPerInch();
  hdpi        = qApp->primaryScreen()->physicalDotsPerInch();
  m_ratio     = qMin(height/refHeight, width/refWidth);
  //m_ratioFont = qMin(heightrefDpi/(dpirefHeight), widthrefDpi/(dpirefWidth));

  dpiFactor = 2.0 / 3.0;
  #if defined(Q_OS_WIN)
    dpiFactor = dpi / 96;
  #elif defined(Q_OS_ANDROID)
    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject resources = activity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
    QAndroidJniObject displayMetrics = resources.callObjectMethod("getDisplayMetrics", "()Landroid/util/DisplayMetrics;");
    qreal densityDpi  = displayMetrics.getField<int>("densityDpi");
    qreal density     = displayMetrics.getField<float>("density");
    dpiFactor = 2.0 / 3.0 * density;
    /*if(densityDpi == 120) //DENSITY_LOW
      dpiFactor = 0.75 / density;
    else if(densityDpi == 160) //DENSITY_MEDIUM
      dpiFactor = 1.0 / density;
    else if(densityDpi == 240) //DENSITY_HIGH
      dpiFactor = 1.5 / density;
    else if(densityDpi == 320) //DENSITY_XHIGH
      dpiFactor = 2.0 / density;
    else if(densityDpi == 480) //DENSITY_XXHIGH
      dpiFactor = 3.0 / density;
    else if(densityDpi == 640) //DENSITY_XXXHIGH
      dpiFactor = 4.0 / density;*/
  #endif
}

ScreenInfo::~ScreenInfo()
{

}

QSize ScreenInfo::screenSize() const
{
  return QSize(width, height);
}

qreal ScreenInfo::pt(double val) const
{
   return val * dpiFactor;
}

qreal ScreenInfo::px(double val) const
{
  return val;
}

qreal ScreenInfo::widthPercent(double proportion) const
{
  return width * proportion;
}

qreal ScreenInfo::heightPercent(double proportion) const
{
  return height * proportion;
}

QString ScreenInfo::log() const
{
	return "hahahah";
}
