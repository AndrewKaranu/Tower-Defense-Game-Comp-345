#include "gameview.h"
#include "ui_gameview.h"
#include "tower.h"
#include "base_tower.h"
#include "slow_tower.h"
#include "aoe_tower.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <cmath>

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameView),
    gameManager(nullptr),
    placingTower(false),
    selectedTowerType(""),
    selectedTowerRow(-1),
    selectedTowerCol(-1)
{
    ui->setupUi(this);
    
    // Initially hide the tower action panel
    ui->towerActionGroup->setVisible(false);
    
    // Set up update timer
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &GameView::updateGameView);
    updateTimer->start(16); // Update every 100ms
    
    // Set up animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &GameView::updateProjectiles);
    animationTimer->start(16); // ~60fps
    
    // Connect tower buttons
    connect(ui->basicTowerButton, &QPushButton::clicked, this, &GameView::on_basicTowerButton_clicked);
    connect(ui->slowTowerButton, &QPushButton::clicked, this, &GameView::on_slowTowerButton_clicked);
    connect(ui->aoeTowerButton, &QPushButton::clicked, this, &GameView::on_aoeTowerButton_clicked);
    
    // Connect tower action buttons
    connect(ui->cancelPlacementButton, &QPushButton::clicked, this, &GameView::on_cancelPlacementButton_clicked);
    connect(ui->upgradeTowerButton, &QPushButton::clicked, this, &GameView::on_upgradeTowerButton_clicked);
    connect(ui->sellTowerButton, &QPushButton::clicked, this, &GameView::on_sellTowerButton_clicked);
    
    // Set background color
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(40, 40, 40));
    setPalette(pal);
    
    // Enable mouse tracking
    setMouseTracking(true);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::setGameManager(GameManager* manager)
{
    gameManager = manager;
    // Connect signals from GameManager
    if (gameManager) {
        connect(gameManager, &GameManager::mapUpdated, this, [this]() { update(); });
        connect(gameManager, &GameManager::coinsChanged, this, [this](int coins) { 
            update(); 
            
            // Update button enabled states
            ui->basicTowerButton->setEnabled(coins >= 100);
            ui->slowTowerButton->setEnabled(coins >= 150);
            ui->aoeTowerButton->setEnabled(coins >= 200);
        });
        
        // Connect the tower attack signal to create projectile animations
        connect(gameManager, &GameManager::towerAttacked, this, &GameView::addProjectile);
    }
}

void GameView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    // Draw game components
    if (gameManager && gameManager->getMap()) {
        drawMap(painter);
        drawTowers(painter);
        drawCritters(painter);
        drawProjectiles(painter);
        
        // Draw tower range if placing or tower is selected
        if (placingTower || (selectedTowerRow >= 0 && selectedTowerCol >= 0)) {
            drawTowerRange(painter);
        }
        
        // Show tower placement preview if in placement mode
        if (placingTower) {
            showPlacementPreview(painter);
        }
        
        drawUI(painter);
        
        // Draw pause overlay if game is paused
        static bool isPaused = false;
        if (ui->pauseButton->text() == "Resume") {
            isPaused = true;
        } else {
            isPaused = false;
        }
        
        if (isPaused) {
            // Semi-transparent overlay
            painter.fillRect(rect(), QColor(0, 0, 0, 150));
            
            // Draw "PAUSED" text
            QFont pauseFont = painter.font();
            pauseFont.setPointSize(40);
            pauseFont.setBold(true);
            painter.setFont(pauseFont);
            painter.setPen(Qt::white);
            painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
            
            // Instructions
            QFont instrFont = pauseFont;
            instrFont.setPointSize(16);
            painter.setFont(instrFont);
            painter.drawText(QRect(0, height()/2 + 40, width(), 40), 
                             Qt::AlignCenter, "Press Resume to continue");
        }
    } else {
        // Display a message if no game is running
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, "No active game");
    }
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    // Convert click position to grid coordinates
    QPoint pos = event->position().toPoint();
    int col = pos.x() / cellWidth();
    int row = pos.y() / cellHeight();
    
    // Check if the click is within the map bounds
    gameMap* map = gameManager->getMap();
    if (row < 0 || row >= map->getRows() || col < 0 || col >= map->getCols()) {
        return;
    }
    
    // Handle tower placement if in placement mode
    if (placingTower && event->button() == Qt::LeftButton) {
        if (canPlaceTowerAt(row, col)) {
            // Convert QString to std::string for the GameManager API
            std::string towerTypeStr = selectedTowerType.toStdString();
            bool success = gameManager->placeTower(row, col, towerTypeStr);
            
            if (success) {
                qDebug() << "Tower placed at:" << row << col;
                // Exit placement mode
                placingTower = false;
                selectedTowerType = "";
                setCursor(Qt::ArrowCursor);
            } else {
                qDebug() << "Failed to place tower";
            }
        } else {
            qDebug() << "Cannot place tower at this location";
        }
    }
    // Select/deselect tower
    else if (event->button() == Qt::LeftButton) {
        Tower* tower = map->getTowerAt(row, col);
        if (tower) {
            selectTower(row, col);
        } else {
            deselectTower();
        }
    }
    
    // Cancel placement or selection on right click
    if (event->button() == Qt::RightButton) {
        if (placingTower) {
            placingTower = false;
            selectedTowerType = "";
            setCursor(Qt::ArrowCursor);
        } else {
            deselectTower();
        }
    }
    
    update();
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    cursorPos = event->position().toPoint();
    if (placingTower) {
        update(); // Redraw to update the tower preview position
    }
}

