#include "t3projecttreenode.h"
#include <QVariant>
#include <QDebug>


t3ProjectTreeNode::t3ProjectTreeNode(int id_, QString name_, QString description_, t3ProjectTreeNode * parent_) :
        _id(id_),
        _parent(parent_),
        _name(name_),
        _description(description_)
{
    if(_parent)
    {
        _parent->_children.append(this);
    }
    qDebug() << "Node Created: " << name_;
}

t3ProjectTreeNode::t3ProjectTreeNode() :
        _id(-1), //indicating a hidden root
        _parent(NULL)
{
}

t3ProjectTreeNode::~t3ProjectTreeNode()
{
    qDeleteAll(_children);
}

void t3ProjectTreeNode::populateChildrenFromQuerry(t3ProjectTreeNode * node_, QSqlQuery & query_)
{

    while(query_.next())
    {
        qDebug() << query_.value(0) << "|"
                << query_.value(1) << "|"
                << query_.value(2) << "|" ;
        t3ProjectTreeNode * node =new t3ProjectTreeNode(query_.value(0).toInt(),
                                                        query_.value(1).toString(),
                                                        query_.value(2).toString(),
                                                        node_);
        populateChildrenFromDB(node);
    }
}

void t3ProjectTreeNode::populateChildrenFromDB(t3ProjectTreeNode * node)
{
    QSqlQuery query;
    query.prepare("SELECT Id,Name,Description FROM Projects WHERE Deleted IS NULL AND Parent=?");
    query.addBindValue(node->_id);
    query.exec();
    populateChildrenFromQuerry(node,query);
}

t3ProjectTreeNode * t3ProjectTreeNode::rebuildFromDB()
{
    t3ProjectTreeNode * root = new t3ProjectTreeNode();
    QSqlQuery query("SELECT Id,Name,Description FROM Projects WHERE Deleted IS NULL AND Parent IS NULL;");
    populateChildrenFromQuerry(root,query);
    return root;
}

t3ProjectTreeNode * t3ProjectTreeNode::getChild(int index)
{
    if (0 <= index && index < _children.size())
    {
        return _children[index];
    }

    return NULL;
}

int t3ProjectTreeNode::getRow()
{
    if(_parent)
        return _parent->_children.indexOf(this);

    return 0;
}
