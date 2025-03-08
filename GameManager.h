#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QTimer>
#include <vector>
#include <map>
#include <string>
#include "map.h"
#include "critter.h"
#include "CritterGroupGenerator.h"

class GameManager : public QObject {
    Q_OBJECT
    
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
    
    // Map setup
    void setMapSize(int x, int y);
    void setStartingCoins(int startingCoins);
    void startGame();
    
    // Tower management
    bool placeTower(int row, int col, const std::string& towerType);
    bool sellTower(int row, int col);
    bool upgradeTower(int row, int col);
    
    // Wave management
    void startNextWave();

    void resetGame();
    
    // Accessors
    gameMap* getMap() const { return map; }
    int getCoins() const { return coins; }
    int getCurrentWave() const { return currentWave; }
    std::vector<Critter*> getActiveCritters() const { return activeCritters; }

public slots:
    // Game control slots
    void pauseGame();
    void resumeGame();
    
private slots:
    void gameLoop();
    void spawnNextCritter();
    
signals:
    void gameStarted();
    void mapUpdated();
    void coinsChanged(int newCoins);
    void waveStarted(int waveNumber);
    void towerAttacked(Tower* tower, Critter* target);
    
private:
    // Map generation
    void generateRandomMap();
    void generateDirectPath(int startX, int startY, int endX, int endY);
    void generateWavyPath(int startX, int startY, int endX, int endY);  // New method
    void addImprovedBranches(int numBranches);  // New method
    void widenPathsSlightly();  // New method
    void addRandomBranches();
    void createSimpleValidMap();
    // Game mechanics
    void moveCritters();
    void performTowerAttacks();
    void cleanupDeadCritters();
    void checkGameStatus();
    
    // Game state
    gameMap* map;
    int coins;
    int mapX;
    int mapY;
    CritterGroupGenerator* critterGenerator;
    int currentWave;
    bool gamePaused;
    
    // Critter management
    std::vector<Critter*> activeCritters;
    std::vector<Critter*> critterQueue;
    std::vector<Critter*> allocatedCritters;
    
    // Timers
    QTimer* gameLoopTimer;
    QTimer* spawnTimer;
    int spawnInterval;
    
    // Time tracking for movement
    qint64 lastUpdateTime;
    
    // Tower costs
    std::map<std::string, int> towerCosts;
};

#endif // GAMEMANAGER_H