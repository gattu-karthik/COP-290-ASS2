#include "main.h"
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Maze::Maze(){
    setHeight(MAZEX);
    setWidth(MAZEY);
    initializeMaze();
    
}

void Maze::setHeight(int h){
    this->Height=h;
}

void Maze::setWidth(int w){
    this->Width=w;
}

void Maze::initializeMaze(){
    for(int i=0;i<MAZEX;i++){
        for(int j=0;j<MAZEY;j++){
            if(i==0 || j==0 || i==MAZEX-1 || j==MAZEY-1){
                MAZE[i][j].in=true;
            }
            MAZE[i][j].up   = (i==0||i==MAZEX-1||j==0)?0:1;
			MAZE[i][j].left = (i==0||j==0||j==MAZEY-1)?0:1;
                    
        }
       
    }
    
}

int Maze::getWidth(){
   return this->Width;
}

int Maze::getHeight(){
    return this->Height;
}


int Maze::dirgenerator(int x,int y,int z){
    int aux=rand();
    int l=(A*x*x+B*y*y+2*H*x*y*aux)%prime;
    int dir=l%z;
    return dir;   
}


void Maze::generate(){
    long numin=1;
	int xcur=1, ycur=1;//start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
	MAZE[xcur][ycur].in = 1;
	int whichway;
	bool success;
	do{

		if( MAZE[xcur][ycur-1].in&&MAZE[xcur][ycur+1].in&&
			   MAZE[xcur-1][ycur].in&&MAZE[xcur+1][ycur].in ){
				   //If at a dead end, randomly destroy a wall to make it not a dead end!
			do{
				success=0;
				whichway=dirgenerator(xcur,ycur,4);
				switch(whichway){
				case UP:
					if(MAZE[xcur][ycur].up&&ycur!=1){
						success=1;
						MAZE[xcur][ycur].up=0;
					}
					break;
				case DOWN:
					if(MAZE[xcur][ycur+1].up&&ycur!=MAZEY-2){
						success=1;
						MAZE[xcur][ycur+1].up=0;
					}
					break;
				case LEFT:
					if(MAZE[xcur][ycur].left&&xcur!=1){
						success=1;
						MAZE[xcur][ycur].left=0;
					}
					break;
				case RIGHT:
					if(MAZE[xcur+1][ycur].left&&xcur!=MAZEX-2){
						success=1;
						MAZE[xcur+1][ycur].left=0;
					}
					break;
				}
			}while(!success);
		}

		while( MAZE[xcur][ycur-1].in&&MAZE[xcur][ycur+1].in&&
			   MAZE[xcur-1][ycur].in&&MAZE[xcur+1][ycur].in ){
				   //If all the neighbourhood cells are in, backtrack.
				int xcur2=MAZE[xcur][ycur].prev_x;
				ycur=MAZE[xcur][ycur].prev_y;
				xcur=xcur2;
		}

		do{
			//randomly find a cell that's in the maze
			xcur=rand()%(MAZEX-2)+1;
			ycur=rand()%(MAZEY-2)+1;
		}while(!MAZE[xcur][ycur].in ||
			MAZE[xcur][ycur-1].in&&MAZE[xcur][ycur+1].in&&
			MAZE[xcur-1][ycur].in&&MAZE[xcur+1][ycur].in);

		do{
			//Randomly grow the maze if possible.
			success=0;
			whichway=dirgenerator(xcur,ycur,4);
			switch(whichway){
			case UP:
				if(!MAZE[xcur][ycur-1].in){
					success=1;
					MAZE[xcur][ycur].up=0;
					MAZE[xcur][ycur-1].prev_x=xcur;
					MAZE[xcur][ycur-1].prev_y=ycur;
					ycur--;
				}
				break;
			case DOWN:
				if(!MAZE[xcur][ycur+1].in){
					success=1;
					MAZE[xcur][ycur+1].up=0;
					MAZE[xcur][ycur+1].prev_x=xcur;
					MAZE[xcur][ycur+1].prev_y=ycur;
					ycur++;
				}
				break;
			case LEFT:
				if(!MAZE[xcur-1][ycur].in){
					success=1;
					MAZE[xcur][ycur].left=0;
					MAZE[xcur-1][ycur].prev_x=xcur;
					MAZE[xcur-1][ycur].prev_y=ycur;
					xcur--;
				}
				break;
			case RIGHT:
				if(!MAZE[xcur+1][ycur].in){
					success=1;
					MAZE[xcur+1][ycur].left=0;
					MAZE[xcur+1][ycur].prev_x=xcur;
					MAZE[xcur+1][ycur].prev_y=ycur;
					xcur++;
				}
				break;
			}
		}while(!success);
		MAZE[xcur][ycur].in=1;
		numin++; //Every iteration of this loop, one maze cell is added to the maze.
	}while(numin<(MAZEX-2)*(MAZEY-2));

	return;
}




void Maze::render(SDL_Renderer* renderer,Uint8 opacity){
   for(int y = 1; y < MAZEX-1; y++) {
		for(int x = 1; x < MAZEX-1; x++) {
			cout<<MAZE[x][y].left<<" "<<MAZE[x][y].up<<" "<<x<<" "<<y<<"\n";
			SDL_SetRenderDrawColor(renderer, 0,0,205,opacity);
			SDL_Rect fillRect = {SPACEX + x*GAP, SPACEY + Y_GAP + y*GAP, GAP, GAP};
			SDL_RenderFillRect(renderer, &fillRect);
			if(MAZE[x][y].left==true) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);
				SDL_Rect fillRect = {SPACEX + x*GAP, SPACEY + Y_GAP + y*GAP, WALL_THICKNESS, GAP};
				SDL_RenderFillRect(renderer, &fillRect);
			}
			if(MAZE[x][y].up==true) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);
				SDL_Rect fillRect = {SPACEX + x*GAP, SPACEY + Y_GAP + y*GAP, GAP, WALL_THICKNESS};
				SDL_RenderFillRect(renderer, &fillRect);
			}
		}
	}
}




void Maze::renderr(SDL_Renderer* gRenderer,Texture txt){
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
	for(int i=0;i<MAZEX;i++){
		for(int j=0;j<MAZEY;j++){
			cout<<i<<" "<<j<<" "<<MAZE[i][j].left<<" "<<MAZE[i][j].up<<"\n";			
			if(MAZE[i][j].left==true){
				SDL_Rect fillRect = {j*SPACEX, i*SPACEY,SPACEX,SPACEY};
				txt.render(gRenderer,&fillRect);
			}
			if(MAZE[i][j].up==true){
				SDL_Rect fillRect = { j*SPACEX, i*SPACEY,SPACEX,SPACEY};
				txt.render(gRenderer,&fillRect);
			}
		}
	}
}








