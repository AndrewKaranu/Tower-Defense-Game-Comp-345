#include "GameManager.h"
#include "tower.h"
#include "base_tower.h"
#include "slow_tower.h"
#include "aoe_tower.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>
#include <algorithm> // For std::min
#include <QDateTime>  // Add this to get currentMSecsSinceEpoch()
#include <limits> 

GameManager::GameManager(QObject *parent) 
    : QObject(parent), 
    map(nullptr), 
    coins(0), 
    mapX(5), 
    mapY(5), 
    critterGenerator(new CritterGroupGenerator()), 
    currentWave(0),
    gamePaused(false),
    spawnInterval(1000) // 1 second between spawns
{
    // Initialize game loop timer
    gameLoopTimer = new QTimer(this);
    connect(gameLoopTimer, &QTimer::timeout, this, &GameManager::gameLoop);
    
    // Initialize spawn timer
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &GameManager::spawnNextCritter);
    
    // Initialize the lastUpdateTime
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    
    // Initialize tower costs
    towerCosts["Basic"] = 100;
    towerCosts["Slow"] = 150;
    towerCosts["AoE"] = 200;
}

GameManager::~GameManager() {
    delete map;
    delete critterGenerator;
    
    // Clean up any active critters - these are just pointers to elements in allocatedCritters
    activeCritters.clear();
    
    // Clean up any queued critters - these are just pointers to elements in allocatedCritters
    critterQueue.clear();
    
    // Delete all allocated critter arrays
    for (auto array : allocatedCritters) {
        delete[] array; // Use delete[] for arrays
    }
    allocatedCritters.clear();
    
    // Delete timers
    if (gameLoopTimer) {
        gameLoopTimer->stop();
    }
    
    if (spawnTimer) {
        spawnTimer->stop();
    }
}

void GameManager::setMapSize(int x, int y) {
    mapX = x;
    mapY = y;
    std::cout << "Map size set to " << x << "x" << y << std::endl;
}

void GameManager::setStartingCoins(int startingCoins) {
    coins = startingCoins;
    std::cout << "Starting coins set to " << coins << std::endl;
    emit coinsChanged(coins); // Emit the signal to update the UI
}
void GameManager::resetGame() {
    // Stop timers
    if (gameLoopTimer) gameLoopTimer->stop();
    if (spawnTimer) spawnTimer->stop();
    
    // Delete map
    if (map) {
        delete map;
        map = nullptr;
    }
    
    // Clean up active critters
    activeCritters.clear();
    
    // Clean up critter queue
    critterQueue.clear();
    
    // Delete all allocated critter arrays
    for (auto array : allocatedCritters) {
        delete[] array;
    }
    allocatedCritters.clear();
    
    // Reset wave counter
    currentWave = 0;
    
    // Reset pause state
    gamePaused = false;
    
    // Reset critter generator
    if (critterGenerator) {
        critterGenerator->reset();
    }
    
    // Update UI
    emit mapUpdated();
}

void GameManager::startGame() {
    // Clean up any existing game state first
    resetGame();
    
    // Create new map
    map = new gameMap(mapX, mapY);
    
    // Generate a random but valid map
    generateRandomMap();
    
    std::cout << "Game started with map size " << mapX << "x" << mapY << " and " << coins << " coins." << std::endl;
    
    // Start the game loop
    gameLoopTimer->start(100); // 100ms = 10 updates per second
    
    emit gameStarted();
    emit coinsChanged(coins);
    emit mapUpdated();
}

