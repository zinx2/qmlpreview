#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widget_adjustbar.h"
#include "widget_explorer.h"
#include "widget_menubar.h"
#include "widget_statusbar.h"
#include "widget_preview.h"
#include "widget_log.h"
#include "db_manager.h"
#include "model.h"
#include "design.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    d = Design::instance();
    d->setTitleBarHeight(this->style()->pixelMetric(QStyle::PM_TitleBarHeight, 0, this));
    d->setWindowWidth(d->MIM_WINDOW_WIDTH); d->setWindowHeight(d->MIM_WINDOW_HEIGHT);

    this->setMinimumSize(d->MIM_WINDOW_WIDTH, d->MIM_WINDOW_HEIGHT);
    this->setGeometry(QRect(100, 100, d->windowWidth(), d->windowHeight()));
    this->setStyleSheet("background-color:" + d->c().explorer);		
    ui->setupUi(this);

    frameMenubar = ui->widget_menuBar;
    frameExplorer = ui->widget_explorer;
    framePreview = ui->widget_preview;
    frameLog = ui->widget_log;
    frameVAdjustbar = ui->widget_adjustVBar;
    frameHAdjustbar = ui->widget_adjustHBar;
    frameStatusbar = ui->widget_statusBar;

    m = Model::instance();
    db = new DBManager();
    db->selectDB();
    for (Explorer* project : m->projects())
        db->modifyExtended(project->id(), 0);

}

void MainWindow::setWidget(QWidget* w, QRect geometry, QString color)
{
    w->setGeometry(geometry);
    w->setStyleSheet("background-color:" + color);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if (!initedUI) {
        initializeUI();
        msg("Ready.");
        return;
    }

    QSize newSize = e->size();
    QSize oldSize = e->oldSize();
    d->setWindowWidth(newSize.width());
    d->setWindowHeight(newSize.height());

    resize();
}

void MainWindow::resize() {

    int x = 0; int y = 0; int w = 0; int h = 0;
    QRect geo;
    int sleepValue = 5;


    geo = frameMenubar->geometry();
    x = 0;
    y = 0;
    w = d->windowWidth(); d->setMenubarWidth(w);
    h = geo.height();
    frameMenubar->setGeometry(x, y, w, h);
    widgetMenubar->setGeometry(0, 0, w, h);
    //QThread::msleep(sleepValue);

    geo = frameExplorer->geometry();
    x = 0;
    y = geo.y();
    w = d->explorerWidth(); // geo.width();
    h = d->windowHeight() - d->menubarHeight() - d->statusbarHeight(); d->setExplorerHeight(h);
    frameExplorer->setGeometry(x, y, w, h);
    widgetExplorer->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);


    geo = frameVAdjustbar->geometry();
    x = geo.x();
    y = geo.y();
    w = d->borderFixedSize(); // geo.width();
    h = d->windowHeight() - d->menubarHeight() - d->statusbarHeight();
    frameVAdjustbar->setGeometry(x, y, w, h);
    widgetVAdjustbar->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);


    geo = framePreview->geometry();
    x = geo.x();
    y = geo.y();
    w = d->windowWidth() - d->explorerWidth() - d->borderFixedSize(); d->setPreviewWidth(w);
    h = d->windowHeight() - d->menubarHeight() - d->borderFixedSize() - d->logHeight() - d->statusbarHeight(); d->setPreviewHeight(h);
    framePreview->setGeometry(x, y, w, h);
    widgetPreview->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);


    geo = frameHAdjustbar->geometry();
    x = geo.x();
    y = d->menubarHeight() + d->previewHeight(); //geo.y() + sY;
    w = d->previewWidth();
    h = d->borderFixedSize();// geo.height();
    frameHAdjustbar->setGeometry(x, y, w, h);
    widgetHAdjustbar->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);


    geo = frameLog->geometry();
    x = geo.x();
    y += d->borderFixedSize();//geo.y() + sY;
    /*w = geo.width() + sX;*/ d->setLogWidth(w);
    h = geo.height();
    frameLog->setGeometry(x, y, w, h);
    widgetLog->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);

    geo = frameStatusbar->geometry();
    x = 0;
    y = d->windowHeight() - d->statusbarHeight();
    w = d->windowWidth(); d->setStatusbarWidth(w);
    h = d->statusbarHeight(); // geo.height();
    frameStatusbar->setGeometry(x, y, w, h);
    widgetStatusbar->setGeometry(0, 0, w, h);
    QThread::msleep(sleepValue);
}
void MainWindow::refresh() {
    qDeleteAll(frameMenubar->children());
    qDeleteAll(frameExplorer->children());
    qDeleteAll(framePreview->children());
    qDeleteAll(frameLog->children());
    qDeleteAll(frameVAdjustbar->children());
    qDeleteAll(frameHAdjustbar->children());
    qDeleteAll(frameStatusbar->children());

    d->initialize();
    initializeUI();
}