void GameView::updateGameView()
{
    // This will be called by the timer to update the view
    update();
}

void GameView::drawMap(QPainter& painter)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    gameMap* map = gameManager->getMap();
    int rows = map->getRows();
    int cols = map->getCols();
    
    int cellW = cellWidth();
    int cellH = cellHeight();
    
    // Draw grid
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            QRect cellRect(col * cellW, row * cellH, cellW, cellH);
            
            // Check if this is entry or exit point
            if (row == map->getEntryX() && col == map->getEntryY()) {
                // Entry point - bright green
                painter.fillRect(cellRect, QColor(50, 220, 50));
                painter.setPen(QPen(Qt::black, 2));
                painter.drawRect(cellRect);
                painter.drawText(cellRect, Qt::AlignCenter, "E");
            } 
            else if (row == map->getExitX() && col == map->getExitY()) {
                // Exit point - bright red
                painter.fillRect(cellRect, QColor(220, 50, 50));
                painter.setPen(QPen(Qt::black, 2));
                painter.drawRect(cellRect);
                painter.drawText(cellRect, Qt::AlignCenter, "X");
            }
            else {
                // Normal cells
                // Color the cell based on its type
                if (map->canCritterMove(row, col)) {
                    // Path cells - draw in tan
                    painter.fillRect(cellRect, QColor(200, 180, 100));
                } else {
                    // Scenery cells - draw in green
                    painter.fillRect(cellRect, QColor(100, 180, 100));
                }
                
                // Draw grid lines
                painter.setPen(Qt::black);
                painter.drawRect(cellRect);
            }
        }
    }
}

