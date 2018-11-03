#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
  int windowSizeX = 1000;
  int windowSizeY = 1000;

  int fieldX = 10;
  int fieldY = 10;

  bool end = false;
  int iteration = 0;

  SDL_Window *window;

  //Init the video driver
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL_Error: %s\n", SDL_GetError());
  }
  else{
    window = SDL_CreateWindow("A*",SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      windowSizeX,windowSizeY,
      SDL_WINDOW_SHOWN);
  }
  if (window == NULL)
  {
      printf("SDL_Error: %s\n", SDL_GetError());
  }
  else{
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, 0);

    //array initialization
    int array[fieldX][fieldY];
    for(int x = 0; x < fieldX; x++){
      for(int y = 0; y < fieldY; y++){
        array[x][y] = 0;
      }
    }

    do{
      printf("DO %d!\n",++iteration);
      SDL_SetRenderDrawColor(renderer,0,0,0,255);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer,255,255,255,255);
      for(int x = 1; x < fieldX; x++){
        for(int y = 1; y < fieldY; y++){
          // printf("X:%d Y:%d fieldX:%d %d %d %d %d\n",x,y,fieldX,x*windowSizeX/fieldX,0,0,0);
          SDL_RenderDrawLine(renderer,x*windowSizeX/fieldX,0,x*windowSizeX/fieldX,windowSizeY);
          SDL_RenderDrawLine(renderer,0,y*windowSizeY/fieldY,windowSizeX,y*windowSizeY/fieldY);
        }
      }
      // SDL_RenderDrawLine();

      //SDL_Rect Rect = {0,0,10,20};
      //SDL_RenderFillRect(renderer,&Rect);

      SDL_RenderPresent(renderer);

      SDL_Delay(1000);
      if(iteration >= 5)
        end = true;
    }while(!end); 
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
