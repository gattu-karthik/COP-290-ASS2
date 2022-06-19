#ifndef MAZE_H
#define MAZE_H

#include "main.h"
using namespace std;


struct Cell{
    bool in=false;
    bool up=false;
    bool left=false;
    int prev_x=-1;
    int prev_y=-1;
    int content=0;
};

class Texture;

class Maze{


public:
    Cell MAZE[MAZEX][MAZEY];
    Maze();
    void createMaze();
    void setHeight(int h);
    void setWidth(int w);
    int getHeight();
    int getWidth();
    void generate();
    void render(SDL_Renderer* renderer,Uint8 opacity);
    void renderr(SDL_Renderer* renderer,Texture txt);
    void initializeMaze();
   
    


private:
    int Height;
    int Width;
    int dirgenerator(int x,int y,int z); //z is the number of neighbours 
    const int prime=98927;
    const int A=17;
    const int H=37;
    const int B=97;           //function is ((Ax^2+By^2+2HXY*rand_number) mod prime)mod z    
};

#endif