void GameManager::generateRandomMap() {
    bool validMap = false;
    int attempts = 0;
    const int maxAttempts = 20;
    
    while (!validMap && attempts < maxAttempts) {
        attempts++;
        
        // Reset the map by removing any previous cells
        if (map != nullptr) {
            for (int i = 0; i < mapY; i++) {
                for (int j = 0; j < mapX; j++) {
                    map->setCell(i, j, nullptr);
                }
            }
        }
        
        // Fill the map with scenery cells
        for (int i = 0; i < mapY; i++) {
            for (int j = 0; j < mapX; j++) {
                map->setCell(i, j, new sceneryCell());
            }
        }
        
        // Generate entry and exit points on opposite sides
        int entryEdge, exitEdge;
        entryEdge = rand() % 4; // 0: top, 1: right, 2: bottom, 3: left
        exitEdge = (entryEdge + 2) % 4; // Choose opposite edge for exit
        
        // Set entry and exit points with randomized positions
        int entryX = 0, entryY = 0, exitX = 0, exitY = 0;
        
        // When working with edge selection:
        // Top (0) and Bottom (2) edges run along the X axis (columns)
        // Left (3) and Right (1) edges run along the Y axis (rows)
        switch(entryEdge) {
            case 0: // Top edge
                entryX = 0;
                entryY = rand() % mapX;
                break;
            case 1: // Right edge
                entryX = rand() % mapY;
                entryY = mapX - 1;
                break;
            case 2: // Bottom edge
                entryX = mapY - 1;
                entryY = rand() % mapX;
                break;
            case 3: // Left edge
                entryX = rand() % mapY;
                entryY = 0;
                break;
        }
        
        switch(exitEdge) {
            case 0: // Top edge
                exitX = 0;
                exitY = rand() % mapX;
                break;
            case 1: // Right edge
                exitX = rand() % mapY;
                exitY = mapX - 1;
                break;
            case 2: // Bottom edge
                exitX = mapY - 1;
                exitY = rand() % mapX;
                break;
            case 3: // Left edge
                exitX = rand() % mapY;
                exitY = 0;
                break;
        }
        
        // Validate that entry and exit points are within bounds
        if (entryX < 0 || entryX >= mapY || entryY < 0 || entryY >= mapX ||
            exitX < 0 || exitX >= mapY || exitY < 0 || exitY >= mapX) {
            continue; // Skip this attempt if coordinates are invalid
        }
        
        // Set entry and exit cells explicitly to ensure they're path cells
        map->setCell(entryX, entryY, new pathCell());
        map->setCell(exitX, exitY, new pathCell());
        map->setEntry(entryX, entryY);
        map->setExit(exitX, exitY);
        
        // Use smarter path generation based on map size
        if (mapX >= 6 && mapY >= 6) {
            generateWavyPath(entryX, entryY, exitX, exitY);
        } else {
            // For smaller maps, use simpler path
            generateDirectPath(entryX, entryY, exitX, exitY);
        }
        
        // Add branching paths for larger maps
        if (mapX >= 8 && mapY >= 8) {
            addImprovedBranches(2 + rand() % 3);
        } else if (mapX >= 5 && mapY >= 5) {
            addImprovedBranches(1 + rand() % 2);
        }
        
        // Slightly widen paths for better critter movement
        widenPathsSlightly();
        
        // Verify map is valid by checking if there's a path from entry to exit
        validMap = map->isValidMap();
    }
    
    if (!validMap) {
        std::cout << "Failed to generate a valid map. Using a simple path." << std::endl;
        createSimpleValidMap();
    } else {
        std::cout << "Valid map generated on attempt " << attempts << std::endl;
    }
}

// Improved version of generateWavyPath
void GameManager::generateWavyPath(int startX, int startY, int endX, int endY) {
    // Create deterministic waypoints
    std::vector<std::pair<int, int>> waypoints;
    
    // Add start point
    waypoints.push_back(std::make_pair(startX, startY));
    
    // Calculate center point with some randomness
    int centerX = (startX + endX) / 2 + (rand() % 3 - 1);
    int centerY = (startY + endY) / 2 + (rand() % 3 - 1);
    
    // Clamp center coordinates to valid range
    centerX = std::max(0, std::min(centerX, mapY - 1));
    centerY = std::max(0, std::min(centerY, mapX - 1));
    
    // Add zigzag waypoints if map is large enough
    if (mapX >= 7 && mapY >= 7) {
        // Add corner points to create a zigzag
        int cornerX1 = centerX;
        int cornerY1 = startY;
        
        int cornerX2 = centerX;
        int cornerY2 = endY;
        
        waypoints.push_back(std::make_pair(cornerX1, cornerY1));
        waypoints.push_back(std::make_pair(cornerX2, cornerY2));
    } else {
        // For smaller maps, just use the center point
        waypoints.push_back(std::make_pair(centerX, centerY));
    }
    
    // Add end point
    waypoints.push_back(std::make_pair(endX, endY));
    
    // Connect all waypoints with direct paths
    for (size_t i = 0; i < waypoints.size() - 1; i++) {
        generateDirectPath(waypoints[i].first, waypoints[i].second,
                          waypoints[i+1].first, waypoints[i+1].second);
    }
}

