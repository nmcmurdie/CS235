#include "Maze.h"

/** Initialize 3D maze array */
Maze::Maze(int height, int width, int layers) : width(width), height(height), layers(layers) {
    maze = new char**[height]();
    
    for (int i = 0; i < height; ++i) {
        maze[i] = new char*[width]();
        for (int j = 0; j < width; ++j) {
            maze[i][j] = new char[layers]();
        }
    }
}

/** Free memory from allocation of maze */
Maze::~Maze(void) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete[] maze[i][j];
        }
        delete[] maze[i];
    }
    delete[] maze;
}

/** Output maze (same order as input maze), @return string of 2D layers */
std::string Maze::toString() const {
    std::ostringstream out;
    for (int l = 0; l < layers; ++l) {
        out << "Layer " << (l + 1) << std::endl;
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                // Remove temporary values
                if (maze[h][w][l] == 'T') maze[h][w][l] = '_';
                out << maze[h][w][l] << " ";
            }
            out << std::endl;
        }
    }
    return out.str();
}

/** Solve maze, @return true if solveable, else false */
bool Maze::find_maze_path() {
    return find_maze_path(0, 0, 0);
}

/** Solve maze by recursively moving through available paths */
bool Maze::find_maze_path(int h, int w, int l) {
    // Check boundaries, if blocked, or if exit
    if (h < 0 || h >= height ||
        w < 0 || w >= width ||
        l < 0 || l >= layers) return false;
    else if (maze[h][w][l] != '_') return false;
    else if (h == height - 1 && w == width - 1 && l == layers - 1) {
        maze[h][w][l] = 'E';
        return true;
    }
    
    // Set path
    maze[h][w][l] = 'P';
    
    // Recurse surrounding cells
    if (find_maze_path(h, w - 1, l)) maze[h][w][l] = 'L';
    else if (find_maze_path(h, w + 1, l)) maze[h][w][l] = 'R';
    else if (find_maze_path(h - 1, w, l)) maze[h][w][l] = 'U';
    else if (find_maze_path(h + 1, w, l)) maze[h][w][l] = 'D';
    else if (find_maze_path(h, w, l - 1)) maze[h][w][l] = 'O';
    else if (find_maze_path(h, w, l + 1)) maze[h][w][l] = 'I';
    else {
        // Undo path
        maze[h][w][l] = 'T';
        return false;
    }
    return true;
}
