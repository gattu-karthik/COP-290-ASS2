#include "texture.h"

Texture::Texture(){
    mTexture=NULL;
    mHeight=0;
    mWidth=0;
}

Texture::~Texture(){
    free();

}

int Texture::getHeight(){
    return mHeight;
}

int Texture::getWidth(){
    return mWidth;
}

bool Texture::loadfromfile(SDL_Renderer* renderer,string path){
    free();
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loaded=IMG_Load(path.c_str());
    if(loaded==NULL){
        printf("Unable to load image %s! SDL_Image Error",path.c_str(),IMG_GetError());
    }
    else{
        SDL_SetColorKey(loaded, SDL_TRUE, SDL_MapRGB(loaded->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loaded);
		if(newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			mWidth = loaded->w;
			mHeight = loaded->h;
		}

		SDL_FreeSurface(loaded);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}




bool Texture::loadrenderedtext(SDL_Renderer* renderer,string text,SDL_Color textcolour){
    free();
    mfont=TTF_OpenFont("../Resources/fonts/lazyfont.ttf",30);       
    if(mfont==NULL){
        printf("Unable to render text surface! SDL_ttf Error:%s\n",TTF_GetError());
    }

    else{
        SDL_Surface* textSurface = TTF_RenderText_Solid(mfont, text.c_str(), textcolour);
        if(textSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        } else {
            mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if(mTexture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            } else {
                mWidth = textSurface->w;
                mHeight = textSurface->h;
            }

            SDL_FreeSurface(textSurface);
        }
        
        return mTexture != NULL;

    }


}



void Texture::free(){

    if(mTexture!=NULL){
        mTexture=NULL;
        mHeight=0;
        mWidth=0;

    }

}

void Texture::setColor(Uint8 red,Uint8 blue,Uint8 green){
    SDL_SetTextureColorMod(mTexture,red,green,blue);

}

void Texture::setBlendmode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(mTexture,blending);

}

void Texture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(mTexture,alpha);

}


void Texture::render(SDL_Renderer* renderer,int x,int y,SDL_Rect* clip,double angle,SDL_Point* center,SDL_RendererFlip flip){
    SDL_Rect renderquad={x,y,mWidth,mHeight};
    if(clip!=NULL){
        renderquad.w=mWidth;
        renderquad.h=mHeight;
    }
    SDL_RenderCopyEx(renderer,mTexture,clip,&renderquad,angle,center,flip);
}


void Texture::render(SDL_Renderer* renderer,SDL_Rect* rec){
    SDL_RenderCopy(renderer,mTexture,NULL,rec);
}
     