// Improved method for branching paths
void GameManager::addImprovedBranches(int numBranches) {
    // Find all valid path cells except entry/exit
    std::vector<std::pair<int, int>> pathCells;
    
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (map->canCritterMove(i, j) && 
                !((i == map->getEntryX() && j == map->getEntryY()) || 
                  (i == map->getExitX() && j == map->getExitY()))) {
                pathCells.push_back(std::make_pair(i, j));
            }
        }
    }
    
    if (pathCells.empty()) return;
    
    // Create branches from random path cells
    for (int b = 0; b < numBranches; b++) {
        if (pathCells.empty()) break;
        
        // Pick a random path cell as branch start
        int index = rand() % pathCells.size();
        int startX = pathCells[index].first;
        int startY = pathCells[index].second;
        
        // Choose a branch direction
        int dx = 0, dy = 0;
        while (dx == 0 && dy == 0) {
            dx = (rand() % 3) - 1;
            dy = (rand() % 3) - 1;
        }
        
        // Create a branch of moderate length
        int length = 2 + rand() % 3;
        int x = startX;
        int y = startY;
        
        for (int step = 0; step < length; step++) {
            x += dx;
            y += dy;
            
            // Ensure we stay within map bounds
            if (x < 0 || x >= mapY || y < 0 || y >= mapX) break;
            
            // Don't overlap with existing path cells
            if (map->canCritterMove(x, y)) break;
            
            // Add a new path cell
            map->setCell(x, y, new pathCell());
            
            // Add this cell to pathCells for potential future branches
            pathCells.push_back(std::make_pair(x, y));
            
            // Occasionally change direction for more natural looking branches
            if (rand() % 3 == 0) {
                int newDx = (rand() % 3) - 1;
                int newDy = (rand() % 3) - 1;
                
                // Avoid stopping
                if (newDx == 0 && newDy == 0) continue;
                
                dx = newDx;
                dy = newDy;
            }
        }
        
        // Optionally connect back to an existing path
        if (rand() % 2 == 0 && x >= 0 && x < mapY && y >= 0 && y < mapX) {
            // Find a nearby path cell to connect to
            for (int nx = x - 2; nx <= x + 2; nx++) {
                for (int ny = y - 2; ny <= y + 2; ny++) {
                    if (nx >= 0 && nx < mapY && ny >= 0 && ny < mapX && 
                        map->canCritterMove(nx, ny) && !(nx == x && ny == y)) {
                        // Connect this branch end to another path
                        generateDirectPath(x, y, nx, ny);
                        break;
                    }
                }
            }
        }
    }
}

// Path widening for better critter movement
void GameManager::widenPathsSlightly() {
    // Create a copy of the current path layout
    std::vector<std::vector<bool>> isPath(mapY, std::vector<bool>(mapX, false));
    
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            isPath[i][j] = map->canCritterMove(i, j);
        }
    }
    
    // Widen paths at strategic locations
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (isPath[i][j]) {
                // Count adjacent path cells
                int adjacentPaths = 0;
                if (i > 0 && isPath[i-1][j]) adjacentPaths++;
                if (i < mapY-1 && isPath[i+1][j]) adjacentPaths++;
                if (j > 0 && isPath[i][j-1]) adjacentPaths++;
                if (j < mapX-1 && isPath[i][j+1]) adjacentPaths++;
                
                // Widen paths at junctions and corners (where path turns)
                // This helps critters navigate turns better
                if (adjacentPaths > 1 || rand() % 5 == 0) {
                    // Add path cell in a random adjacent position
                    int tries = 0;
                    while (tries < 4) {
                        int dir = rand() % 4;
                        int ni = i, nj = j;
                        
                        switch (dir) {
                            case 0: ni--; break; // Up
                            case 1: ni++; break; // Down
                            case 2: nj--; break; // Left
                            case 3: nj++; break; // Right
                        }
                        
                        if (ni >= 0 && ni < mapY && nj >= 0 && nj < mapX && 
                            !isPath[ni][nj] && 
                            !(ni == map->getEntryX() && nj == map->getEntryY()) && 
                            !(ni == map->getExitX() && nj == map->getExitY())) {
                            map->setCell(ni, nj, new pathCell());
                            break;
                        }
                        
                        tries++;
                    }
                }
            }
        }
    }
}

