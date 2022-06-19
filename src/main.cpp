#include "main.h"


SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;

Texture Home_Screen;
Texture Game_Started;
Texture Game_Over;
Texture Jerry_Winning_Texture;
Texture Tom_Winning_Texture;
Texture Cheese_Texture;
Texture Pizza_Texture;
Texture Time_Texture;
Texture Score_Texture;
Texture Wall_Texture;
Texture Jerry_Texture;
Texture Tom_Texture;


bool init(){
    bool ans=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
       printf("Video cannot be initialized:%s\n", SDL_GetError());
       ans=false;
    }
    else{
		if(TTF_Init()==-1){
			printf("Font cannot be loaded! SDL_TTF Error: %s\n", TTF_GetError());
			ans = false;

		}
        gWindow = SDL_CreateWindow("CAT-CHASE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480,600,SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			ans = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				ans = false;
			} else {
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				
			}
		}
    }
    return ans;
    
}


bool loadmedia(){
	bool success=true;
	if(!Wall_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
		success=false;
	}
	else{
		if(!Home_Screen.loadfromfile(gRenderer,"../Resources/images/wallpaper.png")){
			printf("Failed to load Jerry_Texture %s\n");
			success=false;

		}
		if(!Jerry_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Jerry_Texture %s\n");
			success=false;

		}
		if(!Tom_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Tom_Texture %s\n");
			success=false;

		}
		if(!Cheese_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Cheese_Texture %s\n");
			success=false;

		}
		if(!Pizza_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Pizza_Texture %s\n");
			success=false;

		}
		if(!Jerry_Winning_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Winning_Texture %s\n");
			success=false;

		}
		if(!Tom_Winning_Texture.loadfromfile(gRenderer,"../Resources/images/wall.png")){
			printf("Failed to load Winning_Texture %s\n");
			success=false;

		}
		SDL_Color TextColor={255,0,0};
		if(!Game_Started.loadrenderedtext(gRenderer,"GAME STARTS NOW!!",TextColor)){
			printf("Failed to load Winning_Texture %s\n");
			success=false;

		}
		if(!Game_Over.loadrenderedtext(gRenderer,"GAME OVER",TextColor)){
			printf("Failed to load Winning_Texture %s\n");
			success=false;

		}


		

	}
	return success;
	
}


void close(){
	Jerry_Winning_Texture.free();
	Tom_Winning_Texture.free();
	Cheese_Texture.free();
 	Pizza_Texture.free();
	Time_Texture.free();
	Score_Texture.free();
	Wall_Texture.free();
	Jerry_Texture.free();
	Tom_Texture.free();
	Home_Screen.free();
    SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	Mix_Quit();
}

int main(int argc,char* args[]){
    if(!init()){
        cout<<"Couldn't Load Media"<<"\n";
    }
    else{
		Maze game_maze=Maze();
		if(loadmedia()){			
			SDL_Event e;
			bool quit=false;
			while(!quit){
				while(SDL_PollEvent (&e)){
				if(e.type==SDL_QUIT){
					quit=true;
					}
				}


            SDL_RenderClear( gRenderer );
			SDL_RenderCopy(gRenderer,Wall_Texture.mTexture,NULL,NULL);
			game_maze.generate();
			game_maze.renderr(gRenderer,Wall_Texture);			
			SDL_RenderPresent(gRenderer);

			}
		  


		}
		
	
    }
	close();
	
	

}
   



