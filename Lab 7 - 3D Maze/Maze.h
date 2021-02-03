#ifndef MAZE_H
#define MAZE_H
#include <stdio.h>
#include <sstream>
#include "MazeInterface.h"

class Maze : public MazeInterface {
private:
    int width, height, layers;
    char ***maze;
    
public:
    /** Initialize Maze */
    Maze(int height, int width, int layers);
    
    /** Free memory from allocation of maze */
    ~Maze();
    
    /** Set maze value */
    virtual void setValue(int height, int width, int layer, int value) {
        if (!value) maze[height][width][layer] = '_';
        else maze[height][width][layer] = 'X';
    }
    
    /** Solve maze, @return true if solveable, else false */
    virtual bool find_maze_path();
    
    /** Actual maze solver, called from wrapper above */
    bool find_maze_path(int h, int w, int l);
    
    /** Output maze (same order as input maze), @return string of 2D layers */
    virtual std::string toString() const;
};

#endif
