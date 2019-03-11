#include "binding_listview.h"
#include "item_delegate.h"
#include "item_model.h"
#include "model.h"
#include "design.h"
#include "db_manager.h"
#include <QDebug>
BindingListView::BindingListView(QWidget *parent) :
	m(Model::instance()),
	db(new DBManager())
{
	ItemDelegate* d = new ItemDelegate;
	this->setItemDelegate(d);
	this->setStyleSheet("border: 0px; background-color:" + Design::instance()->c().explorer);
	this->setAlternatingRowColors(false);

	refresh();

	connect(m, SIGNAL(dirChanged()), this, SLOT(insert()));
	connect(m, SIGNAL(dirRemove()), this, SLOT(remove()));
	connect(m, SIGNAL(dirRefresh()), this, SLOT(refresh()));
}
BindingListView::~BindingListView()
{
	for (Item* item : values)
		delete item;

	delete selections;
	delete data;
	delete m;
	delete db;
}

/* THIS FUNCTION WORKS THE OPPOSITE OF THE CURRENT STATE. FOR EXAMPLE,
	 IF PARENT IS BEING EXTENDED, WOULD BE CLOSED. THEN CHILD ITEMS WOULD BE HIDED.
	 IF PARENT IS BEING CLOSED, WOULD BE EXTENDED. THEN CHILD ITEMS WOULD BE SHOWED. */
void BindingListView::updateView(int row)
{
	if (values.size() < 1 || row < 0) return;
	bool doUpdate = false;

	/* IF THE NODE IS PARENT NODE,*/
	if (values[row]->parent() == 0) {

		/* SHOW THE CHILDREN. */
		Item* parent = values[row];
		if (!parent->extended())
			doUpdate = true;
		else
			doUpdate = selectedRow == row ? true : false;

		/* 'selectedRow' HAVE TO BE UPDATED ANYTIME.	*/
		selectedRow = row;

		if (doUpdate) {
			parent->extend(!parent->extended());
			db->modifyExtended(parent->did(), parent->extended());
			//qDebug() << parent->extended();

			bool visible = false;
			if (parent->extended()) visible = true;
			for (int offset = 1; offset <= parent->childCount(); offset++) {
				int rid = row + offset;
				Item* child = values[rid];
				child->visible(visible);
				this->setRowHidden(rid, !visible);
			}

			/* 'selectionChanged' FUNCTION WOULD BE CALLED BY SYSTEM WHEN INDEX IS CHANGED,
			BUT IT COULD BE CALLED BY USER. IN THIS CASE THE FUNCTION HAVE TO BE CONTROL
			BY ANY FLAG. 'allowedSelection' IS BEING USED ON THE FOLLOWING CODES. */
			if (values.size() < 1) return;
			allowedSelection = true;
			this->setCurrentIndex(data->index(row, 0));
			allowedSelection = false;

			update();
		}
	}

	/* THE FOLLOWING CODE HAVE TO BE REMOVED SOMETIME. */
#pragma region TESTING CODE

//QAbstractItemModel *data = new Model(values, list);	
/*QModelIndex mIdx = this->currentIndex();
int row = mIdx.row();*/

/*values[idx.row()]->setStr("XXX");
values[2]->visible(true);
list->setRowHidden(2, false);*/

/* If this code isn't written, UI don't be updated immediately.  */


///* Get model and cast the appropriate type */
//Model* md = qobject_cast<Model*>(list->model());

///* Refresh all items.  */
//md->setData(idx, QVariant::fromValue(values));

///* Get item at index. */
//QMap<int, QVariant> m = list->model()->itemData(idx);
//qDebug() << m[0].toString();

///* Set item at index */
//md->setItemData(idx, m);


//QMap<int, QVariant> m = list->model()->itemData(idx);
//m[0] = "FFFF ITEM ";
//Model* md = qobject_cast<Model*>(list->model());		
//list->setModel(data);
#pragma endregion

}

/* 'selectionChanged' FUNCTION WOULD BE CALLED BY SYSTEM WHEN INDEX IS CHANGED,
BUT IT COULD BE CALLED BY USER. IN THIS CASE THE FUNCTION HAVE TO BE CONTROL
BY ANY FLAG. 'allowedSelection' IS BEING USED ON THE FOLLOWING CODES. */
void BindingListView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	QModelIndexList mList = selected.indexes();
	if (mList.length() > 0)
	{
		int currentRow = mList[0].row();
		Item* item = values[currentRow];
		if (item->parent() > 0) {
			m->selectItem(item->id());
			m->setPath(item->path());	/* EMIT 'pathChanged' SIGNAL */
		}
		selectedRow = currentRow;
	}

	/* IF 'allowedSelection' FLAG ISN'T ENABLED,
		 DON'T HAVE TO BE CALLED 'selectionChanged' FUNCTION. */
	if (allowedSelection)
		updateView(selectedRow);
}
void BindingListView::mouseReleaseEvent(QMouseEvent *e)
{
	if (!allowedSelection)
		updateView(selectedRow);
}