MainWindow::~MainWindow()
{
    /* Delet model instances. */
    Model* m = Model::instance();
    for (int i = 0; i < m->projects().size(); i++)
        delete m->projects()[i];

    //qDeleteAll(frameMenubar->children());
    //qDeleteAll(frameExplorer->children());
    //qDeleteAll(framePreview->children());
    //qDeleteAll(frameLog->children());
    //qDeleteAll(frameVAdjustbar->children());
    //qDeleteAll(frameHAdjustbar->children());
    //qDeleteAll(frameStatusbar->children());

    delete db;
    delete ui;
}

void MainWindow::initializeUI()
{
    int sleepValue = 3;
    int x = 0; int y = 0; int w = 0; int h = 0;

    /* MENU BAR */
    w = d->menubarWidth(); h = d->menubarHeight();
    setWidget(frameMenubar, QRect(x, y, w, h), d->c().background);
    widgetMenubar = new WidgetMenubar(frameMenubar);
    QVBoxLayout* vBoxMenubar = new QVBoxLayout(frameMenubar);
    vBoxMenubar->setMargin(0);
    vBoxMenubar->addWidget(widgetMenubar);
    QThread::msleep(sleepValue);

    /* EXPLORER */
    y += h; w = d->explorerWidth(); h = d->explorerHeight();
    setWidget(frameExplorer, QRect(x, y, w, h), d->c().explorer);
    widgetExplorer = new WidgetExplorer(frameExplorer);
    QVBoxLayout* vBoxExplorer = new QVBoxLayout(frameExplorer);
    vBoxExplorer->setMargin(0);
    vBoxExplorer->addWidget(widgetExplorer);
    QThread::msleep(sleepValue);

    /* VERTICAL ADJUST BAR */
    x += w; w = d->borderFixedSize();
    setWidget(frameVAdjustbar, QRect(x, y, w, h), d->c().adjustbar);
    widgetVAdjustbar = new WidgetAdjustbar(Qt::Vertical, frameVAdjustbar);
    QVBoxLayout* vBox1 = new QVBoxLayout(frameVAdjustbar);
    vBox1->setMargin(0);
    vBox1->addWidget(widgetVAdjustbar);
    QThread::msleep(sleepValue);

    /* PREVIEW */
    x += w;	w = d->previewWidth(); h = d->previewHeight();
    setWidget(framePreview, QRect(x, y, w, h), d->c().preview);
    widgetPreview = new WidgetPreview(framePreview);
    framePreview->setLayout(new QVBoxLayout);
    framePreview->layout()->setMargin(0);
    //framePreview->layout()->setAlignment(Qt::AlignTop);
    framePreview->layout()->addWidget(widgetPreview);
    QThread::msleep(sleepValue);

    /* HORIZONTAL ADJUST BAR */
    y += h; h = d->borderFixedSize();
    setWidget(frameHAdjustbar, QRect(x, y, w, h), d->c().adjustbar);
    widgetHAdjustbar = new WidgetAdjustbar(Qt::Horizontal, frameHAdjustbar);
    QVBoxLayout* vBox2 = new QVBoxLayout(frameHAdjustbar);
    vBox2->setMargin(0);
    vBox2->addWidget(widgetHAdjustbar);
    QThread::msleep(sleepValue);

    /* LOG VIEW */
    y += h; h = d->logHeight();
    setWidget(frameLog, QRect(x, y, w, h), d->c().explorer);
    widgetLog = new WidgetLog(frameLog);
    QVBoxLayout* vBoxLog = new QVBoxLayout(frameLog);
    vBoxLog->setMargin(0);
    vBoxLog->addWidget(widgetLog);
    QThread::msleep(sleepValue);

    /* STATUS BAR */
    x = 0; y = d->windowHeight() - d->statusbarHeight();
    w = d->statusbarWidth(); h = d->statusbarHeight();
    setWidget(frameStatusbar, QRect(x, y, w, h), d->c().selected);
    widgetStatusbar = new WidgetStatusbar(frameStatusbar);
    QVBoxLayout* vBoxStatusbar = new QVBoxLayout(frameStatusbar);
    vBoxStatusbar->setMargin(0);
    vBoxStatusbar->addWidget(widgetStatusbar);
    QThread::msleep(sleepValue);

    /* TO ADJUST. */
    resize();
    connections();
    initedUI = true;
}

