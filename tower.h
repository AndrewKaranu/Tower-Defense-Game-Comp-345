#pragma once
#include <vector>
#include <iostream>

struct LevelStats {
    float buyCost;
    float refundValue;
    float range;
    float power;
    float fireRate;
};

class Critter;

class Tower {
protected:
    size_t currentLevel;
    std::vector<LevelStats> levels;
    
public:
    Tower();
    virtual ~Tower() = default;

    // Core functionality
    virtual void attack(std::vector<Critter*>& targets) = 0;
    bool upgrade();
    float sell() const;
    
    // Getters
    float getRange() const;
    float getPower() const;
    size_t getLevel() const;
    float getFireRate() const;

    // Helper
    bool isInRange(float x, float y, float critterX, float critterY) const;
};