void GameView::drawTowers(QPainter& painter)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    gameMap* map = gameManager->getMap();
    int cellW = cellWidth();
    int cellH = cellHeight();
    
    // Get all towers on the map
    std::vector<Tower*> towers = map->getAllTowers();
    for (Tower* tower : towers) {
        int row = static_cast<int>(tower->getX());
        int col = static_cast<int>(tower->getY());
        
        QRect cellRect(col * cellW, row * cellH, cellW, cellH);
        
        // Highlight selected tower
        if (row == selectedTowerRow && col == selectedTowerCol) {
            painter.setPen(QPen(Qt::yellow, 3));
            painter.drawRect(cellRect);
        }
        
        // Draw different towers with different colors and shapes
        if (dynamic_cast<BasicTower*>(tower)) {
            // Basic tower (blue)
            painter.setBrush(QColor(100, 100, 200));
            painter.setPen(Qt::black);
            QRect towerRect = cellRect.adjusted(cellW/4, cellH/4, -cellW/4, -cellH/4);
            painter.drawRect(towerRect);
            
            // Draw cannon
            int centerX = col * cellW + cellW / 2;
            int centerY = row * cellH + cellH / 2;
            painter.setPen(QPen(Qt::black, 3));
            painter.drawLine(centerX, centerY, centerX, centerY - cellH/3);
            
            // Show level as number
            painter.setPen(Qt::white);
            painter.drawText(cellRect, Qt::AlignCenter, QString::number(tower->getLevel()));
        } else if (dynamic_cast<SlowTower*>(tower)) {
            // Slow tower (cyan) - ice crystal shape
            painter.setBrush(QColor(100, 220, 255));
            painter.setPen(Qt::black);
            
            // Create a snowflake/ice crystal shape
            int centerX = col * cellW + cellW / 2;
            int centerY = row * cellH + cellH / 2;
            int radius = qMin(cellW, cellH) / 3;
            
            QPointF points[8];
            for (int i = 0; i < 8; i++) {
                double angle = i * M_PI / 4;
                int r = (i % 2 == 0) ? radius : radius / 2;
                points[i] = QPointF(centerX + r * cos(angle), centerY + r * sin(angle));
            }
            
            painter.drawPolygon(points, 8);
            
            // Show level as number
            painter.setPen(Qt::white);
            painter.drawText(cellRect, Qt::AlignCenter, QString::number(tower->getLevel()));
        } else if (dynamic_cast<AoETower*>(tower)) {
            // AoE tower (orange) - circular/explosion shape
            painter.setBrush(QColor(255, 140, 0));
            painter.setPen(Qt::black);
            
            int centerX = col * cellW + cellW / 2;
            int centerY = row * cellH + cellH / 2;
            int radius = qMin(cellW, cellH) / 3;
            
            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
            
            // Add some "explosion" rays
            painter.setPen(QPen(QColor(255, 80, 0), 2));
            for (int i = 0; i < 8; i++) {
                double angle = i * M_PI / 4;
                int innerR = radius;
                int outerR = radius + radius / 2;
                QPoint start(centerX + innerR * cos(angle), centerY + innerR * sin(angle));
                QPoint end(centerX + outerR * cos(angle), centerY + outerR * sin(angle));
                painter.drawLine(start, end);
            }
            
            // Show level as number
            painter.setPen(Qt::white);
            painter.drawText(cellRect, Qt::AlignCenter, QString::number(tower->getLevel()));
        }
    }
}

void GameView::drawTowerRange(QPainter& painter)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    float range = 0;
    int row = 0, col = 0;
    
    // Get the range depending on the context
    if (placingTower) {
        // For tower placement preview, use the range of the selected tower type
        col = cursorPos.x() / cellWidth();
        row = cursorPos.y() / cellHeight();
        
        if (selectedTowerType == "Basic") range = 3.0f;
        else if (selectedTowerType == "Slow") range = 2.8f;
        else if (selectedTowerType == "AoE") range = 2.5f;
    } else if (selectedTowerRow >= 0 && selectedTowerCol >= 0) {
        // For selected tower, get range from the tower object
        Tower* tower = gameManager->getMap()->getTowerAt(selectedTowerRow, selectedTowerCol);
        if (tower) {
            range = tower->getRange();
            row = selectedTowerRow;
            col = selectedTowerCol;
        }
    }
    
    // Draw range indicator if we have a valid range
    if (range > 0) {
        int cellW = cellWidth();
        int cellH = cellHeight();
        
        int centerX = col * cellW + cellW / 2;
        int centerY = row * cellH + cellH / 2;
        
        // Convert from grid units to pixels (approximately)
        int pixelRange = static_cast<int>(range * cellW);
        
        // Draw a semi-transparent circle
        painter.setPen(QPen(QColor(255, 255, 255, 100), 2));
        painter.setBrush(QColor(255, 255, 255, 40));
        painter.drawEllipse(QPoint(centerX, centerY), pixelRange, pixelRange);
    }
}

