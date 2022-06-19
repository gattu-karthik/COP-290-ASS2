#ifndef TEXT_H
#define TEXT_H

#include "main.h"
using namespace std;

class Texture{
    public:
      Texture();
     ~Texture();
      SDL_Texture *mTexture;     
      bool loadfromfile(SDL_Renderer* renderer,string path);
      bool loadrenderedtext(SDL_Renderer* renderer,string text,SDL_Color textcolour);
      void free();
      void setColor(Uint8 red,Uint8 blue,Uint8 green);
      void setBlendmode(SDL_BlendMode blending);
      void setAlpha(Uint8 alpha);
      void render(SDL_Renderer* renderer,int x,int y,SDL_Rect* clip,double angle,SDL_Point* Center,SDL_RendererFlip);
      void render(SDL_Renderer* renderer,SDL_Rect* rec);
      int getHeight();
      int getWidth();

    private:
        TTF_Font *mfont;
        //SDL_Texture *mTexture;
        int mHeight;
        int mWidth;
};

#endif