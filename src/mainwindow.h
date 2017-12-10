#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qheader.h"
//#include "db_manager.h"
namespace Ui {
    class MainWindow;
}

class WidgetAdjustbar;
class WidgetExplorer;
class WidgetMenubar;
class WidgetStatusbar;
class WidgetPreview;
class WidgetLog;
class DBManager;
class Model; class Design;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    public slots:
    void initializeUI();
    void addProject();
    void removeProject();
    void refreshProject();
    void clearLog();
    void adjustVAbar(QMouseEvent *event);
    void adjustHAbar(QMouseEvent *event);
    void refresh();
    void zoomIn();
    void zoomOut();
    void full();
    void resize();

signals:
    void add(QString);
    void remove();

protected:

    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
		void keyReleaseEvent(QKeyEvent *event) override;
    /*void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;*/

private:
    Design* d;
    Ui::MainWindow *ui;
    int titleBarHeight;
    QWidget* frameExplorer;
    QWidget* framePreview;
    QWidget* frameLog;
    QWidget* frameVAdjustbar;
    QWidget* frameHAdjustbar;
    QWidget* frameMenubar;
    QWidget* frameStatusbar;

    WidgetAdjustbar* widgetVAdjustbar;
    WidgetAdjustbar* widgetHAdjustbar;
    WidgetExplorer* widgetExplorer;
    WidgetMenubar* widgetMenubar;
    WidgetStatusbar* widgetStatusbar;
    WidgetPreview* widgetPreview;
    WidgetLog* widgetLog;

    DBManager* db;
    Model* m;
    bool initedUI = false;

    int tmp_explorerWidth;
    int tmp_logHeight;
    int tmp_borderFixedSize;

    void setWidget(QWidget* w, QRect geometry, QString color = "blue");

    void msg(QString m);
    void connections();

};

#endif // MAINWINDOW_H