void MainWindow::adjustVAbar(QMouseEvent *event)
{
    QRect g = frameVAdjustbar->geometry();
    int currentX = frameVAdjustbar->geometry().x();
    int movedX = event->x();

    int updatedX = currentX + movedX;

    if ((d->windowWidth() - d->pt(100)) > d->pt(updatedX) && d->pt(updatedX) > d->pt(50)) {
        frameVAdjustbar->setGeometry(updatedX, g.y(), g.width(), g.height());

        int sleepValue = 3;
        int x = 0; int y = 0; int w = 0; int h = 0;
        x = 0;
        y = g.y();
        w = g.width() + updatedX - 7; d->setExplorerWidth(w);
        h = g.height();
        frameExplorer->setGeometry(x, y, w, h);
        widgetExplorer->setGeometry(0, 0, w, h);
        QThread::msleep(sleepValue);

        g = framePreview->geometry();
        x = g.x() + movedX;
        y = g.y();
        w = g.width() - movedX; d->setPreviewWidth(w);
        h = g.height();
        framePreview->setGeometry(x, y, w, h);
        QThread::msleep(sleepValue);

        g = frameHAdjustbar->geometry();
        x = g.x() + movedX;
        y = g.y();
        w = g.width() - movedX;
        h = g.height();
        frameHAdjustbar->setGeometry(x, y, w, h);
        widgetHAdjustbar->setGeometry(0, 0, w, h);
        QThread::msleep(sleepValue);

        g = frameLog->geometry();
        x = g.x() + movedX;
        y = g.y();
        w = g.width() - movedX; d->setLogWidth(w);
        h = g.height();
        frameLog->setGeometry(x, y, w, h);
        QThread::msleep(sleepValue);
    }
}

