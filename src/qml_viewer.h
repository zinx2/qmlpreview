#pragma once
#include "qheader.h"

class Design;
class Model;
class QTime; 
class QmlViewer : public QQuickWidget
{
	Q_OBJECT
public:
	static QmlViewer* instance(QWidget *parent = 0);
	//explicit QmlViewer(QWidget *parent = 0);
	void create(QWidget *parent = 0);
	~QmlViewer();
	public slots:
	void resize();
	void zoomIn();
	void zoomOut();
	void initialize();
	void removeObj();
	//protected:
	//	void wheelEvent(QWheelEvent *event);
		//void resizeEvent(QResizeEvent *) override;
private:
	Design* d;
	Model* m;
	Debug dg;
	

	static QmlViewer* m_instance;
	explicit QmlViewer(QWidget *parent = 0);
};