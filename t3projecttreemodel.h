#ifndef T3PROJECTTREEMODEL_H
#define T3PROJECTTREEMODEL_H

#include <QAbstractItemModel>
#include <t3projecttreenode.h>

namespace t3
{
    enum dataRole{
        IdRole = Qt::UserRole
    };
}

class t3ProjectTreeModel : public QAbstractItemModel
{

public:
    t3ProjectTreeModel(QObject * parent_=0);
    ~t3ProjectTreeModel();

    QModelIndex index(int row_,int column_,const QModelIndex &parent_) const;
    QModelIndex parent(const QModelIndex &index_)const;

    QVariant data(const QModelIndex &index_,int role_) const;
    Qt::ItemFlags flags(const QModelIndex &index_) const;
    QVariant headerData(int section_,Qt::Orientation orientation_,int role_) const;

    int columnCount(const QModelIndex & /*parent_*/) const {return 2;}
    int rowCount(const QModelIndex &parentS_) const;

private:
    t3ProjectTreeNode * _root;
};

#endif // T3PROJECTTREEMODEL_H
