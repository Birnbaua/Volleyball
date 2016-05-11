/****************************************************************************
**
** Copyright (C) 2015 cfr
** Description: adds item delegates to models
** Contact:
** Version: 0.3
**
** Version 0.1  add background color change for items
** Version 0.2  add eventfilter for copy + paste
** Version 0.3  add eventfilter for return and esc key, signals for commit data
**              and close editor
**
****************************************************************************/

#ifndef ITEMDELEGATES_H
#define ITEMDELEGATES_H

#include <QApplication>
#include <QObject>
#include <QPainter>
#include <QColor>
#include <QStyle>
#include <QStyleOptionViewItemV4>
#include <QStyledItemDelegate>
#include <QKeyEvent>
#include <QTableView>

class ItemDelegates : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegates(QObject *parent = 0);
    ~ItemDelegates();

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    bool eventFilter(QObject *object, QEvent *event);

signals:
    void ctrlCopyKeyEvent();
    void ctrlPasteKeyEvent();
    void enterKeyEvent();

private:
    QColor getColor(int rC) const;
};

#endif // ITEMDELEGATES_H
