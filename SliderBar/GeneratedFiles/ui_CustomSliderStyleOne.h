/********************************************************************************
** Form generated from reading UI file 'CustomSliderStyleOne.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMSLIDERSTYLEONE_H
#define UI_CUSTOMSLIDERSTYLEONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "CustomSliderStyleOne.h"

QT_BEGIN_NAMESPACE

class Ui_CustomSliderStyleOne
{
public:
    QRoundedLabelStyleOne *hander_lab;

    void setupUi(QWidget *CustomSliderStyleOne)
    {
        if (CustomSliderStyleOne->objectName().isEmpty())
            CustomSliderStyleOne->setObjectName(QStringLiteral("CustomSliderStyleOne"));
        CustomSliderStyleOne->resize(304, 300);
        hander_lab = new QRoundedLabelStyleOne(CustomSliderStyleOne);
        hander_lab->setObjectName(QStringLiteral("hander_lab"));
        hander_lab->setGeometry(QRect(140, 120, 81, 71));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hander_lab->sizePolicy().hasHeightForWidth());
        hander_lab->setSizePolicy(sizePolicy);
        hander_lab->setStyleSheet(QStringLiteral(""));
        hander_lab->setAlignment(Qt::AlignCenter);

        retranslateUi(CustomSliderStyleOne);

        QMetaObject::connectSlotsByName(CustomSliderStyleOne);
    } // setupUi

    void retranslateUi(QWidget *CustomSliderStyleOne)
    {
        CustomSliderStyleOne->setWindowTitle(QApplication::translate("CustomSliderStyleOne", "CustomSliderStyleOne", Q_NULLPTR));
        hander_lab->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CustomSliderStyleOne: public Ui_CustomSliderStyleOne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMSLIDERSTYLEONE_H
