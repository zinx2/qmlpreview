#include "item_model.h"
#include <QDebug>
ItemModel::ItemModel(QList<Item*> values, QObject *parent) :
	m_values(values),
	QAbstractItemModel(parent)
{

}

ItemModel::~ItemModel()
{
}

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
	if (0 <= row && row < m_values.length() && column == 0)
		return createIndex(row, column);
	return QModelIndex();
}

QModelIndex ItemModel::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

int ItemModel::rowCount(const QModelIndex &parent) const
{	
	return m_values.length();
}

int ItemModel::columnCount(const QModelIndex &parent) const
{	
	return 1;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	//if (role == Qt::DisplayRole)
	else
		return QVariant::fromValue(m_values[index.row()]);
}
bool ItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		m_values = value.value<QList<Item*>>();
		emit dataChanged(index, index);
		return true;
	}
	return false;	
}
bool ItemModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
	if (index.isValid()) {		
		m_values[index.row()]->setStr(roles[0].toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

QVariant ItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QAbstractItemModel::headerData(section, orientation, role);
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	return Qt::ItemIsSelectable | QAbstractItemModel::flags(index);
}