void GameView::showPlacementPreview(QPainter& painter)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    int col = cursorPos.x() / cellWidth();
    int row = cursorPos.y() / cellHeight();
    
    gameMap* map = gameManager->getMap();
    
    // Only show preview if within map bounds
    if (row >= 0 && row < map->getRows() && col >= 0 && col < map->getCols()) {
        int cellW = cellWidth();
        int cellH = cellHeight();
        QRect cellRect(col * cellW, row * cellH, cellW, cellH);
        
        // Show if tower can be placed
        bool canPlace = canPlaceTowerAt(row, col);
        
        // Draw a preview indicator
        QColor previewColor = canPlace ? QColor(0, 255, 0, 100) : QColor(255, 0, 0, 100);
        painter.setBrush(previewColor);
        painter.setPen(QPen(canPlace ? Qt::green : Qt::red, 2));
        painter.drawRect(cellRect);
        
        // Draw preview of the selected tower
        if (canPlace) {
            int centerX = col * cellW + cellW / 2;
            int centerY = row * cellH + cellH / 2;
            
            if (selectedTowerType == "Basic") {
                painter.setBrush(QColor(100, 100, 200, 150));
                QRect towerRect = cellRect.adjusted(cellW/4, cellH/4, -cellW/4, -cellH/4);
                painter.drawRect(towerRect);
                
                // Draw cannon
                painter.setPen(QPen(Qt::black, 3));
                painter.drawLine(centerX, centerY, centerX, centerY - cellH/3);
            } else if (selectedTowerType == "Slow") {
                painter.setBrush(QColor(100, 220, 255, 150));
                
                // Snowflake shape
                int radius = qMin(cellW, cellH) / 3;
                QPointF points[8];
                for (int i = 0; i < 8; i++) {
                    double angle = i * M_PI / 4;
                    int r = (i % 2 == 0) ? radius : radius / 2;
                    points[i] = QPointF(centerX + r * cos(angle), centerY + r * sin(angle));
                }
                
                painter.drawPolygon(points, 8);
            } else if (selectedTowerType == "AoE") {
                painter.setBrush(QColor(255, 140, 0, 150));
                
                int radius = qMin(cellW, cellH) / 3;
                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
                
                // Add rays
                painter.setPen(QPen(QColor(255, 80, 0, 150), 2));
                for (int i = 0; i < 8; i++) {
                    double angle = i * M_PI / 4;
                    int innerR = radius;
                    int outerR = radius + radius / 2;
                    QPoint start(centerX + innerR * cos(angle), centerY + innerR * sin(angle));
                    QPoint end(centerX + outerR * cos(angle), centerY + outerR * sin(angle));
                    painter.drawLine(start, end);
                }
            }
        }
    }
}

void GameView::drawProjectiles(QPainter& painter)
{
    int cellW = cellWidth();
    int cellH = cellHeight();
    
    for (const ProjectileAnimation& proj : activeProjectiles) {
        // Calculate current position based on progress
        QPointF currentPos = proj.startPos + (proj.progress * (proj.targetPos - proj.startPos));
        
        // Draw different projectiles based on tower type
        if (proj.towerType == 0) {  // Basic Tower
            // Draw a small bullet/projectile
            painter.setBrush(Qt::white);
            painter.setPen(Qt::black);
            painter.drawEllipse(currentPos, 3, 3);
        } else if (proj.towerType == 1) {  // Slow Tower
            // Draw an ice/snow projectile
            painter.setBrush(QColor(150, 220, 255));
            painter.setPen(QColor(100, 200, 255));
            painter.drawEllipse(currentPos, 4, 4);
            
            // Add some snowflake-like details
            painter.setPen(QPen(QColor(200, 240, 255), 1));
            for (int i = 0; i < 4; i++) {
                double angle = i * M_PI / 2;
                QPointF start = currentPos + QPointF(3 * cos(angle), 3 * sin(angle));
                QPointF end = currentPos + QPointF(6 * cos(angle), 6 * sin(angle));
                painter.drawLine(start, end);
            }
        } else if (proj.towerType == 2) {  // AoE Tower
            // Draw a fiery projectile
            painter.setBrush(QColor(255, 140, 0));
            painter.setPen(Qt::transparent);
            painter.drawEllipse(currentPos, 5, 5);
            
            // Add some fire trail effect
            for (int i = 0; i < 3; i++) {
                QPointF offset = proj.startPos - proj.targetPos;
                offset = offset * (0.15 * i);
                QPointF trailPos = currentPos + offset;
                int alpha = 150 - (i * 40);
                painter.setBrush(QColor(255, 80, 0, alpha));
                painter.drawEllipse(trailPos, 4 - i, 4 - i);
            }
            
            // If it's an AoE attack that reached its target, draw the explosion
            if (proj.isAoE && proj.progress >= 0.95) {
                QRadialGradient gradient(proj.targetPos, 20);
                gradient.setColorAt(0, QColor(255, 200, 50, 150));
                gradient.setColorAt(0.5, QColor(255, 100, 0, 100));
                gradient.setColorAt(1, QColor(200, 0, 0, 50));
                
                painter.setBrush(gradient);
                painter.setPen(Qt::transparent);
                painter.drawEllipse(proj.targetPos, 20, 20);
            }
        }
    }
}

