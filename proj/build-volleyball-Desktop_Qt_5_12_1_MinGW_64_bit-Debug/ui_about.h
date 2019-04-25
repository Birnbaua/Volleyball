/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *labelPicture;
    QPlainTextEdit *plainTextEditVersioninfo;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->setWindowModality(Qt::ApplicationModal);
        About->resize(582, 327);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/mikasa.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        About->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(About);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        labelPicture = new QLabel(About);
        labelPicture->setObjectName(QString::fromUtf8("labelPicture"));
        labelPicture->setMaximumSize(QSize(150, 150));
        labelPicture->setPixmap(QPixmap(QString::fromUtf8("resources/mikasa.jpg")));
        labelPicture->setScaledContents(true);

        gridLayout->addWidget(labelPicture, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        plainTextEditVersioninfo = new QPlainTextEdit(About);
        plainTextEditVersioninfo->setObjectName(QString::fromUtf8("plainTextEditVersioninfo"));
        plainTextEditVersioninfo->setEnabled(true);

        gridLayout_2->addWidget(plainTextEditVersioninfo, 0, 1, 1, 1);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QString());
        labelPicture->setText(QString());
        plainTextEditVersioninfo->setPlainText(QString());
        plainTextEditVersioninfo->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
