#pragma once
#include "qheader.h"
class Explorer : public QObject {
	Q_OBJECT
		Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
		Q_PROPERTY(int parent READ parent WRITE setParent NOTIFY parentChanged)
		Q_PROPERTY(bool extended READ extended WRITE extend NOTIFY extendedChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
		Q_PROPERTY(QList<QObject*> children READ children WRITE setChildren NOTIFY childrenChanged)
public:

	Explorer(int id, QString name, QString path) : m_id(id), m_name(name), m_path(path) { }
	Explorer(int id, QString name, QString path, bool extended) : m_id(id), m_name(name), m_path(path), m_extended(extended) { }
	Explorer(
		int id,
		int parent,
		QString name,
		QString path,
		QList<QObject*> children) : m_id(id), m_parent(parent), m_name(name), m_path(path), m_children(children) { 	}
	Explorer(
		int id,
		int parent,
		QString name,
		QString path,
		bool extended,
		QList<QObject*> children) : m_id(id), m_parent(parent), m_name(name), m_path(path), m_extended(extended), m_children(children) { 	}

	int id() const { return m_id; }
	int parent() const { return m_parent; }
	bool extended() const { return m_extended; }
	QString name() const { return m_name; }
	QString path() const { return m_path; }
	QList<QObject*> children() const { return m_children; }

	public slots:
	void setId(const int id) { m_id = id; }
	void setParent(const int parent) { m_parent = parent; }
	void setName(const QString &m) { m_name = m; emit nameChanged(); }
	void setPath(const QString &m) { m_path = m; emit pathChanged(); }
	void setChildren(const QList<QObject*> &m) { m_children = m; emit childrenChanged(); }
	void extend(bool m) { m_extended = m; emit extendedChanged(); };

signals:
	void idChanged();
	void parentChanged();
	void nameChanged();
	void pathChanged();
	void childrenChanged();
	void extendedChanged();


private:
	int m_id = -1;
	int m_parent = -1;
	bool m_extended = false;
	QString m_name;
	QString m_path;
	QList<QObject*> m_children;
};


class Model : public QObject {
	Q_OBJECT
		Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
		Q_PROPERTY(int selectedItem READ selectedItem WRITE selectItem NOTIFY itemSelected)
		Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
		Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
		Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
		Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
		Q_PROPERTY(bool full READ full WRITE setFull NOTIFY fullChanged)
		Q_PROPERTY(bool pressedCtrl READ pressedCtrl WRITE pressCtrl NOTIFY pressedCtrlChanged)
		Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
		Q_PROPERTY(int scaledItemWidth READ scaledItemWidth WRITE setScaledItemWidth NOTIFY scaledItemWidthChanged)
		Q_PROPERTY(int scaledItemHeight READ scaledItemHeight WRITE setScaledItemHeight NOTIFY scaledItemHeightChanged)
		Q_PROPERTY(int itemFixedWidth READ itemFixedWidth WRITE setItemFixedWidth NOTIFY itemFixedWidthChanged)
		Q_PROPERTY(int itemFixedHeight READ itemFixedHeight WRITE setItemFixedHeight NOTIFY itemFixedHeightChanged)
private:
	Model() { };
	static Model* m_instance;
public:
	static Model* instance() {
		if (m_instance == nullptr) m_instance = new Model();
		return m_instance;
	}

	QList<Explorer*> projects() { return m_projects; }
	QString message() const { return m_message; }
	int count() { return m_projects.size(); }
	int selectedItem() const { return m_selectedItem; }
	QString path() const { return m_path; }
	QString dir() const { return m_dir; }
	QString log() const { return m_log; }
	QString date() const { return m_date; }
	bool full() const { return m_full; }
	bool pressedCtrl() const { return m_pressedCtrl; }
	qreal scale() const { return m_scale; }
	int scaledItemWidth() const { return m_scaledItemWidth; }
	int scaledItemHeight() const { return m_scaledItemHeight; }
	int itemFixedWidth() const { return m_itemFixedWidth; }
	int itemFixedHeight() const { return m_itemFixedHeight; }

	public slots:
	void setProjects(QList<Explorer*> m) { m_projects = m; }
	void setMessage(QString m) { m_message = m; emit messageChanged(); }
	void selectItem(int m) { m_selectedItem = m; emit itemSelected(); }
	void setPath(QString m) { m_path = m; emit pathChanged(); }
	void setDir(QString m) { m_dir = m; emit dirChanged(); }
	void setLog(QString m) { m_log = m; emit logChanged(); }
	void setDate(QString m) { m_date = m; emit dateChanged(); }
	void setFull(bool m) { m_full = m; emit fullChanged(); }
	void pressCtrl(bool m) { m_pressedCtrl = m; emit pressedCtrlChanged(); }
	void setScale(qreal m) { m_scale = m; emit scaleChanged(); }
	void setScaledItemWidth(int m) { m_scaledItemWidth = m; emit scaledItemWidthChanged(); }
	void setScaledItemHeight(int m) { m_scaledItemHeight = m; emit scaledItemHeightChanged(); }
	void setItemFixedWidth(int m) { m_itemFixedWidth = m; emit itemFixedWidthChanged(); }
	void setItemFixedHeight(int m) { m_itemFixedHeight = m; emit itemFixedHeightChanged(); }

signals:
	void messageChanged();
	void itemSelected();
	void pathChanged();
	void dirChanged();
	void logChanged();
	void dateChanged();
	void dirRemove();
	void dirRefresh();
	void logClear();
	void zoomIn();
	void zoomOut();
  void fullChanged();
	void pressedCtrlChanged();
	void scaleChanged();
	void scaledItemWidthChanged();
	void scaledItemHeightChanged();
	void itemFixedWidthChanged();
	void itemFixedHeightChanged();

private:
	QList<Explorer*> m_projects;
	QString m_message;
	int m_selectedItem;
	QString m_path;
	QString m_dir;
	QString m_log;
	QString m_date;
	bool m_full = false;
	bool m_pressedCtrl = false;
	qreal m_scale = 1;
	int m_scaledItemWidth = 720;
	int m_scaledItemHeight = 1080;
	int m_itemFixedWidth = 720;
	int m_itemFixedHeight = 1280;
};