#ifndef ITEMROWDELEGATE_H
#define ITEMROWDELEGATE_H

#include <QApplication>
#include <QObject>
#include <itemdelegates.h>

class ItemRowDelegate : public ItemDelegates
{
    Q_OBJECT
public:
    explicit ItemRowDelegate(QObject *parent = 0);
    ~ItemRowDelegate();

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    QColor getColor(int rC) const;
};

#endif // ITEMROWDELEGATE_H
