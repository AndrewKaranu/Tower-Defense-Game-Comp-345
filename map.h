#ifndef MAP_H
#define MAP_H

#include <vector>
#include <set>
#include "cell.h"
#include "observer.h"



class Map {
private:
    std::vector<std::vector<Cell*>> grid;
    std::set<Observer*> observers;
    int rows, cols;
    std::vector<int> entryCoords = {-1, -1};  // Coordinates for entry point {x, y}
    std::vector<int> exitCoords = {-1, -1}; // Coordinates for exit point {x, y}

public:
    Map(int r, int c);
    ~Map();

    //Observer section:
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
    void notifyObservers();

    //Designing map section:
    void setCell(int r, int c, Cell* cell);
    Cell* getCell(int r, int c) const;

    void setEntry(int r, int c);
    std::vector<int> getEntry() const;  // Returns the entry coordinates as a vector {x, y}
    void removeEntry();

    void setExit(int r, int c);
    std::vector<int> getExit() const; // Returns the exit coordinates as a vector {x, y}
    void removeExit();

    bool isValidPath();
    void display() const;


    int getRows() const;
    int getCols() const;
};

#endif
