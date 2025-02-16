#include <iostream>
#include "map.h"
using namespace std;

void checkValidMap()
{
    cout << "Creating My Map 1:\n";
    // Create a 5x5 game map
    gameMap myMap1(5, 5);

    // Set up a valid path (placing path cells and scenery cells in the map)
    myMap1.setCell(0, 0, new pathCell());
    myMap1.setCell(0, 1, new pathCell());
    myMap1.setCell(0, 2, new pathCell());
    myMap1.setCell(0, 3, new pathCell());
    myMap1.setCell(0, 4, new sceneryCell());

    myMap1.setCell(1, 0, new pathCell());
    myMap1.setCell(1, 1, new sceneryCell());
    myMap1.setCell(1, 2, new pathCell());
    myMap1.setCell(1, 3, new sceneryCell());
    myMap1.setCell(1, 4, new pathCell());

    myMap1.setCell(2, 0, new pathCell());
    myMap1.setCell(2, 1, new sceneryCell());
    myMap1.setCell(2, 2, new pathCell());
    myMap1.setCell(2, 3, new pathCell());
    myMap1.setCell(2, 4, new sceneryCell());

    myMap1.setCell(3, 0, new pathCell());
    myMap1.setCell(3, 1, new sceneryCell());
    myMap1.setCell(3, 2, new pathCell());
    myMap1.setCell(3, 3, new pathCell());
    myMap1.setCell(3, 4, new pathCell());

    myMap1.setCell(4, 0, new sceneryCell());
    myMap1.setCell(4, 1, new sceneryCell());
    myMap1.setCell(4, 2, new sceneryCell());
    myMap1.setCell(4, 3, new sceneryCell());
    myMap1.setCell(4, 4, new pathCell());

    // Set entry and exit points
    myMap1.setEntry(0, 0);
    myMap1.setExit(4, 4);

    // Display the map
    cout << "\nGame Map 1:\n";
    myMap1.displayMap();

    // Check map validity
    if (myMap1.isValidMap())
    {
        cout << "\nThe map is valid (as expected)!\n";
        cout << "P: Critters are allowed to move!\n";
        cout << "S: Towers can be placed!\n";
    }
    else
    {
        cout << "\nThe map is invalid (code failed)!\n";
    }

    // Checking canCritterMove()
    cout << "\nCritter Movement Check:\n";
    cout << "(0,0) Path: " << (myMap1.canCritterMove(0, 0) ? "YES\n" : "NO\n");
    cout << "(1,1) Scenery: " << (myMap1.canCritterMove(1, 1) ? "YES\n" : "NO\n");
    cout << "(0,1) Path: " << (myMap1.canCritterMove(0, 1) ? "YES\n" : "NO\n");
    cout << "(1,0) Path: " << (myMap1.canCritterMove(1, 0) ? "YES\n" : "NO\n");

    // Checking canPlaceTower()
    cout << "\nTower Placement Check:\n";
    cout << "(0,0) Path: " << (myMap1.canPlaceTower(0, 0) ? "YES\n" : "NO\n");
    cout << "(1,1) Scenery: " << (myMap1.canPlaceTower(1, 1) ? "YES\n" : "NO\n");
    cout << "(0,1) Path: " << (myMap1.canPlaceTower(0, 1) ? "YES\n" : "NO\n");
    cout << "(1,0) Path: " << (myMap1.canPlaceTower(1, 0) ? "YES\n" : "NO\n");
};

void checkInvalidMaps()
{
    cout << "\nCreating my map 2 - map without Entry(E) or Exit(X)\n";

    // Create a 3x4 game map
    gameMap myMap2(4, 3);

    // Set some paths and scenery but do not assign entry/exit
    myMap2.setCell(0, 0, new pathCell());
    myMap2.setCell(0, 1, new pathCell());
    myMap2.setCell(0, 2, new sceneryCell());

    myMap2.setCell(1, 0, new sceneryCell());
    myMap2.setCell(1, 1, new pathCell());
    myMap2.setCell(1, 2, new sceneryCell());

    myMap2.setCell(2, 0, new sceneryCell());
    myMap2.setCell(2, 1, new pathCell());
    myMap2.setCell(2, 2, new pathCell());

    myMap2.setCell(3, 0, new pathCell());
    myMap2.setCell(3, 1, new sceneryCell());
    myMap2.setCell(3, 2, new pathCell());

    // Display the map
    cout << "\nGame Map 2:\n";
    myMap2.displayMap();

    // Checking validity!
    if (myMap2.isValidMap())
    {
        cout << "\nThe map is valid (code fails)!\n";
    }
    else
    {
        cout << "\nThe map is invalid! No entry or exit (as expected)!\n";
    }

    //Trying to add a second entry point should give an error message!
    cout << "\nAdding 2 entry points:\n";
    myMap2.setEntry(0, 0);
    myMap2.setEntry(0, 2);

    //Removing entry point and setting entry to a scenery cell should give an error message!
    myMap2.removeEntry();
    myMap2.setEntry(0,2);

    //Trying to add a second exit point should give an error message!
    cout << "\nAdding 2 exit points:\n";
    myMap2.setExit(3, 2);
    myMap2.setExit(3, 1);

    //Removing entry point and setting entry to a scenery cell should give an error message!
    myMap2.removeExit();
    myMap2.setExit(3,1);

};

void checkDisconnectedMap()
{
    cout << "\nCreating my map 3 - invalid map - disconnected paths:\n";
    // Create a 4x4 game map
    gameMap myMap3(4, 4);

    // Set up a valid path (placing path cells and scenery cells in the map)
    myMap3.setCell(0, 0, new pathCell());
    myMap3.setCell(0, 1, new pathCell());
    myMap3.setCell(0, 2, new pathCell());
    myMap3.setCell(0, 3, new pathCell());

    myMap3.setCell(1, 0, new pathCell());
    myMap3.setCell(1, 1, new sceneryCell());
    myMap3.setCell(1, 2, new pathCell());
    myMap3.setCell(1, 3, new sceneryCell());

    myMap3.setCell(2, 0, new pathCell());
    myMap3.setCell(2, 1, new sceneryCell());
    myMap3.setCell(2, 2, new pathCell());
    myMap3.setCell(2, 3, new sceneryCell());

    myMap3.setCell(3, 0, new pathCell());
    myMap3.setCell(3, 1, new sceneryCell());
    myMap3.setCell(3, 2, new sceneryCell());
    myMap3.setCell(3, 3, new pathCell());

    // Set entry and exit points
    myMap3.setEntry(0, 0);
    myMap3.setExit(3, 3);

    //Display the map:
    cout << "\nGame Map 3 - Disconnected paths:\n";
    myMap3.displayMap();

    // Check map validity
    if (myMap3.isValidMap())
    {
        cout << "The map is valid (code fails)!\n";
    }
    else
    {
        cout << "\nThe map is invalid! There are disconnected paths(code works)!\n";
    }

    cout << "Creating my map 4 - empty map:\n";

    gameMap myMap4(4, 6);

    // Display the map
    cout << "\nGame Map 4 - empty map:\n";
    myMap4.displayMap();
};

int main()
{

    checkValidMap();
    checkInvalidMaps();
    checkDisconnectedMap();

    return 0;
}
