#ifndef T3PROJECTTREENODE_H
#define T3PROJECTTREENODE_H

#include <QList>
#include <QString>
#include <QSqlQuery>

/**
 * t3ProjectTreeNode represent the tree of projects. Prefered population is through
 * the rebuildFromDB which is reading the data from a db. If initialized from db then
 * it will persist the data to the same db.
 */
class t3ProjectTreeNode
{
public:

    t3ProjectTreeNode(int id_, QString name_, QString description_, t3ProjectTreeNode * parent_);
    virtual ~t3ProjectTreeNode();
    QString getName() { return _name;}
    QString getDescription() { return _description;}
    int getId() { return _id; }
    t3ProjectTreeNode * getChild(int index);
    int getChildCount() {return _children.size();}
    t3ProjectTreeNode * getParent() {return _parent;}
    int getRow();

private:
    t3ProjectTreeNode();
    static void populateChildrenFromQuerry(t3ProjectTreeNode * node_, QSqlQuery &query_);
    static void populateChildrenFromDB(t3ProjectTreeNode* node);

private:
    int _id;
    t3ProjectTreeNode * _parent;
    QList<t3ProjectTreeNode *> _children;
    QString _name;
    QString _description;

    bool _persistToDb;

public:
    static t3ProjectTreeNode * rebuildFromDB();

};

#endif // T3PROJECTTREENODE_H
