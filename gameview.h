#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QMessageBox>
#include "GameManager.h"

namespace Ui {
class GameView;
}

// Struct to represent projectile animations
struct ProjectileAnimation {
    QPointF startPos;
    QPointF targetPos;
    double progress;
    int towerType;  // 0 = basic, 1 = slow, 2 = aoe
    bool isAoE;
};

class GameView : public QWidget
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();
    
    void setGameManager(GameManager* manager);

signals:
    // Signal for menu navigation
    void returnToMenu();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void updateGameView();
    void on_startWaveButton_clicked();
    void on_basicTowerButton_clicked();
    void on_slowTowerButton_clicked();
    void on_aoeTowerButton_clicked();
    void on_cancelPlacementButton_clicked();
    void on_upgradeTowerButton_clicked();
    void on_sellTowerButton_clicked();
    
    // Slots for pause and menu buttons
    void on_pauseButton_clicked();
    void on_menuButton_clicked();
    
    // Slot for updating projectiles
    void updateProjectiles();
    
    // Slot for adding a projectile
    void addProjectile(Tower* tower, Critter* target);

private:
    // Drawing methods
    void drawMap(QPainter& painter);
    void drawTowers(QPainter& painter);
    void drawCritters(QPainter& painter);
    void drawProjectiles(QPainter& painter);
    void drawUI(QPainter& painter);
    void drawTowerRange(QPainter& painter);
    void showPlacementPreview(QPainter& painter);
    
    // Tower selection and placement methods
    void selectTower(int row, int col);
    void deselectTower();
    bool canPlaceTowerAt(int row, int col);
    void updateSelectedTowerInfo();
    
    // Utility methods
    int cellWidth() const;
    int cellHeight() const;
    QPointF gridToScreen(float row, float col) const;
    
    // Members
    Ui::GameView *ui;
    GameManager* gameManager;
    bool placingTower;
    QString selectedTowerType;
    int selectedTowerRow;
    int selectedTowerCol;
    QPoint cursorPos;
    QVector<ProjectileAnimation> activeProjectiles;
    
    // Add these timer declarations
    QTimer* updateTimer;
    QTimer* animationTimer;
};

#endif // GAMEVIEW_H