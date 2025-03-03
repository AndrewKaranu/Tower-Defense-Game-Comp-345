#pragma once
#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "tower.h"
#include "base_tower.h"
#include "aoe_tower.h"
#include "slow_tower.h"
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

class TowerObserverGUI : public Observer {
private:
    Tower* tower;
    std::string name;
    std::thread windowThread;
    std::atomic<bool> running{true};
    std::mutex updateMutex;
    
    // GUI elements
    sf::RenderWindow* window;
    sf::Font font;
    sf::CircleShape towerShape;
    sf::CircleShape rangeIndicator;
    sf::Text titleText;
    sf::Text levelText;
    sf::Text powerText;
    sf::Text rangeText;
    sf::Text fireRateText;
    sf::Text positionText;
    sf::Text costText;
    sf::Text refundText;
    
    void initializeGUI();
    void updateGUIElements();
    void runWindow();
    
public:
    TowerObserverGUI(Tower* t, const std::string& observerName = "Tower Observer");
    ~TowerObserverGUI();
    void update() override;
};