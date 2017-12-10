#pragma once

#include "qheader.h"
class Item;
class Explorer;
class Model;
class DBManager;
class BindingListView : public QListView
{
	Q_OBJECT

public:
	explicit BindingListView(QWidget *parent = Q_NULLPTR);
	~BindingListView();
	void updateView(int row);
	
	public slots:
	bool insert();
	bool remove();
	void refresh();
signals:
	void select(int rowNum);
	void alert(QString message);


protected:
	void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);	
	void	mouseReleaseEvent(QMouseEvent *e);

private:
	int selectedRow;

	bool selectionChagned = false;
	bool allowedSelection = false;	
	bool checkDirectory(int id, QString path);
		
	QList<Item*> values;// = { "A", "B", "C" };
	QStringList findFiles(QString path);
	
	QAbstractItemModel *data;
	QItemSelectionModel *selections;

	Model* m;
	DBManager* db;

	void msg(QString);
};
