#include "itemrowdelegate.h"

ItemRowDelegate::ItemRowDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

ItemRowDelegate::~ItemRowDelegate()
{

}

void ItemRowDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString itemText = index.model()->data(index.model()->index(index.row(), index.column())).toString();
    QString ms = index.model()->data(index.model()->index(index.row(), 0)).toString();
    int satz = index.model()->data(index.model()->index(index.row(), 1)).toInt();
    int spiel = index.model()->data(index.model()->index(index.row(), 2)).toInt();
    int intern = index.model()->data(index.model()->index(index.row(), 3)).toInt();
    int ext = index.model()->data(index.model()->index(index.row(), 4)).toInt();

    for(int i = 0; i < index.model()->rowCount(); i++)
    {
        QString msCheck = index.model()->data(index.model()->index(i, 0)).toString();
        int satzCheck = index.model()->data(index.model()->index(i, 1)).toInt();
        int spielCheck = index.model()->data(index.model()->index(i, 2)).toInt();
        int internCheck = index.model()->data(index.model()->index(index.row(), 3)).toInt();
        int extCheck = index.model()->data(index.model()->index(index.row(), 4)).toInt();
        QStyleOptionViewItem op(option);
        QStyle *style = op.widget->style();
        op.text = itemText;

        if(ms != msCheck && satz == satzCheck && spiel == spielCheck && intern == internCheck && ext == extCheck)
        {
            op.backgroundBrush = QBrush(Qt::red);
            style->drawControl(QStyle::CE_ItemViewItem, &op, painter, op.widget);
            break;
        }
        else
        {
            op.backgroundBrush = QBrush(Qt::white);
            style->drawControl(QStyle::CE_ItemViewItem, &op, painter, op.widget);
        }
    }
}
