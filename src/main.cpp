#include "texture.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>

int main( int argc, char *args[] )
{
 ///Random
 srand((unsigned int)(time(NULL)));
 ///Random

 Open_Window_and_Renderer(1,1,0);
 Create_Screen_Texture(1,1);

 //static_screen=screen;

 return 0;
}
