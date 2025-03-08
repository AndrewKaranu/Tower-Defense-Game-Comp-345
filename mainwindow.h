#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "GameManager.h"
#include "gameview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked(); // This is the start game button
    void on_StartCoin_textChanged(const QString &arg1);
    void on_ymap_valueChanged(int arg1);
    void on_xmap_valueChanged(int arg1);
    
    // Add slots for game management
    void switchToGameView();
    void switchToMainMenu();

    // Add slots for new buttons
    void showSettings();
    void showHelp();
    void exitGame();

private:
    Ui::MainWindow *ui;
    GameManager* gameManager;
    QStackedWidget* stackedWidget;
    GameView* gameView;
};

#endif // MAINWINDOW_H