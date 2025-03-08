#include "MapObserver.h"
#include "tower.h"
#include "base_tower.h"
#include "slow_tower.h"
#include "aoe_tower.h"
#include <QPainter>
#include <algorithm>

MapObserver::MapObserver(gameMap* m, QWidget* parent) 
    : QWidget(parent), subject(m) 
{
    subject->attach(this);
    setMinimumSize(500, 500);
}

MapObserver::~MapObserver() {
    subject->detach(this);
}

void MapObserver::update() {
    // Trigger repaint when map is updated
    repaint();
}

void MapObserver::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    int cellSize = std::min(width(), height()) / std::max(subject->getRows(), subject->getCols());
    
    // Draw cells
    for (int i = 0; i < subject->getRows(); i++) {
        for (int j = 0; j < subject->getCols(); j++) {
            QRect cellRect(j * cellSize, i * cellSize, cellSize, cellSize);
            
            // Different colors based on cell type
            if (i == subject->getEntryX() && j == subject->getEntryY()) {
                painter.fillRect(cellRect, QColor(0, 200, 0));  // Entry - green
            } else if (i == subject->getExitX() && j == subject->getExitY()) {
                painter.fillRect(cellRect, QColor(200, 0, 0));  // Exit - red
            } else if (subject->canCritterMove(i, j)) {
                painter.fillRect(cellRect, QColor(150, 150, 150));  // Path - gray
            } else {
                painter.fillRect(cellRect, QColor(100, 200, 100));  // Scenery - light green
            }
            
            // Draw border
            painter.setPen(Qt::black);
            painter.drawRect(cellRect);
            
            // Draw towers if present
            Tower* tower = subject->getTowerAt(i, j);
            if (tower) {
                // Draw different shapes/colors based on tower type
                if (dynamic_cast<BasicTower*>(tower)) {
                    painter.setBrush(QColor(100, 100, 200));  // Blue
                } else if (dynamic_cast<SlowTower*>(tower)) {
                    painter.setBrush(QColor(0, 200, 200));    // Cyan
                } else if (dynamic_cast<AoETower*>(tower)) {
                    painter.setBrush(QColor(200, 0, 200));    // Purple
                }
                
                // Draw tower as a circle
                painter.setPen(Qt::black);
                QRect towerRect = cellRect.adjusted(cellSize/4, cellSize/4, -cellSize/4, -cellSize/4);
                painter.drawEllipse(towerRect);
                
                // Display tower level
                painter.setPen(Qt::white);
                painter.drawText(cellRect, Qt::AlignCenter, QString::number(tower->getLevel()));
            }
        }
    }
}