void GameView::drawCritters(QPainter& painter)
{
    if (!gameManager || !gameManager->getMap()) return;
    
    gameMap* map = gameManager->getMap();
    int cellW = cellWidth();
    int cellH = cellHeight();
    
    // Get active critters from the game manager
    std::vector<Critter*> critters = gameManager->getActiveCritters();
    
    for (Critter* critter : critters) {
        if (!critter->isAlive()) continue;
        
        // Calculate critter position in pixels
        float xPos = critter->getX();
        float yPos = critter->getY();
        
        // Calculate the center position for the critter within the cell
        int centerX = static_cast<int>(yPos * cellW + cellW / 2);
        int centerY = static_cast<int>(xPos * cellH + cellH / 2);
        
        

        // Determine the radius of the critter based on the cell size
        int radius = std::min(cellW, cellH) / 3;

        if (critter->getSpeed() < critter->getOriginalSpeed()) {
            // Draw a blue aura/circle around slowed critters
            painter.setPen(QPen(QColor(100, 200, 255, 100), 2));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(QPoint(centerX, centerY), radius + 4, radius + 4);
            
            // Add snowflake symbols
            painter.setPen(QColor(150, 220, 255));
            for (int i = 0; i < 4; i++) {
                double angle = i * M_PI / 2;
                QPointF point(centerX + (radius + 8) * cos(angle), centerY + (radius + 8) * sin(angle));
                painter.drawText(QRectF(point.x()-5, point.y()-5, 10, 10), Qt::AlignCenter, "*");
            }
        }
        
        // Draw critter body
        QColor critterColor;
        // Color based on health percentage
        float healthPercentage = static_cast<float>(critter->getHitpoints()) / (10 + critter->getLevel() * 5);
        
        if (healthPercentage > 0.7f) {
            critterColor = QColor(255, 50, 50);  // Healthy: bright red
        } else if (healthPercentage > 0.3f) {
            critterColor = QColor(255, 165, 0);  // Medium health: orange
        } else {
            critterColor = QColor(100, 0, 0);    // Low health: dark red
        }
        
        // Draw the critter as a circle
        painter.setBrush(critterColor);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
        
        // Draw critter ID
        painter.setPen(Qt::white);
        painter.drawText(QRect(centerX - radius, centerY - radius, radius * 2, radius * 2), 
                         Qt::AlignCenter, QString::number(critter->getId()));
        
        // Health bar background
        int healthBarWidth = cellW - 4;
        int healthBarHeight = cellH / 10;
        QRect healthBarRect(centerX - healthBarWidth/2, centerY - radius - healthBarHeight - 2, 
                           healthBarWidth, healthBarHeight);
        
        painter.setBrush(Qt::darkGray);
        painter.setPen(Qt::black);
        painter.drawRect(healthBarRect);
        
        // Health bar fill
        int fillWidth = static_cast<int>(healthBarWidth * healthPercentage);
        QRect fillRect(centerX - healthBarWidth/2, centerY - radius - healthBarHeight - 2, 
                      fillWidth, healthBarHeight);
        
        painter.setBrush(Qt::green);
        painter.setPen(Qt::NoPen);
        painter.drawRect(fillRect);
    }
}

void GameView::drawUI(QPainter& painter)
{
    if (!gameManager) return;

    // Set font for UI elements
    QFont uiFont = painter.font();
    uiFont.setPointSize(12);
    painter.setFont(uiFont);
    
    // Draw coins
    QString coinsText = "Coins: " + QString::number(gameManager->getCoins());
    painter.setPen(Qt::yellow);
    painter.drawText(10, 25, coinsText);
    
    // Draw wave number
    QString waveText = "Wave: " + QString::number(gameManager->getCurrentWave());
    painter.setPen(Qt::white);
    painter.drawText(10, 50, waveText);
    
    // Draw active critters count
    QString crittersText = "Critters: " + QString::number(gameManager->getActiveCritters().size());
    painter.setPen(Qt::white);
    painter.drawText(10, 75, crittersText);
    
    // Draw placement help text when placing tower
    if (placingTower) {
        painter.setPen(Qt::white);
        QString helpText = "Left click to place tower, right click to cancel";
        QFontMetrics fm(uiFont);
        int textWidth = fm.horizontalAdvance(helpText);
        painter.drawText((width() - textWidth) / 2, height() - 20, helpText);
    }
}

