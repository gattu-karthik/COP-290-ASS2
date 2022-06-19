#ifndef MAIN_H
#define MAIN_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
#include <string>
#include <stack>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define SPACEX 6
#define SPACEY 6
#define GAP 10

#define WALL_THICKNESS 10

#define MAZEX 30
#define MAZEY 30

#define Y_GAP 20




const int SCREEN_WIDTH = 2*SPACEX + MAZEX*GAP;
const int SCREEN_HEIGHT = 2*SPACEY + MAZEY*GAP + 2*GAP;


#include "maze.h"
#include "player.h"
#include "texture.h"




#endif
