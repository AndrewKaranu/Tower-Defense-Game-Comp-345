/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QFrame *line;
    QLabel *label_3;
    QHBoxLayout *mapSizeLayout;
    QLabel *label_4;
    QSpinBox *xmap;
    QLabel *label_5;
    QSpinBox *ymap;
    QHBoxLayout *coinLayout;
    QLabel *label_6;
    QLineEdit *StartCoin;
    QPushButton *pushButton;
    QPushButton *settingsButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QMenu *menuMain_Menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 24pt; font-weight: bold; color: #ff6600;"));

        verticalLayout->addWidget(titleLabel);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setStyleSheet(QString::fromUtf8("font-size: 14pt; font-weight: bold;"));

        verticalLayout->addWidget(label_3);

        mapSizeLayout = new QHBoxLayout();
        mapSizeLayout->setObjectName("mapSizeLayout");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        mapSizeLayout->addWidget(label_4);

        xmap = new QSpinBox(centralwidget);
        xmap->setObjectName("xmap");

        mapSizeLayout->addWidget(xmap);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        mapSizeLayout->addWidget(label_5);

        ymap = new QSpinBox(centralwidget);
        ymap->setObjectName("ymap");

        mapSizeLayout->addWidget(ymap);


        verticalLayout->addLayout(mapSizeLayout);

        coinLayout = new QHBoxLayout();
        coinLayout->setObjectName("coinLayout");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        coinLayout->addWidget(label_6);

        StartCoin = new QLineEdit(centralwidget);
        StartCoin->setObjectName("StartCoin");

        coinLayout->addWidget(StartCoin);


        verticalLayout->addLayout(coinLayout);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");

        verticalLayout->addWidget(settingsButton);

        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName("helpButton");

        verticalLayout->addWidget(helpButton);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuMain_Menu = new QMenu(menubar);
        menuMain_Menu->setObjectName("menuMain_Menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMain_Menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AMMA Tower Defense", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "AMMA TOWER DEFENSE", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Game Settings", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Map Size :", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Starting Coins :", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuMain_Menu->setTitle(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