void MainWindow::adjustHAbar(QMouseEvent* e)
{
    QRect g = frameHAdjustbar->geometry();
    int currentY = frameHAdjustbar->geometry().y();
    int movedY = e->y();

    int updatedY = currentY + movedY;
    int limitedY1 = d->pt(150) - d->menubarHeight();
    int limitedY2 = d->windowHeight() - d->statusbarHeight() - d->pt(50);
    if (limitedY2 > d->pt(updatedY) && d->pt(updatedY) > limitedY1) {

        frameHAdjustbar->setGeometry(g.x(), updatedY, g.width(), g.height());

        int sleepValue = 3;
        int x = 0; int y = 0; int w = 0; int h = 0;

        g = framePreview->geometry();
        x = g.x();
        y = g.y();
        w = g.width();
        h = g.height() + movedY; d->setPreviewHeight(h);
        framePreview->setGeometry(x, y, w, h);
        QThread::msleep(sleepValue);

        g = frameLog->geometry();
        x = g.x();
        y = g.y() + movedY;
        w = g.width();
        h = g.height() - movedY; d->setLogHeight(h);
        frameLog->setGeometry(x, y, w, h);
        QThread::msleep(sleepValue);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key) {
    case Qt::Key_F3: addProject(); break;
    case Qt::Key_F4: removeProject(); break;
    case Qt::Key_F5: refreshProject(); break;
    case Qt::Key_F6: clearLog(); break;
    case Qt::Key_F7: zoomIn(); break;
    case Qt::Key_F8: zoomOut(); break;
    case Qt::Key_F9: full(); break;
		case Qt::Key_Control: m->pressCtrl(true); break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	int key = event->key();
	switch (key) {
		case Qt::Key_Control: m->pressCtrl(false); break;
	}
}

void MainWindow::connections()
{
    connect(widgetMenubar->btnAdd(), SIGNAL(clicked()), this, SLOT(addProject()));
    connect(widgetMenubar->btnRemove(), SIGNAL(clicked()), this, SLOT(removeProject()));
    connect(widgetMenubar->btnRefresh(), SIGNAL(clicked()), this, SLOT(refreshProject()));
    connect(widgetMenubar->btnClearLog(), SIGNAL(clicked()), this, SLOT(clearLog()));
    connect(widgetMenubar->btnZoomIn(), SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(widgetMenubar->btnZoomOut(), SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(widgetMenubar->btnFullScreen(), SIGNAL(clicked()), this, SLOT(full()));

    connect(widgetVAdjustbar, SIGNAL(adjust(QMouseEvent*)), this, SLOT(adjustVAbar(QMouseEvent*)));
    connect(widgetHAdjustbar, SIGNAL(adjust(QMouseEvent*)), this, SLOT(adjustHAbar(QMouseEvent*)));
}

void MainWindow::addProject()
{
    msg("Adding Project...");

    QString path = QFileDialog::getExistingDirectory(this, "Open Directory...", QDir::currentPath());

    if (path.isEmpty()) {
        msg("Canceled.");
        return;
    }
    m->setDir(path);
}
void MainWindow::removeProject()
{
    msg("Removing Project...");
    emit m->dirRemove();
}
void MainWindow::refreshProject()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    m->setDate(QString("updated at: %1").arg(currentTime));
    msg("Project Refreshed.");
    emit m->dirRefresh();
}
void MainWindow::clearLog()
{
    msg("Cleared Logs.");
    emit m->logClear();
}
void MainWindow::zoomIn()
{
    emit m->zoomIn();
}
void MainWindow::zoomOut()
{
    emit m->zoomOut();
}
void MainWindow::full()
{
    m->setFull(!m->full());

    if (m->full()) {
        tmp_explorerWidth = d->explorerWidth();
        tmp_logHeight = d->logHeight();
        tmp_borderFixedSize = d->borderFixedSize();

        d->setExplorerWidth(0);
        d->setLogHeight(0);
        d->setBorderFixedSize(0);
        framePreview->setGeometry(0, d->menubarHeight(), d->windowWidth(), d->windowHeight() + d->titleBarHeight());

        msg("Full Mode.");
    }
    else {
        d->setExplorerWidth(tmp_explorerWidth);
        d->setLogHeight(tmp_logHeight);
        d->setBorderFixedSize(tmp_borderFixedSize);
        framePreview->setGeometry(d->explorerWidth() + d->borderFixedSize(), d->menubarHeight(), d->previewWidth(), d->previewHeight());

        msg("Released Full Mode.");
    }
    resize();


}
void MainWindow::msg(QString message) { m->setMessage(message); }