void GameManager::generateDirectPath(int startX, int startY, int endX, int endY) {
    // This ensures there's at least one valid path from entry to exit
    int x = startX;
    int y = startY;
    
    // Create path cells for start position
    map->setCell(x, y, new pathCell());
    
    // First move horizontally to align on one axis
    while (x != endX) {
        x += (x < endX) ? 1 : -1;
        map->setCell(x, y, new pathCell());
    }
    
    // Then move vertically to reach the destination
    while (y != endY) {
        y += (y < endY) ? 1 : -1;
        map->setCell(x, y, new pathCell());
    }
}

void GameManager::addRandomBranches() {
    // Create a list of all path cells
    std::vector<std::pair<int, int>> pathCells;
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (map->canCritterMove(i, j)) {
                pathCells.push_back(std::make_pair(i, j));
            }
        }
    }
    
    if (pathCells.empty()) return;
    
    // Add a few random branches
    int numBranches = 1 + rand() % std::min(mapX, mapY);
    
    for (int b = 0; b < numBranches; b++) {
        // Select a random path cell as the start of the branch
        if (pathCells.empty()) break;
        int index = rand() % pathCells.size();
        int x = pathCells[index].first;
        int y = pathCells[index].second;
        
        // Choose a random direction
        int dx = 0, dy = 0;
        do {
            dx = (rand() % 3) - 1; // -1, 0, 1
            dy = (rand() % 3) - 1; // -1, 0, 1
        } while (dx == 0 && dy == 0); // Don't want to stay in place
        
        // Create a branch of random length
        int length = 1 + rand() % 3;
        for (int step = 0; step < length; step++) {
            x += dx;
            y += dy;
            
            // Check boundaries and don't overwrite entry/exit
            if (x < 0 || x >= mapY || y < 0 || y >= mapX ||
                (x == map->getEntryX() && y == map->getEntryY()) ||
                (x == map->getExitX() && y == map->getExitY())) {
                break;
            }
            
            map->setCell(x, y, new pathCell());
            pathCells.push_back(std::make_pair(x, y));
        }
    }
}

void GameManager::createSimpleValidMap() {
    // Clear the existing map
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            map->setCell(i, j, new sceneryCell());
        }
    }
    
    // For rectangular maps, adapt the path layout to the dimensions
    // This creates a zigzag path that works for both square and rectangular maps
    
    // First row is path
    for (int j = 0; j < mapX; j++) {
        map->setCell(0, j, new pathCell());
    }
    
    // Create vertical zigzag connections
    int numRows = std::min(mapY, 10); // Limit number of rows for really tall maps
    
    for (int i = 1; i < numRows - 1; i++) {
        // Alternate between left and right edges
        if (i % 2 == 1) {
            // Create a horizontal row
            for (int j = 0; j < mapX; j++) {
                map->setCell(i, j, new pathCell());
            }
            
            // Connect to next row at the right edge
            if (i + 1 < numRows - 1) {
                map->setCell(i + 1, mapX - 1, new pathCell());
            }
        } else {
            // Connect from right edge to left edge
            map->setCell(i, 0, new pathCell());
        }
    }
    
    // Last row is path
    for (int j = 0; j < mapX; j++) {
        map->setCell(mapY - 1, j, new pathCell());
    }
    
    // Set entry and exit
    map->setEntry(0, 0);
    map->setExit(mapY - 1, mapX - 1);
}

void GameManager::gameLoop() {
    if (gamePaused) return;
    
    // Move critters
    moveCritters();
    
    // Let towers attack
    performTowerAttacks();
    
    // Check game status (win/loss conditions)
    checkGameStatus();
    
    // Signal UI updates
    emit mapUpdated();
}



