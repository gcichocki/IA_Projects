/********************************************************************************
** Form generated from reading UI file 'WestWolrdGui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WESTWOLRDGUI_H
#define UI_WESTWOLRDGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WestWolrdGuiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WestWolrdGuiClass)
    {
        if (WestWolrdGuiClass->objectName().isEmpty())
            WestWolrdGuiClass->setObjectName(QStringLiteral("WestWolrdGuiClass"));
        WestWolrdGuiClass->resize(600, 400);
        menuBar = new QMenuBar(WestWolrdGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        WestWolrdGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WestWolrdGuiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WestWolrdGuiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(WestWolrdGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WestWolrdGuiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WestWolrdGuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WestWolrdGuiClass->setStatusBar(statusBar);

        retranslateUi(WestWolrdGuiClass);

        QMetaObject::connectSlotsByName(WestWolrdGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *WestWolrdGuiClass)
    {
        WestWolrdGuiClass->setWindowTitle(QApplication::translate("WestWolrdGuiClass", "WestWolrdGui", 0));
    } // retranslateUi

};

namespace Ui {
    class WestWolrdGuiClass: public Ui_WestWolrdGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WESTWOLRDGUI_H
