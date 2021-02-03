#include <iostream>
#include <fstream>
#include <sstream>
#include "Maze.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // Open Files
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in)  {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    ofstream out(argv[2]);
    
    // Read Maze
    out << "Solve Maze:" << endl;
    Maze *maze = nullptr;
    
    int layer = 0, currentHeight = 0, height, width, depth;
    for (string line; getline(in, line);) {
        if (line.size() <= 1) {
            // Empty line, must be a divider between layers
            ++layer;
            currentHeight = 0;
            out << "Layer " << layer << endl;
            continue;
        }
        else if (!layer) {
            // First line, setup maze
            istringstream read(line);
            read >> height;
            read >> width;
            read >> depth;
            maze = new Maze(height, width, depth);
        }
        else {
            // Read data into maze
            istringstream read(line);
            for (int i, currentWidth = 0; read >> i; ++currentWidth) {
                if (!i) out << "_ ";
                else out << "X ";
                maze -> setValue(currentHeight, currentWidth, layer - 1, i);
            }
            out << endl;
        }
        ++currentHeight;
    }
    // Solve Maze
    bool solvable = maze -> find_maze_path();
    if (!solvable) out << endl << "No Solution Exists!" << endl;
    else out << endl << "Solution:" << endl << maze -> toString();

    delete maze;
    
    return 0;
}