void GameManager::moveCritters() {
    // Use time-based movement instead of constant movement per frame
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;
    
    // Convert milliseconds to seconds for slow effect update
    double deltaSeconds = deltaTime / 1000.0;
    
    // Don't move critters every frame, have a time accumulator
    static qint64 moveAccumulator = 0;
    moveAccumulator += deltaTime;
    
    // Only move every 300ms (adjust as needed)
    if (moveAccumulator < 300) {
        return;
    }
    
    moveAccumulator = 0;
    
    // Now move each critter along the path
    for (auto it = activeCritters.begin(); it != activeCritters.end();) {
        Critter* critter = *it;
        
        if (!critter) {
            // Handle null pointer - should not happen but just in case
            it = activeCritters.erase(it);
            continue;
        }
        
        // Update slow effect duration
        critter->updateSlowEffect(deltaSeconds);
        
        if (!critter->isAlive()) {
            // Add coins for killing the critter
            coins += critter->getReward();
            emit coinsChanged(coins);
            
            // Debug output
            std::cout << "Critter " << critter->getId() << " died and gave " << critter->getReward() << " coins." << std::endl;
            
            // Just remove from active list - DO NOT DELETE the critter
            it = activeCritters.erase(it);
        }
        // Compare with tolerance for float comparison
        else if (std::abs(critter->getX() - map->getExitX()) < 0.5f && 
                std::abs(critter->getY() - map->getExitY()) < 0.5f) {
            // Critter reached exit - remove it
            std::cout << "Critter " << critter->getId() << " reached the exit!" << std::endl;
            
            // Just remove from active list - DO NOT DELETE the critter
            it = activeCritters.erase(it);
        }
        else {
            // Move the critter along the path
            critter->move(*map);
            ++it;
        }
    }
}
// Update the performTowerAttacks method to add projectile animations

