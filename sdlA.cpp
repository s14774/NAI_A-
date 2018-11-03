#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
  int windowSizeX = 1000;
  int windowSizeY = 1000;

  int fieldX = 10;
  int fieldY = 10;

  SDL_Window *window;
  SDL_Renderer *renderer;

  window = SDL_CreateWindow("A*",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    windowSizeX,windowSizeY,
    SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);

  //array initialization
  int array[fieldX][fieldY];


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

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
