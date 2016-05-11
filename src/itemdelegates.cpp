#include "itemdelegates.h"

ItemDelegates::ItemDelegates(QObject *parent) : QStyledItemDelegate(parent)
{

}

ItemDelegates::~ItemDelegates()
{

}

void ItemDelegates::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyle *style;
    QStyleOptionViewItemV4 optionV4 = option;
    int roundCount = index.model()->data(index.model()->index(index.row(), 1)).toInt();

    QString itemText = index.model()->data(index.model()->index(index.row(), index.column())).toString();

    initStyleOption(&optionV4, index);

    optionV4.backgroundBrush = QBrush(getColor(roundCount));
    optionV4.text = itemText;

    // draw correct setup
    if(optionV4.widget)
        style = optionV4.widget->style();
    else
        style = QApplication::style();

    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter, optionV4.widget);
}

bool ItemDelegates::eventFilter(QObject *object, QEvent *event)
{
    QWidget *editor = qobject_cast<QWidget*>(object);
    if(!editor)
        return false;

    if(event->type() == QEvent::KeyPress)
    {
        // key pressed, transforms QEvent into QKeyEvent
        QKeyEvent* pKeyEvent=static_cast<QKeyEvent*>(event);
        if(pKeyEvent->matches(QKeySequence::Copy))
        {
            emit ctrlCopyKeyEvent();
            return true;
        }
        else if(pKeyEvent->matches(QKeySequence::Paste))
        {
            emit ctrlPasteKeyEvent();
            return true;
        }
        else if(pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Enter)
        {
            emit commitData(editor);
            emit closeEditor(editor, QAbstractItemDelegate::NoHint);
            emit enterKeyEvent();
            editor->parentWidget()->setFocus();
            return true;
        }
        else if(pKeyEvent->key() == Qt::Key_Escape)
        {
            emit closeEditor(editor, QAbstractItemDelegate::NoHint);
            editor->parentWidget()->setFocus();
            return true;
        }
    }

    return false;
}

QColor ItemDelegates::getColor(int rC) const
{
    QString rCS = QString::number(rC);
    QChar rCC = rCS.at(rCS.length() - 1);

    if(rCC == '1' || rCC == '6')
        return Qt::yellow;

    if(rCC == '2' || rCC == '7')
        return Qt::lightGray;

    if(rCC == '3' || rCC == '8')
        return Qt::cyan;

    if(rCC == '4' || rCC == '9')
        return Qt::magenta;

    if(rCC == '5' || rCC == '0')
        return Qt::green;

    return Qt::white;
}
