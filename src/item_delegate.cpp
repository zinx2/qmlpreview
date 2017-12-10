#include <QtWidgets>

#include "item_delegate.h"
#include "item_model.h"
void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.highlight());

	Item* item = index.data().value<Item*>();
	QFontMetrics fontMetrics = painter->fontMetrics();
	painter->save();
	painter->setPen(Qt::white);

	QString childCount = " (" + QString::number(item->childCount()) + ")";
    QString path = ":/imgs/folder.png";
	int margin = option.rect.x() + 10;
	if (item->parent() > 0) {
        path = ":/imgs/file.png";
		margin += 20;
		childCount = "";
	}
	QPixmap img(path);
	
	painter->drawPixmap(margin, option.rect.y() + 10, 20, 20, img);  // this works

	margin += 30;
	int txtWidth = option.rect.width() - margin;

	QString elidedLastLine = fontMetrics.elidedText(item->title() + childCount, Qt::ElideRight, txtWidth);
	painter->drawText(QPoint(margin, option.rect.y() + 25), elidedLastLine);
	painter->restore();
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
    QSize size(option.rect.width(), 40);
    return size;
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QStyledItemDelegate::setEditorData(editor, index);
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QStyledItemDelegate::setModelData(editor, model, index);
}


//bool ItemDelegate::eventFilter(QObject *object, QEvent *event)
//{
//	return true;
//}
//bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
//	const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//
//	//qDebug() << "x : " << option.rect.x() << ", y: " << option.rect.y();
//	//if(event->type() == QEvent::MouseMove) 
//	//{
//	//}
//	//if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) 
//	//{
//	//}
//	//if (event->type() == QEvent::MouseButtonRelease) 
//	//{
//	//}
//	return true;
//}