bool GameView::canPlaceTowerAt(int row, int col)
{
    if (!gameManager || !gameManager->getMap()) return false;
    
    gameMap* map = gameManager->getMap();
    
    // Check if within map bounds
    if (row < 0 || row >= map->getRows() || col < 0 || col >= map->getCols()) {
        return false;
    }
    
    // Check if this is a valid spot (not on path and no tower already there)
    if (map->canCritterMove(row, col) || map->getTowerAt(row, col)) {
        return false;
    }
    
    // Check if player can afford it
    int cost = 0;
    if (selectedTowerType == "Basic") cost = 100;
    else if (selectedTowerType == "Slow") cost = 150;
    else if (selectedTowerType == "AoE") cost = 200;
    
    return gameManager->getCoins() >= cost;
}

void GameView::selectTower(int row, int col)
{
    Tower* tower = gameManager->getMap()->getTowerAt(row, col);
    if (!tower) return;
    
    selectedTowerRow = row;
    selectedTowerCol = col;
    
    // Show tower action panel
    ui->towerActionGroup->setVisible(true);
    
    // Update tower info
    updateSelectedTowerInfo();
}

void GameView::deselectTower()
{
    selectedTowerRow = -1;
    selectedTowerCol = -1;
    ui->towerActionGroup->setVisible(false);
}

void GameView::updateSelectedTowerInfo()
{
    if (selectedTowerRow < 0 || selectedTowerCol < 0) return;
    
    Tower* tower = gameManager->getMap()->getTowerAt(selectedTowerRow, selectedTowerCol);
    if (!tower) return;
    
    // Update tower stats
    QString towerType;
    if (dynamic_cast<BasicTower*>(tower)) towerType = "Basic Tower";
    else if (dynamic_cast<SlowTower*>(tower)) towerType = "Slow Tower";
    else if (dynamic_cast<AoETower*>(tower)) towerType = "AoE Tower";
    
    QString statText = towerType + "\nLevel: " + QString::number(tower->getLevel()) +
                      "\nPower: " + QString::number(tower->getPower(), 'f', 1) +
                      "\nRange: " + QString::number(tower->getRange(), 'f', 1);
    
    ui->towerStatsLabel->setText(statText);
    
    // Disable upgrade button if at max level
    ui->upgradeTowerButton->setEnabled(tower->getLevel() < 3);
}

QPointF GameView::gridToScreen(float row, float col) const
{
    int cellW = cellWidth();
    int cellH = cellHeight();
    
    return QPointF(col * cellW + cellW / 2, row * cellH + cellH / 2);
}

int GameView::cellWidth() const
{
    if (!gameManager || !gameManager->getMap()) return 0;
    
    // Use only the left 800 pixels for the map (adjust as needed)
    int mapWidth = 800;
    return mapWidth / gameManager->getMap()->getCols();
}

int GameView::cellHeight() const
{
    if (!gameManager || !gameManager->getMap()) return 0;
    return height() / gameManager->getMap()->getRows();
}


void GameView::on_startWaveButton_clicked()
{
    if (gameManager) {
        gameManager->startNextWave();
    }
}


// Add these methods to GameView class implementation

void GameView::on_basicTowerButton_clicked()
{
    // Enter tower placement mode for basic tower
    placingTower = true;
    selectedTowerType = "Basic";
    setCursor(Qt::CrossCursor);
    deselectTower(); // Deselect any selected tower
}

void GameView::on_slowTowerButton_clicked()
{
    // Enter tower placement mode for slow tower
    placingTower = true;
    selectedTowerType = "Slow";
    setCursor(Qt::CrossCursor);
    deselectTower(); // Deselect any selected tower
}

