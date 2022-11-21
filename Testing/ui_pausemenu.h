/********************************************************************************
** Form generated from reading UI file 'pausemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAUSEMENU_H
#define UI_PAUSEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PauseMenu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *ContinueButton;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QPushButton *ExitButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *LanguageButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *PauseMenu)
    {
        if (PauseMenu->objectName().isEmpty())
            PauseMenu->setObjectName(QString::fromUtf8("PauseMenu"));
        PauseMenu->resize(1520, 860);
        QFont font;
        PauseMenu->setFont(font);
        PauseMenu->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(PauseMenu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(550, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ContinueButton = new QPushButton(centralwidget);
        ContinueButton->setObjectName(QString::fromUtf8("ContinueButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ContinueButton->sizePolicy().hasHeightForWidth());
        ContinueButton->setSizePolicy(sizePolicy);
        ContinueButton->setMinimumSize(QSize(500, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Rockwell Extra Bold")});
        font1.setPointSize(48);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        ContinueButton->setFont(font1);
        ContinueButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ContinueButton);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));
        sizePolicy.setHeightForWidth(ExitButton->sizePolicy().hasHeightForWidth());
        ExitButton->setSizePolicy(sizePolicy);
        ExitButton->setMinimumSize(QSize(500, 100));
        ExitButton->setFont(font1);

        verticalLayout->addWidget(ExitButton);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        LanguageButton = new QPushButton(centralwidget);
        LanguageButton->setObjectName(QString::fromUtf8("LanguageButton"));
        sizePolicy.setHeightForWidth(LanguageButton->sizePolicy().hasHeightForWidth());
        LanguageButton->setSizePolicy(sizePolicy);
        LanguageButton->setMinimumSize(QSize(50, 50));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        LanguageButton->setFont(font2);

        verticalLayout_2->addWidget(LanguageButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_2);

        PauseMenu->setCentralWidget(centralwidget);

        retranslateUi(PauseMenu);

        QMetaObject::connectSlotsByName(PauseMenu);
    } // setupUi

    void retranslateUi(QMainWindow *PauseMenu)
    {
        PauseMenu->setWindowTitle(QCoreApplication::translate("PauseMenu", "Menu", nullptr));
        ContinueButton->setText(QCoreApplication::translate("PauseMenu", "CONTINUE", nullptr));
        ExitButton->setText(QCoreApplication::translate("PauseMenu", "EXIT", nullptr));
        LanguageButton->setText(QCoreApplication::translate("PauseMenu", " EN ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PauseMenu: public Ui_PauseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAUSEMENU_H
