#include "t3dataviewbase.h"

t3DataViewBase::t3DataViewBase(QObject *parent_) :
        QObject(parent_)
{
}

QString t3DataViewBase::category()
{
    return "Misc";
}

t3DataViewBase::~t3DataViewBase()
{
}
