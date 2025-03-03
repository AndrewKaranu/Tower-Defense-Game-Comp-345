#include "TowerObserverGUI.h"
#include <iostream>

TowerObserverGUI::TowerObserverGUI(Tower* t, const std::string& observerName) 
    : tower(t), name(observerName) {
    
    tower->addObserver(this);
    
    // Start the window thread
    windowThread = std::thread(&TowerObserverGUI::runWindow, this);
}

TowerObserverGUI::~TowerObserverGUI() {
    tower->removeObserver(this);
    
    // Stop the thread
    running = false;
    if (windowThread.joinable()) {
        windowThread.join();
    }
}

void TowerObserverGUI::update() {
    updateGUIElements();
}

void TowerObserverGUI::initializeGUI() {
    // Create window in the thread function
    window = new sf::RenderWindow(sf::VideoMode(600, 500), name);
    window->setFramerateLimit(30);
    
    // Load font
    if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
        // Try alternate paths
        if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf")) {
            // If no system fonts found, use default
            std::cerr << "Warning: Could not load font, using default" << std::endl;
        }
    }
    
    // Tower representation (center of the window)
    towerShape.setRadius(25);
    towerShape.setOrigin(25, 25);
    towerShape.setPosition(300, 250);
    
    // Different colors for different tower types
    if (dynamic_cast<BasicTower*>(tower)) {
        towerShape.setFillColor(sf::Color(50, 50, 200)); // Blue for BasicTower
    } else if (dynamic_cast<AoETower*>(tower)) {
        towerShape.setFillColor(sf::Color(200, 50, 50)); // Red for AoETower
    } else if (dynamic_cast<SlowTower*>(tower)) {
        towerShape.setFillColor(sf::Color(50, 200, 50)); // Green for SlowTower
    } else {
        towerShape.setFillColor(sf::Color(150, 150, 150)); // Gray for unknown
    }
    
    // Range indicator (circle around tower)
    rangeIndicator.setRadius(1); // Initial size will be updated
    rangeIndicator.setOrigin(1, 1); // Will be updated
    rangeIndicator.setPosition(300, 250);
    rangeIndicator.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent
    rangeIndicator.setOutlineColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white
    rangeIndicator.setOutlineThickness(2);
    
    // Title
    titleText.setFont(font);
    titleText.setString(name);
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(20, 20);
    
    // Statistics texts
    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(20, 70);
    
    powerText.setFont(font);
    powerText.setCharacterSize(18);
    powerText.setFillColor(sf::Color::White);
    powerText.setPosition(20, 110);
    
    rangeText.setFont(font);
    rangeText.setCharacterSize(18);
    rangeText.setFillColor(sf::Color::White);
    rangeText.setPosition(20, 150);
    
    fireRateText.setFont(font);
    fireRateText.setCharacterSize(18);
    fireRateText.setFillColor(sf::Color::White);
    fireRateText.setPosition(20, 190);
    
    costText.setFont(font);
    costText.setCharacterSize(18);
    costText.setFillColor(sf::Color::White);
    costText.setPosition(20, 230);
    
    refundText.setFont(font);
    refundText.setCharacterSize(18);
    refundText.setFillColor(sf::Color::White);
    refundText.setPosition(20, 270);
    
    positionText.setFont(font);
    positionText.setCharacterSize(18);
    positionText.setFillColor(sf::Color::White);
    positionText.setPosition(20, 310);
    
    updateGUIElements();
}

void TowerObserverGUI::updateGUIElements() {
    std::lock_guard<std::mutex> lock(updateMutex);
    
    // Update range indicator
    float range = tower->getRange() * 30; // Scale range for visibility
    rangeIndicator.setRadius(range);
    rangeIndicator.setOrigin(range, range);
    
    // Update position based on tower position
    towerShape.setPosition(300 + tower->getPositionX() * 10, 250 + tower->getPositionY() * 10);
    rangeIndicator.setPosition(300 + tower->getPositionX() * 10, 250 + tower->getPositionY() * 10);
    
    // Update texts
    levelText.setString("Level: " + std::to_string(tower->getLevel()));
    powerText.setString("Power: " + std::to_string(tower->getPower()));
    rangeText.setString("Range: " + std::to_string(tower->getRange()));
    fireRateText.setString("Fire Rate: " + std::to_string(tower->getFireRate()));
    
    // Update buy cost and refund if methods are available
    try {
        costText.setString("Buy Cost: " + std::to_string(tower->getBuyCost()));
        refundText.setString("Refund: " + std::to_string(tower->sell()));
    } catch (...) {
        costText.setString("Buy Cost: N/A");
        refundText.setString("Refund: N/A");
    }
    
    positionText.setString("Position: (" + std::to_string(tower->getPositionX()) + 
                          ", " + std::to_string(tower->getPositionY()) + ")");
}

void TowerObserverGUI::runWindow() {
    initializeGUI();
    
    while (running && window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        
        window->clear(sf::Color(30, 30, 30));
        
        {
            std::lock_guard<std::mutex> lock(updateMutex);
            window->draw(rangeIndicator);
            window->draw(towerShape);
            window->draw(titleText);
            window->draw(levelText);
            window->draw(powerText);
            window->draw(rangeText);
            window->draw(fireRateText);
            window->draw(costText);
            window->draw(refundText);
            window->draw(positionText);
        }
        
        window->display();
        sf::sleep(sf::milliseconds(33)); // ~30 FPS
    }
    
    if (window->isOpen()) {
        window->close();
    }
    
    delete window;
}