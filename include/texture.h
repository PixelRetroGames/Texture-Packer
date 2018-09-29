#ifndef TEXTURE_H
#define TEXTURE_H

#include "library.h"

struct Rect
{
 int x,y,w,h;
};

#ifdef TP_SDL_USED
struct Texture
{
 public:
 int w,h;
 SDL_Texture *image=NULL;
};

Texture *Load_Texture(char *filename);
Texture *Create_Transparent_Texture(int w,int h);

void Apply_Texture(Rect src_rect,Texture *src,Rect dest_rect,Texture *dest);

void Destroy_Texture(Texture *_texture);

extern Texture *SCREEN;
void Create_Screen_Texture(int RESOLUTION_W,int RESOLUTION_H);

void Flip_Buffers(Texture *screen);

#elif defined TP_SFML_USED



#endif // TP_SDL_USED

#endif // TEXTURE_H
