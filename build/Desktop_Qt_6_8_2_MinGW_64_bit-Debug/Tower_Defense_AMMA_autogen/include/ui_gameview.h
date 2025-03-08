/********************************************************************************
** Form generated from reading UI file 'gameview.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEVIEW_H
#define UI_GAMEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameView
{
public:
    QGroupBox *gameControlGroup;
    QPushButton *startWaveButton;
    QPushButton *pauseButton;
    QPushButton *menuButton;
    QGroupBox *towerSelectionGroup;
    QPushButton *basicTowerButton;
    QPushButton *slowTowerButton;
    QPushButton *aoeTowerButton;
    QPushButton *cancelPlacementButton;
    QGroupBox *towerActionGroup;
    QPushButton *upgradeTowerButton;
    QPushButton *sellTowerButton;
    QLabel *towerStatsLabel;

    void setupUi(QWidget *GameView)
    {
        if (GameView->objectName().isEmpty())
            GameView->setObjectName("GameView");
        GameView->resize(1000, 600);
        gameControlGroup = new QGroupBox(GameView);
        gameControlGroup->setObjectName("gameControlGroup");
        gameControlGroup->setGeometry(QRect(800, 10, 190, 120));
        startWaveButton = new QPushButton(gameControlGroup);
        startWaveButton->setObjectName("startWaveButton");
        startWaveButton->setGeometry(QRect(10, 30, 170, 30));
        pauseButton = new QPushButton(gameControlGroup);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setGeometry(QRect(10, 65, 80, 30));
        menuButton = new QPushButton(gameControlGroup);
        menuButton->setObjectName("menuButton");
        menuButton->setGeometry(QRect(100, 65, 80, 30));
        towerSelectionGroup = new QGroupBox(GameView);
        towerSelectionGroup->setObjectName("towerSelectionGroup");
        towerSelectionGroup->setGeometry(QRect(800, 140, 190, 320));
        basicTowerButton = new QPushButton(towerSelectionGroup);
        basicTowerButton->setObjectName("basicTowerButton");
        basicTowerButton->setGeometry(QRect(10, 30, 170, 80));
        slowTowerButton = new QPushButton(towerSelectionGroup);
        slowTowerButton->setObjectName("slowTowerButton");
        slowTowerButton->setGeometry(QRect(10, 120, 170, 80));
        aoeTowerButton = new QPushButton(towerSelectionGroup);
        aoeTowerButton->setObjectName("aoeTowerButton");
        aoeTowerButton->setGeometry(QRect(10, 210, 170, 80));
        cancelPlacementButton = new QPushButton(towerSelectionGroup);
        cancelPlacementButton->setObjectName("cancelPlacementButton");
        cancelPlacementButton->setGeometry(QRect(10, 270, 170, 40));
        towerActionGroup = new QGroupBox(GameView);
        towerActionGroup->setObjectName("towerActionGroup");
        towerActionGroup->setGeometry(QRect(800, 470, 190, 120));
        towerActionGroup->setVisible(false);
        upgradeTowerButton = new QPushButton(towerActionGroup);
        upgradeTowerButton->setObjectName("upgradeTowerButton");
        upgradeTowerButton->setGeometry(QRect(10, 30, 80, 40));
        sellTowerButton = new QPushButton(towerActionGroup);
        sellTowerButton->setObjectName("sellTowerButton");
        sellTowerButton->setGeometry(QRect(100, 30, 80, 40));
        towerStatsLabel = new QLabel(towerActionGroup);
        towerStatsLabel->setObjectName("towerStatsLabel");
        towerStatsLabel->setGeometry(QRect(10, 75, 170, 40));

        retranslateUi(GameView);

        QMetaObject::connectSlotsByName(GameView);
    } // setupUi

    void retranslateUi(QWidget *GameView)
    {
        GameView->setWindowTitle(QCoreApplication::translate("GameView", "Tower Defense Game", nullptr));
        gameControlGroup->setTitle(QCoreApplication::translate("GameView", "Game Controls", nullptr));
        startWaveButton->setText(QCoreApplication::translate("GameView", "Start Wave", nullptr));
        pauseButton->setText(QCoreApplication::translate("GameView", "Pause", nullptr));
        menuButton->setText(QCoreApplication::translate("GameView", "Menu", nullptr));
        towerSelectionGroup->setTitle(QCoreApplication::translate("GameView", "Towers", nullptr));
        basicTowerButton->setText(QCoreApplication::translate("GameView", "Basic Tower\n"
"$100", nullptr));
        slowTowerButton->setText(QCoreApplication::translate("GameView", "Slow Tower\n"
"$150", nullptr));
        aoeTowerButton->setText(QCoreApplication::translate("GameView", "AoE Tower\n"
"$200", nullptr));
        cancelPlacementButton->setText(QCoreApplication::translate("GameView", "Cancel", nullptr));
        towerActionGroup->setTitle(QCoreApplication::translate("GameView", "Selected Tower", nullptr));
        upgradeTowerButton->setText(QCoreApplication::translate("GameView", "Upgrade", nullptr));
        sellTowerButton->setText(QCoreApplication::translate("GameView", "Sell", nullptr));
        towerStatsLabel->setText(QCoreApplication::translate("GameView", "Level: 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameView: public Ui_GameView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEVIEW_H
