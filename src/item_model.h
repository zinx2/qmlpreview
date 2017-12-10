#pragma once
#include <QAbstractItemModel>
#include <QFileIconProvider>
#include <QIcon>
#include <QVector>

class Item : public QObject {
	Q_OBJECT
		Q_PROPERTY(QString str READ str WRITE setStr NOTIFY strChanged)
		Q_PROPERTY(bool visibled READ visibled WRITE visible NOTIFY visibleChanged)
public:
	Item(QString str) : m_str(str) {}
	Item(int id, int parent, QString str) : m_id(id), m_parent(parent), m_str(str) {}
	Item(int id, int parent, int childCount, QString title) :
		m_id(id), m_parent(parent), m_childCount(childCount), m_title(title) {}
	Item(int id, int parent, int childCount, QString title, QString path, int did=0) : 
		m_id(id), m_parent(parent), m_childCount(childCount), m_title(title), m_path(path), m_did(did) {}
	Item(int id, int parent, int childCount, QString title, QString path, bool visible) :
		m_id(id), m_parent(parent), m_childCount(childCount), m_title(title), m_path(path), m_visibled(visible), m_did(0) {}
	Item(int id, int parent, int childCount, QString title, QString path, bool extended, int did) :
		m_id(id), m_parent(parent), m_childCount(childCount), m_title(title), m_path(path), m_extended(extended), m_visibled(true), m_did(did) {}

	QString str() { return m_str; }
	QString str2() { return mm_str; }
	QString title() { return m_title; }
	QString path() { return m_path; }
	int parent() { return m_parent; }
	int id() { return m_id; }
	int did() { return m_did; }
	int childCount() { return m_childCount; }
	bool extended() { return m_extended; }
	bool visibled() { return m_visibled; }
	QVector<int> children() { return m_children; }

	public slots:
	void setStr(QString str) { m_str = str; emit strChanged(); }
	void setTitle(QString m) { m_title = m; }
	void setPath(QString m) { m_path = m;  }
	void setStr2(QString str) { mm_str = str;  }
	void setParent(int m) { m_parent = m; }
	void setID(int m) { m_id = m; }
	void setDID(int m) { m_did = m; }
	void extend(bool m) { m_extended = m; }
	void visible(bool m) { m_visibled = m; emit visibleChanged(); }
	void insertChild(int id) { m_children.push_back(id); }
	void setChildCount(int m) { m_childCount = m; }

signals:
	void strChanged();
	void visibleChanged();

private:
	QString m_str;
	QString mm_str;
	QString m_title;
	QString m_path;
	int m_parent = 0;
	int m_id = 0;
	int m_did = 0;
	int m_childCount = 0;
	bool m_extended = false;
	bool m_visibled = true;
	QVector<int> m_children;
};
Q_DECLARE_METATYPE(Item*)
class ItemModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	ItemModel(QList<Item*> values, QObject *parent = 0);
	~ItemModel();

	QModelIndex index(int row, int column, const QModelIndex &parent) const override;
	QModelIndex parent(const QModelIndex &child) const override;

	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;

private:
	QList<Item*> m_values;
};
