#include "t3projecttreenode.h"

t3ProjectTreeNode::t3ProjectTreeNode(QString name_, t3ProjectTreeNode * parent_) :
        _parent(parent_),
        _name(name_)
{
}