void BindingListView::refresh()
{
	if (values.size() > 0) values.clear();

	db->selectDB();
	QList<Explorer*> parents = Model::instance()->projects();

	QStringList strFilters;
	strFilters += "*.qml";

	int itemID = 1;
	for (Explorer* parent : parents) {
		int parentID = 0;
		QString prefixPath = parent->path();

		/* CHECK DIRECOTORY. */
		if (!checkDirectory(parent->id(), prefixPath)) continue;

		/* FIND QML FILES. */
        QStringList children = findFiles(prefixPath);
        children.sort();

		/* CREATE PARENT ITEM. */
		values.append(new Item(itemID, parentID,
			children.size(), parent->name(),
			prefixPath, parent->extended(), parent->id()));
		parentID = itemID;
		itemID++;

		/* ADD FILES. */
		for (QString name : children) {
			values.append(new Item(itemID, parentID,
				0, name,
				prefixPath + "/" + name, parent->extended()));
			itemID++;
		}
	}

	/* UPDATE MODELS. */
	data = new ItemModel(values, this);
	selections = new QItemSelectionModel(data);
	this->setModel(data);
	this->setSelectionModel(selections);

	/* WHEN CALLED FIRSTLY, ALL ITEMS HAVE TO BE FOLDED. */
	for (int i = 0; i < values.length(); i++) {
		if (values[i]->parent() > 0)
			this->setRowHidden(i, !values[i]->visibled());
	}
	update();

	if (!m->path().isEmpty())
		emit m->pathChanged();
}

bool BindingListView::insert()
{
	QString path = m->dir();

	/* UPDATE DATABASE. */
	QStringList temp = path.split("/");
	QString name = temp[temp.length() - 1];
	if (!db->insertDB(name, path)) {
		msg("Can't insert the data to DB.");
		return false;
	}

	int offset = values.size();
	int parentID = 0;
	int itemID = offset > 0 ? values[values.size() - 1]->id() + 1 : 1;

	Model* m = Model::instance();
	Explorer* parent = (m->projects())[m->count() - 1];
	QString prefixPath = parent->path();

	/* CHECK DIRECOTORY. */
	if (!checkDirectory(parent->id(), prefixPath))
		return false;

	/* FIND QML FILES. */
    QStringList children; //= findFiles(prefixPath);

	/* CREATE PARENT ITEM. */
	Item* parentItem = new Item(itemID, parentID,
		children.size(), parent->name(),
		prefixPath, parent->extended(), parent->id());
	values.append(parentItem);
	parentID = itemID;
	itemID++;

	/* ADD FILES. */
	for (QString name : children) {
		values.append(new Item(itemID, parentID,
			0, name,
			prefixPath + "/" + name, parent->extended()));
		itemID++;
	}
	refresh();

	msg("Inserted Successfully.");
	return true;
}

bool BindingListView::remove()
{
	int rowID = this->currentIndex().row();

	if (rowID > -1)
	{
		/* IF HAVE NO SELECTED DIRECOTY, DON'T REMOVE. */
		int parentID = values[rowID]->parent();
		if (parentID > 0) {
			msg("Only directory can be removed.");
			return false;
		}

		int did = values[rowID]->did();
		if (db->removeDB(did)) refresh();

		msg("Removed Successfully.");
		return true;
	}

	msg("Please Select Directory.");
	return false;
}

/* CHECK THE VALIDALITY OF SELECTED DIRECTORY. */
bool BindingListView::checkDirectory(int id, QString path)
{
	QFileInfo check(path);
	if (!check.exists()) {
		db->removeDB(id);
		msg("Can't the selected directory.");
		return false;
	}
	return true;
}

QStringList BindingListView::findFiles(QString path)
{
	QDirIterator iterDir(path, { "*.qml" });
	QStringList children;
	while (iterDir.hasNext())
	{
		iterDir.next();
		children.push_back(iterDir.fileName());
    }
	return children;
}


void BindingListView::msg(QString message) {
	m->setMessage(message);
}         