void GameManager::performTowerAttacks() {
    if (!map) return;
    
    std::vector<Tower*> towers = map->getAllTowers();
    
    for (Tower* tower : towers) {
        // Safety check for tower
        if (!tower) continue;
        
        // Track the closest critter for this tower
        Critter* closestTarget = nullptr;
        double minDistance = std::numeric_limits<double>::max();
        
        // Find eligible targets within range
        std::vector<Critter*> targets;
        
        for (Critter* critter : activeCritters) {
            // Safety check for critter
            if (!critter || !critter->isAlive()) continue;
            
            try {
                // Check if the critter is within the tower's range
                double distSquared = tower->getDistanceSquared(tower->getX(), tower->getY(), 
                                                             critter->getX(), critter->getY());
                
                if (distSquared <= tower->getRange() * tower->getRange()) {
                    targets.push_back(critter);
                    
                    // Track closest critter for projectile animation
                    if (distSquared < minDistance) {
                        minDistance = distSquared;
                        closestTarget = critter;
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Exception in performTowerAttacks: " << e.what() << std::endl;
                continue;
            }
        }
        
        // If we found targets, attack them based on tower type
        if (!targets.empty() && closestTarget) {
            // For visual feedback, emit signal for projectile animation
            emit towerAttacked(tower, closestTarget);
            
            // For AoETower, attack all targets in range
            // For other towers, we'll still send the full list of targets but
            // their attack methods will handle targeting appropriately
            tower->attack(targets);
        }
    }
}

void GameManager::cleanupDeadCritters() {
    // Remove dead critters from active list but don't delete them
    auto it = activeCritters.begin();
    while (it != activeCritters.end()) {
        if (!(*it)->isAlive()) {
            it = activeCritters.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::checkGameStatus() {
    // For now, just a stub
    // In a full implementation, you would:
    // 1. Check if all waves are done and no critters left (victory)
    // 2. Check if player lost (e.g., lives reached zero)
    
    std::cout << "Checking game status..." << std::endl;
}

bool GameManager::placeTower(int row, int col, const std::string& towerType) {
    // Check if player has enough coins
    int cost = towerCosts[towerType];
    if (coins < cost) {
        return false;
    }
    
    // Create appropriate tower type
    Tower* tower = nullptr;
    if (towerType == "Basic") {
        tower = new BasicTower();
    } else if (towerType == "Slow") {
        tower = new SlowTower();
    } else if (towerType == "AoE") {
        tower = new AoETower();
    }
    
    // Try to place tower
    if (map && tower && map->placeTower(row, col, tower)) {
        // Deduct coins on successful placement
        coins -= cost;
        emit coinsChanged(coins);
        emit mapUpdated();
        return true;
    }
    
    // Clean up if tower placement failed
    delete tower;
    return false;
}

bool GameManager::sellTower(int row, int col) {
    if (!map) return false;
    
    Tower* tower = map->getTowerAt(row, col);
    if (!tower) {
        return false;
    }
    
    // Calculate refund and remove tower
    int refund = tower->sell();
    tower = map->removeTower(row, col);
    
    // Use safe deletion with a timer
    QTimer::singleShot(100, this, [tower]() {
        delete tower;
    });
    
    // Update coins and return value
    coins += refund;
    emit coinsChanged(coins);
    emit mapUpdated();
    
    return true;
}

bool GameManager::upgradeTower(int row, int col) {
    if (!map) return false;
    
    Tower* tower = map->getTowerAt(row, col);
    if (!tower) {
        return false;
    }
    
    // Attempt upgrade
    return tower->upgrade();
}


// Add this new method:
void GameManager::spawnNextCritter() {
    if (!critterQueue.empty() && map) {
        // Get the next critter from the queue
        Critter* critter = critterQueue.front();
        critterQueue.erase(critterQueue.begin());
        
        // Set its position to the entry point
        critter->setPosition(map->getEntryX(), map->getEntryY());
        
        // Debug output to verify critter position
        std::cout << "Spawning critter at entry point: (" 
                  << map->getEntryX() << ", " << map->getEntryY() 
                  << "). Critter ID: " << critter->getId() << std::endl;
        
        // Add it to the active critters
        activeCritters.push_back(critter);
        
        // If queue is empty, stop the timer
        if (critterQueue.empty()) {
            spawnTimer->stop();
        }
        
        // Signal that the map has been updated
        emit mapUpdated();
    }
}

// ADD THIS AFTER spawnNextCritter() function (around line 470)
void GameManager::startNextWave() {
    // Increase wave counter
    currentWave++;
    
    std::cout << "Starting wave " << currentWave << std::endl;
    std::cout << "Entry point: (" << map->getEntryX() << ", " << map->getEntryY() << ")" << std::endl;
    std::cout << "Exit point: (" << map->getExitX() << ", " << map->getExitY() << ")" << std::endl;
    
    // Generate new critters
    int numCritters = 5; // Start with a fixed number of critters for testing
    
    // Check if the map is initialized
    if (!map) {
        std::cerr << "Error: Map is not initialized when starting wave" << std::endl;
        return;
    }
    
    try {
        // Generate critters
        Critter* newCritters = critterGenerator->generateCritters(
            currentWave, 
            numCritters, 
            map->getEntryX(), 
            map->getEntryY()
        );
        
        // Safety check
        if (!newCritters) {
            std::cerr << "Error: Failed to generate critters" << std::endl;
            return;
        }
        
        // Store the pointer to the array for later deletion
        allocatedCritters.push_back(newCritters);
        
        // Add the critters to the queue
        for (int i = 0; i < numCritters; i++) {
            Critter* critter = &newCritters[i];
            if (critter) {
                // Initialize critter position at entry point
                critter->setPosition(map->getEntryX(), map->getEntryY());
                critterQueue.push_back(critter);
                std::cout << "Added critter #" << critter->getId() << " to queue with position ("
                          << critter->getX() << ", " << critter->getY() << ")" << std::endl;
            }
        }
        
        // Start spawning critters if we have any
        if (!critterQueue.empty()) {
            spawnTimer->start(spawnInterval);
        }
        
        // Signal that a new wave has started
        emit waveStarted(currentWave);
    } 
    catch (const std::exception& e) {
        std::cerr << "Exception in startNextWave: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception in startNextWave" << std::endl;
    }
}



void GameManager::pauseGame() {
    gamePaused = true;
    if (gameLoopTimer) gameLoopTimer->stop();
    if (spawnTimer) spawnTimer->stop();
}

void GameManager::resumeGame() {
    gamePaused = false;
    if (gameLoopTimer) gameLoopTimer->start(100);  // 100ms = 10 updates per second
    if (spawnTimer && !critterQueue.empty()) spawnTimer->start(spawnInterval);
}