void GameView::on_aoeTowerButton_clicked()
{
    // Enter tower placement mode for AoE tower
    placingTower = true;
    selectedTowerType = "AoE";
    setCursor(Qt::CrossCursor);
    deselectTower(); // Deselect any selected tower
}

void GameView::on_cancelPlacementButton_clicked()
{
    // Cancel tower placement mode
    placingTower = false;
    selectedTowerType = "";
    setCursor(Qt::ArrowCursor);
}

void GameView::on_upgradeTowerButton_clicked()
{
    if (selectedTowerRow >= 0 && selectedTowerCol >= 0) {
        bool success = gameManager->upgradeTower(selectedTowerRow, selectedTowerCol);
        if (success) {
            qDebug() << "Tower upgraded";
            updateSelectedTowerInfo();
        } else {
            qDebug() << "Failed to upgrade tower";
        }
    }
}

void GameView::on_sellTowerButton_clicked()
{
    if (selectedTowerRow >= 0 && selectedTowerCol >= 0) {
        bool success = gameManager->sellTower(selectedTowerRow, selectedTowerCol);
        if (success) {
            qDebug() << "Tower sold";
            deselectTower();
        } else {
            qDebug() << "Failed to sell tower";
        }
    }
}

// Add these methods to GameView class implementation

void GameView::addProjectile(Tower* tower, Critter* target)
{
    // Add thorough null checking
    if (!tower || !target || !target->isAlive()) {
        return;
    }
    
    // Create a new projectile animation
    ProjectileAnimation proj;
    
    try {
        // Set start position (tower location)
        int towerRow = static_cast<int>(tower->getX());
        int towerCol = static_cast<int>(tower->getY());
        proj.startPos = gridToScreen(towerRow, towerCol);
        
        // Set target position (critter location)
        proj.targetPos = gridToScreen(target->getX(), target->getY());
        
        // Initialize progress
        proj.progress = 0.0;
        
        // Set tower type to determine projectile appearance
        if (dynamic_cast<BasicTower*>(tower)) {
            proj.towerType = 0;
            proj.isAoE = false;
        } else if (dynamic_cast<SlowTower*>(tower)) {
            proj.towerType = 1;
            proj.isAoE = false;
        } else if (dynamic_cast<AoETower*>(tower)) {
            proj.towerType = 2;
            proj.isAoE = true;
        } else {
            proj.towerType = 0;
            proj.isAoE = false;
        }
        
        // Add to active projectiles
        activeProjectiles.append(proj);
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in addProjectile:" << e.what();
    }
    catch (...) {
        qDebug() << "Unknown exception in addProjectile";
    }
}

void GameView::updateProjectiles()
{
    // Update all active projectiles
    for (int i = activeProjectiles.size() - 1; i >= 0; i--) {
        // Increase progress more slowly (from 0.05 to 0.02)
        activeProjectiles[i].progress += 0.02; // Slower projectile speed
        
        // Remove completed projectiles
        if (activeProjectiles[i].progress >= 1.0) {
            activeProjectiles.remove(i);
        }
    }
    
    // Request update if there are active projectiles
    if (!activeProjectiles.isEmpty()) {
        update();
    }
}

void GameView::on_pauseButton_clicked()
{
    if (!gameManager) return;
    
    // Toggle pause state
    static bool isPaused = false;
    isPaused = !isPaused;
    
    if (isPaused) {
        gameManager->pauseGame();
        ui->pauseButton->setText("Resume");
        
        // Draw a semi-transparent overlay with "PAUSED" text
        update();
    } else {
        gameManager->resumeGame();
        ui->pauseButton->setText("Pause");
        update();
    }
}

void GameView::on_menuButton_clicked()
{
    // Show confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Return to Menu", 
                                "Are you sure you want to return to the main menu?\nYour game progress will be lost.",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Pause the game
        if (gameManager) {
            gameManager->pauseGame();
        }
        
        // Reset local state
        placingTower = false;
        selectedTowerType = "";
        selectedTowerRow = -1;
        selectedTowerCol = -1;
        activeProjectiles.clear();
        
        // Reset UI elements
        ui->pauseButton->setText("Pause");
        ui->towerActionGroup->setVisible(false);
        
        // Signal to return to menu
        emit returnToMenu();
    }
}

