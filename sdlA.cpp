#include <SDL2/SDL.h>
#include <stdio.h>

#define windowSizeX 1000
#define windowSizeY 1000

#define fieldX 10
#define fieldY 10

#define distanceBetweenCells 3

bool isPointInsideGrid(int x, int y){
  return (x >= 0) && (x < fieldX) && (y >= 0) && (y < fieldY);
}

bool isPointNotBlocked(grid[fieldX][fieldY], int x, int y){
  return (grid[x][y] == 0);
}



int main()
{
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
    int grid[fieldX][fieldY];
    for(int x = 0; x < fieldX; x++){
      for(int y = 0; y < fieldY; y++){
        grid[x][y] = 0;
      }
    }

    do{
      printf("DO %d!\n",++iteration);
      SDL_SetRenderDrawColor(renderer,20,30,55,255);
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

    SDL_DestroyRenderer(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
