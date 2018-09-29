#ifndef LIBRARY_H
#define LIBRARY_H

#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>

#ifdef TP_SDL_USED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window *WINDOW;
extern SDL_Renderer *RENDERER;
extern SDL_mutex *RENDERER_MUTEX;
extern SDL_Surface *SCREEN_SURFACE;

void Init_Graphics();

void Open_Window_and_Renderer(int RESOLUTION_W,int RESOLUTION_H,int DISPLAY_MODE);
void Close_Window_and_Renderer();

SDL_Surface *load_image(std::string filename);

#elif defined TP_SFML_USED

#include <SFML/Graphics.hpp>

#endif



#define TEXT_LENGTH_MAX 101

#endif // LIBRARY_H
