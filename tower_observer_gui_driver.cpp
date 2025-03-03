// tower_observer_gui_driver.cpp
#include <iostream>
#include "tower.h"
#include "base_tower.h"
#include "slow_tower.h"
#include "aoe_tower.h"
#include "TowerObserverGUI.h"
#include <thread>
#include <chrono>

void testBasicTower() {
    std::cout << "\n=== Testing Basic Tower Observer ===\n";
    
    // Create a tower and attach an observer
    BasicTower* tower = new BasicTower();
    TowerObserverGUI* observer = new TowerObserverGUI(tower, "Basic Tower");
    
    // Allow time for the window to initialize
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Change tower properties every few seconds
    std::cout << "\nUpgrading tower...\n";
    tower->upgrade();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nMoving tower to position (3, 4)...\n";
    tower->setPosition(3, 4);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nUpgrading tower again...\n";
    tower->upgrade();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nMoving tower to position (5, -2)...\n";
    tower->setPosition(5, -2);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Clean up
    delete observer;
    delete tower;
}

void testAoETower() {
    std::cout << "\n=== Testing AoE Tower Observer ===\n";
    
    // Create a tower and attach an observer
    AoETower* tower = new AoETower();
    TowerObserverGUI* observer = new TowerObserverGUI(tower, "Area of Effect Tower");
    
    // Allow time for the window to initialize
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Change tower properties
    std::cout << "\nUpgrading tower...\n";
    tower->upgrade();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nMoving tower to position (-3, 2)...\n";
    tower->setPosition(-3, 2);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nUpgrading tower again...\n";
    tower->upgrade();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Clean up
    delete observer;
    delete tower;
}

void testSlowTower() {
    std::cout << "\n=== Testing Slow Tower Observer ===\n";
    
    // Create a tower and attach an observer
    SlowTower* tower = new SlowTower();
    TowerObserverGUI* observer = new TowerObserverGUI(tower, "Slow Tower");
    
    // Allow time for the window to initialize
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Change tower properties
    std::cout << "\nUpgrading tower...\n";
    tower->upgrade();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nMoving tower to position (2, 8)...\n";
    tower->setPosition(2, 8);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\nMoving tower to position (-4, -4)...\n";
    tower->setPosition(-4, -4);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Clean up
    delete observer;
    delete tower;
}

int main() {
    std::cout << "=== Tower Observer GUI Pattern Demonstration ===\n";
    std::cout << "Each test will open a window displaying the tower.\n";
    std::cout << "Close the window or wait for the test to complete.\n";
    
    int choice;
    do {
        std::cout << "\nSelect a test:\n";
        std::cout << "1. Basic Tower Observer\n";
        std::cout << "2. AoE Tower Observer\n";
        std::cout << "3. Slow Tower Observer\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                testBasicTower();
                break;
            case 2:
                testAoETower();
                break;
            case 3:
                testSlowTower();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
    
    return 0;
}