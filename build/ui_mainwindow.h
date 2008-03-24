/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Mon Mar 24 12:00:46 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "src/svggraph.h"

class Ui_MainWindow
{
public:
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    SvgGraph *graphImg;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(530, 372);
    MainWindow->setWindowIcon(QIcon(QString::fromUtf8("../pngicon.png")));
    actionOuvrir = new QAction(MainWindow);
    actionOuvrir->setObjectName(QString::fromUtf8("actionOuvrir"));
    actionQuitter = new QAction(MainWindow);
    actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    graphImg = new SvgGraph(centralwidget);
    graphImg->setObjectName(QString::fromUtf8("graphImg"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(graphImg->sizePolicy().hasHeightForWidth());
    graphImg->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(graphImg);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 530, 22));
    menuFichier = new QMenu(menubar);
    menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFichier->menuAction());
    menuFichier->addAction(actionOuvrir);
    menuFichier->addAction(actionQuitter);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Mighty Graph", 0, QApplication::UnicodeUTF8));
    actionOuvrir->setText(QApplication::translate("MainWindow", "Ouvrir", 0, QApplication::UnicodeUTF8));
    actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
    menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
