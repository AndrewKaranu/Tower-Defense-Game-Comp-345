# Tower Defense Game - Assignment 1

## Game Rules

This project implements the initial version of a tower defense game. The core game mechanics involve:

*   **Waves of Enemies:** Enemies (critters) spawn in waves and attempt to move from an entry point to an exit point on the map.
*   **Towers:** Towers defend against the critters. Towers of different specifications attack critters within their range.
*   **Map:** The game takes place on a map consisting of path cells (where critters move) and scenery cells (where towers can be placed).
*   **Tower Types:** Different types of towers have different attack strategies (single target, area of effect, slowing).
*   **Upgrades:** Towers can be upgraded to increase their power and range.
*   **Selling:** Towers can be sold for a refund.

## Design

The design adopts an object-oriented approach with the following key classes:

*   **`Critter`:** Represents an enemy critter with attributes like hitpoints, speed, reward, and position. Key methods include constructors, getters/setters for properties (id, hitpoints, reward, strength, speed, level), `takeDamage()`, `isAlive()`, and `move()`.
*   **`Tower`:** Base class for all towers, defining common functionality like attacking, upgrading, and selling.
*   **`BasicTower`:** A tower that attacks a single critter within its range.
*   **`AoETower`:** A tower that attacks all critters within its range.
*   **`SlowTower`:** A tower that slows down critters within its range.
*   **`gameMap`:** Represents the game map, managing cells, entry/exit points, and map validity.
*   **`Cell`:** Abstract base class for map cells (`pathCell` and `sceneryCell`).
*   **`pathCell`:** Represents a path cell where critters can move.
*   **`sceneryCell`:** Represents a scenery cell where towers can be placed.
*   **`CritterGroupGenerator`:** Generates waves of critters with varying stats based on the wave number. Key methods include the constructor, destructor, `generateCritters()` (dynamically allocates critter arrays), and `reset()`.  Memory management of the critter arrays returned by `generateCritters()` is crucial.

The `as1_driver.cpp` file contains the main function and demonstration code for the various game components.

*   **Map Generation Demonstrations:**
    *   **Valid Map (`checkValidMap()`):** Creates a 5x5 map with a single entry and exit point, connected paths, and demonstrates critter movement on path cells and tower placement on scenery cells.
    *   **Invalid Maps (`checkInvalidMaps()`):** Demonstrates map invalidity due to missing entry/exit points, multiple entry/exit points, and the inability to add a second entry/exit point.
    *   **Disconnected Map (`checkDisconnectedMap()`):** Demonstrates map invalidity due to disconnected paths between the entry and exit points, and the creation of an empty map.
*   **Critter Generation:** Shows how critters are generated in waves with varying stats based on the wave number.
*   **Tower-Critter Interactions:** Demonstrates the functionality of different tower types (Basic, AoE, Slow) and their interactions with critters, including attacking, upgrading, and selling towers.
*   **Critter-Map Interaction:** Simulates critter movement on a sample map from the entry point to the exit point.

## Compilation Instructions

This project is written in C++ and can be compiled using g++.

1.  **Prerequisites:** We coded our assignment in a docker dev container with the Ubuntu 24.04 system.

2.  **Compilation:** Navigate to the project directory in the terminal and use the provided `Makefile` to compile the code:

    ```sh
    make
    ```

    This command will compile all the `.cpp` files and create an executable named 'as1_driver'.

## Usage Instructions

After successful compilation, you can run the executable using:

```sh
./as1_driver