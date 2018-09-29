#include "library.h"

#ifdef TP_SDL_USED

SDL_Window *WINDOW;
SDL_Renderer *RENDERER;
SDL_mutex *RENDERER_MUTEX;
SDL_Surface *SCREEN_SURFACE;

void Init_Graphics()
{
 if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"SDL_Init() failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"SDL_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL failure",message,NULL);
     exit(-1);
    }
}

void Open_Window_and_Renderer(int RESOLUTION_W,int RESOLUTION_H,int DISPLAY_MODE)
{
 WINDOW=SDL_CreateWindow("Texture Packer",0,0,RESOLUTION_W,RESOLUTION_H,DISPLAY_MODE);
 SDL_SetWindowPosition(WINDOW,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
 RENDERER=SDL_CreateRenderer(WINDOW,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
 RENDERER_MUTEX=SDL_CreateMutex();
 SCREEN_SURFACE=SDL_GetWindowSurface(WINDOW);
 SDL_HideWindow(WINDOW);
}

void Close_Window_and_Renderer()
{
 SDL_DestroyWindow(WINDOW);
 WINDOW=NULL;
 SDL_DestroyRenderer(RENDERER);
 RENDERER=NULL;
 SDL_DestroyMutex(RENDERER_MUTEX);
 RENDERER_MUTEX=NULL;
}

SDL_Surface *load_image(std::string filename)
{
 SDL_Surface *loadedImage=NULL;
 loadedImage=IMG_Load(filename.c_str());
 if(loadedImage==NULL)
    return NULL;
 SDL_Surface *optimizedImage=SDL_ConvertSurface(loadedImage,SCREEN_SURFACE->format,NULL);
 SDL_FreeSurface(loadedImage);
 return optimizedImage;
}

#elif defined TP_SFML_USED

#endif
