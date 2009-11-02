#ifndef T3PROJECTTREENODE_H
#define T3PROJECTTREENODE_H

#include <QList>
#include <QString>

class t3ProjectTreeNode
{
public:
    t3ProjectTreeNode(QString name_, t3ProjectTreeNode * parent_);

private:
    t3ProjectTreeNode * _parent;
    QList<t3ProjectTreeNode *> _children;
    QString _name;


};

#endif // T3PROJECTTREENODE_H
