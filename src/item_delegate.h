#pragma once
#include <QStyledItemDelegate>

class ItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	ItemDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;

//protected:
//	bool eventFilter(QObject *object, QEvent *event);
//	bool editorEvent(QEvent *event, QAbstractItemModel *model,
//		const QStyleOptionViewItem &option, const QModelIndex &index);;

};