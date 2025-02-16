#include <iostream>
#include <vector>
using namespace std;

enum cellType
{
    SCENERY,
    PATH
};

class Cell
{
public:
    // A pure virtual function, hence this base class is an abstract class
    virtual void display() = 0;
    virtual cellType getCellType() = 0;
    virtual bool canPlaceTower() = 0;
    virtual bool canCritterMove() = 0;
    // Destructor class: this is used so that when we try to delete a specific type of class, it destroys the right class and does not cause memory leaks
    // Why do we not need a constructor here? We don't need one. We are not creating any object with the cell class itself. IOW, bc cell is abstract.
    virtual ~Cell() {};
};

class sceneryCell : public Cell
{
public:
    void display() override
    {
        cout << "S";
    }
    cellType getCellType() override
    {
        return SCENERY;
    }

    bool canPlaceTower() override
    {
        return true;
    }

    bool canCritterMove() override
    {
        return false;
    }
};

class pathCell : public Cell
{
public:
    void display() override
    {
        cout << "P";
    }

    cellType getCellType() override
    {
        return PATH;
    }

    bool canPlaceTower() override
    {
        return false;
    }

    bool canCritterMove() override
    {
        return true;
    }
};

class gameMap
{
private:
    // Initializing the 2D vector where each inner vector represents a row and each element in that row is a pointer to a Cell object.
    vector<vector<Cell *> > grid;
    int rows, cols;
    int entryX = -1, entryY = -1;
    int exitX = -1, exitY = -1;

public:
    // Resizes the grid to have length rows and each row contains width nullptr pointers indicating empty cells(columns).
    gameMap(int r, int c) : rows(r), cols(c)
    {
        grid.resize(rows, vector<Cell *>(cols, nullptr));
    }
    // Set/access individual cells using this method r:row c:column
    void setCell(int r, int c, Cell *cell)
    {
        if (r >= 0 && r < rows && c >= 0 && c < cols)
        {
            if (grid[r][c] != nullptr)
            {
                delete grid[r][c];
            }
            grid[r][c] = cell;
        }
    }

    void setEntry(int r, int c) {
    if (entryX != -1 && entryY != -1) { 
        cout << "Error: An entry point already exists at (" << entryX << ", " << entryY << "). Cannot add another entry point.\n";
        return;
    }
    if (grid[r][c] == nullptr) {
        cout << "Error: Cannot set entry to an empty cell.\n";
        return;
    }
    if (grid[r][c]->getCellType() != PATH) {
        cout << "Error: Entry must be placed on a PATH cell.\n";
        return;
    }

    entryX = r;
    entryY = c;
    }

    void removeEntry() {
        if (entryX != -1 && entryY != -1) {
            cout << "\nRemoving entry point at (" << entryX << ", " << entryY << ").\n";
            entryX = -1;
            entryY = -1;
        } else {
            cout << "\nNo entry point to remove.\n";
        }
    }

    void setExit(int r, int c) {
    if (exitX != -1 && exitY != -1) {  
        cout << "Error: An exit point already exists at (" << exitX << ", " << exitY << "). Cannot add another exit point.\n";
        return;
    }
    if (grid[r][c] == nullptr) {
        cout << "Error: Cannot set exit to an empty cell.\n";
        return;
    }
    if (grid[r][c]->getCellType() != PATH) {
        cout << "Error: Exit must be placed on a PATH cell.\n";
        return;
    }

    exitX = r;
    exitY = c;
    }

    void removeExit() {
        if (exitX != -1 && exitY != -1) {
            cout << "\nRemoving exit point at (" << exitX << ", " << exitY << ").\n";
            exitX = -1;
            exitY = -1;
        } else {
            cout << "\nNo exit point to remove.\n";
        }
    }

    // Check if a critter can move along the path from a specific cell
    bool canCritterMove(int r, int c) const
    {
        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr)
        {
            return grid[r][c]->canCritterMove();
        }
        return false;
    }

    // Check if a tower can be placed at a specific cell
    bool canPlaceTower(int r, int c) const
    {
        if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr)
        {
            return grid[r][c]->canPlaceTower();
        }
        return false;
    }

    void displayMap() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (i == entryX && j == entryY)
                    cout << "E"; // Entry point
                else if (i == exitX && j == exitY)
                    cout << "X"; // Exit point
                else if (grid[i][j])
                    grid[i][j]->display(); // Display the cell content (either 'S' or 'P')
                else
                    cout << "."; // Default empty cell
            }
            cout << "\n";
        }
    }

    // Method to check if the map is valid
    bool isValidMap()
    {
        // Ensure exactly one entry and one exit exist
        if (entryX == -1 || exitX == -1)
        {
            return false;
        }

        // Create a 2D visited vector initialized to false
        vector<vector<bool> > visited(rows, vector<bool>(cols, false));

        // Call the modified path-checking function
        return isPathConnected(entryX, entryY, visited);
    }

    // Destructor to clean up dynamically allocated memory
    ~gameMap()
    {
        for (auto &row : grid)
        {
            for (auto &cell : row)
            {
                delete cell; // Deallocate each Cell object
                cell = nullptr;
            }
        }
    }

private:
    // Helper method to check if there's a valid path between entry and exit
    bool isPathConnected(int x, int y, vector<vector<bool> > &visited)
    {
        // If we reach the exit point, return true
        if (x == exitX && y == exitY)
        {
            return true;
        }

        // Mark the current cell as visited
        if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y] || grid[x][y]->getCellType() != PATH)
        {
            return false; // Out of bounds or not a path cell
        }

        // Mark current cell as visited
        visited[x][y] = true;

        // Directions: right, left, down, up
        bool found = isPathConnected(x + 1, y, visited) || isPathConnected(x - 1, y, visited) ||
                     isPathConnected(x, y + 1, visited) || isPathConnected(x, y - 1, visited);

        return found;
    }
};