#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
using namespace std;

enum Direction{
    UP,RIGHT,DOWN,LEFT
};

class Maze;
class Texture;


class Player{


public:
    Player(int id,string name);
    int id;                  //0-TOM 1-JERRY
    int score;
    string name;    
    int get_r();
    int get_c();
    void set_r(int x1);
    void set_c(int y1);
    void set_dir(Direction dir);
    int nxt_r();
    int nxt_c();
    Direction getDir();


private:
    Direction direct;
    int r;
    int c;

};

#endif