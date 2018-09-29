#include "texture.h"

#ifdef TP_SDL_USED

void Create_Screen_Texture(int RESOLUTION_W,int RESOLUTION_H)
{
 SCREEN=new Texture;
 SCREEN->w=1;
 SCREEN->h=1;
 SCREEN->image=NULL;

 if(SCREEN==NULL)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"Open_Window_and_Renderer failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"Open_Window_and_Renderer failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL video module failure",message,NULL);
     exit(-1);
    }
}

Texture *Load_Texture(char *filename)
{
 SDL_Surface *image_surface=load_image(filename);
 if(image_surface==NULL)
    return NULL;
 SDL_LockMutex(RENDERER_MUTEX);
 SDL_Texture *image_texture=SDL_CreateTextureFromSurface(RENDERER,image_surface);
 if(image_texture==NULL)
    {
     FILE *where=fopen("err/logs.txt","a");
     fprintf(where,"%s while loading %s \n",SDL_GetError(),filename);
     fclose(where);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"SDL_CreateTextureFromSurface failed : ");
     strcat(message,SDL_GetError());
     strcat(message," while loading ");
     strcat(message,filename);
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL video module failure",message,NULL);
     exit(-1);
    }
 SDL_UnlockMutex(RENDERER_MUTEX);

 Texture *texture;
 texture=new Texture;
 texture->w=image_surface->w;
 texture->h=image_surface->h;
 texture->image=image_texture;

 SDL_FreeSurface(image_surface);
 return texture;
}

Texture *Create_Transparent_Texture(int w,int h)
{
 Texture *_texture=NULL;
 _texture=new Texture;
 SDL_LockMutex(RENDERER_MUTEX);
 _texture->image=SDL_CreateTexture(RENDERER,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w,h);
 SDL_SetRenderTarget(RENDERER,_texture->image);
 SDL_SetRenderDrawBlendMode(RENDERER,SDL_BLENDMODE_BLEND);
 SDL_SetTextureBlendMode(_texture->image,SDL_BLENDMODE_BLEND);
 SDL_SetRenderDrawColor(RENDERER,0,0,0,0);
 SDL_RenderClear(RENDERER);
 SDL_SetRenderTarget(RENDERER,NULL);
 SDL_UnlockMutex(RENDERER_MUTEX);
 if(_texture->image==NULL)
    {
     FILE *where=fopen("err/logs.txt","a");
     fprintf(where,"%s\n",SDL_GetError());
     fclose(where);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"SDL_CreateTexture failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL video module failure",message,NULL);
     exit(-1);
    }
 _texture->w=w;
 _texture->h=h;
 return _texture;
}

void Apply_Texture(Rect src_rect,Texture *src,Rect dest_rect,Texture *dest)
{
 if(src==NULL || src->image==NULL)
    return;

 SDL_LockMutex(RENDERER_MUTEX);
 if(dest->image!=NULL)
    {
     SDL_SetRenderTarget(RENDERER,dest->image);
    }
 SDL_Rect _src_rect;
 _src_rect.x=src_rect.x,_src_rect.y=src_rect.y,_src_rect.h=src_rect.h,_src_rect.w=src_rect.w;
 SDL_Rect _dest_rect;
 _dest_rect.x=dest_rect.x,_dest_rect.y=dest_rect.y,_dest_rect.h=dest_rect.h,_dest_rect.w=dest_rect.w;
 SDL_RenderCopy(RENDERER,src->image,&_src_rect,&_dest_rect);
 if(dest->image!=NULL)
    {
     SDL_SetRenderTarget(RENDERER,NULL);
    }
 SDL_UnlockMutex(RENDERER_MUTEX);
}

void Destroy_Texture(Texture *_texture)
{
 if(_texture==NULL)
    return;
 if(_texture->image!=NULL)
    {
     SDL_LockMutex(RENDERER_MUTEX);
     SDL_DestroyTexture(_texture->image);
     SDL_UnlockMutex(RENDERER_MUTEX);
     _texture->image=NULL;
    }
 delete _texture;
 _texture=NULL;
}

Texture *SCREEN;

void Flip_Buffers(Texture *screen)
{
 if(screen!=SCREEN)
    return;
 SDL_LockMutex(RENDERER_MUTEX);
 SDL_RenderPresent(RENDERER);
 SDL_UnlockMutex(RENDERER_MUTEX);
}

#elif defined TP_SFML_USED

#endif
