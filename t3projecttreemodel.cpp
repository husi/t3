#include "t3projecttreemodel.h"

t3ProjectTreeModel::t3ProjectTreeModel(QObject * parent_):
        QAbstractItemModel(parent_)
{
    _root = t3ProjectTreeNode::rebuildFromDB();
}

t3ProjectTreeModel::~t3ProjectTreeModel()
{
    delete _root;
}
QModelIndex t3ProjectTreeModel::index(int row_,int column_,const QModelIndex &parent_) const
{
    if(!hasIndex(row_,column_,parent_))
    {
        return QModelIndex();
    }

    t3ProjectTreeNode * parent;

    if(!parent_.isValid())
    {
        parent = _root;
    }
    else
    {
        parent = static_cast<t3ProjectTreeNode*>(parent_.internalPointer());
    }

    t3ProjectTreeNode * child = parent->getChild(row_);

    if(child)
    {
        return createIndex(row_,column_,child);
    }

    return QModelIndex();
}

int t3ProjectTreeModel::rowCount(const QModelIndex &parent_) const
{
    t3ProjectTreeNode * parent;
    if(!parent_.isValid())
    {
        parent = _root;
    }
    else
    {
        parent = static_cast<t3ProjectTreeNode *>(parent_.internalPointer());
    }

    return parent->getChildCount();
}


QModelIndex t3ProjectTreeModel::parent(const QModelIndex &index_) const
{
    if(!index_.isValid())
        return QModelIndex();

    t3ProjectTreeNode * node = static_cast<t3ProjectTreeNode *>(index_.internalPointer());
    t3ProjectTreeNode * parent = node->getParent();

    if(parent == _root)
        return QModelIndex();

    return createIndex(parent->getRow(),0,parent);
}

QVariant t3ProjectTreeModel::data(const QModelIndex &index_,int role_) const
{
    if(!index_.isValid())
    {
        return QVariant();
    }

    if(Qt::DisplayRole == role_)
    {
        t3ProjectTreeNode * node = static_cast<t3ProjectTreeNode *>(index_.internalPointer());
        switch(index_.column())
        {
        case 0:
            return node->getName();
            break;
        case 1:
            return node->getDescription();
            break;
        default: {}
        }
    }

    return QVariant();
}

Qt::ItemFlags t3ProjectTreeModel::flags(const QModelIndex &index_) const
{
    if(!index_.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant t3ProjectTreeModel::headerData(int section_, Qt::Orientation orientation_, int role_) const
{
    if (orientation_ == Qt::Horizontal && role_ == Qt::DisplayRole)
    {
        switch(section_)
        {
        case 0:
            return "Project";
        case 1:
            return "Description";
        }
    }

    return QVariant();
}
