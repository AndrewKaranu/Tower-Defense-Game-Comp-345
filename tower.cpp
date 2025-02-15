#include "tower.h"
#include "critter.h"

Tower::Tower() : currentLevel(0) {}

bool Tower::upgrade() {
    if(currentLevel + 1 < levels.size()) {
        currentLevel++;
        return true;
    }
    return false;
}

float Tower::sell() const {
    return levels[currentLevel].refundValue;
}

float Tower::getRange() const { return levels[currentLevel].range; }
float Tower::getPower() const { return levels[currentLevel].power; }
size_t Tower::getLevel() const { return currentLevel + 1; }
float Tower::getFireRate() const { return levels[currentLevel].fireRate; }

bool Tower::isInRange(float x, float y, float critterX, float critterY) const {
    float dx = x - critterX;
    float dy = y - critterY;
    return (dx*dx + dy*dy) <= (levels[currentLevel].range * levels[currentLevel].range);
}