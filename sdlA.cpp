#include<SDL2/SDL.h>
#include<stdio.h>
#include<bits/stdc++.h> 
// using namespace std; 

#define windowSizeX 800
#define windowSizeY 800

// #define distanceBetweenCells 2

// // <x, y>
typedef std::pair<int, int> Coordinates;
// // <f, <x, y>>
// // f = g + h
// // g(Point) = distance(start, Point)
// // h(Point) = expected distance (Point, end)
// typedef std::pair<double, std::pair<int, int>> fPoint; 

struct Point {
  Point() : x(-1), y(-1), 
  f(FLT_MAX), g(FLT_MAX), h(FLT_MAX), 
  parentX(-1), parentY(-1), status(0) {}
  
  int x, y;
  // f = g + h
  // g(Point) = distance(start, Point)
  // h(Point) = expected distance (Point, end)
  double f, g, h;
  int parentX, parentY;
  // 0 = empty space
  // 1 = wall
  // 2 = open
  // 3 = start
  // 4 = end
  int status;
};

bool isPointInsideGrid(int x, int y, int fieldX, int fieldY){
  return (x >= 0) && (x < fieldX) && (y >= 0) && (y < fieldY);
}

// bool isPointInsideGrid(std::pair<int, int> p){
//   return (p.first >= 0) && (p.first < fieldX) && (p.second >= 0) && (p.second < fieldY);
// }

bool isPointInsideGrid(Point p, int fieldX, int fieldY){
  return (p.x >= 0) && (p.x < fieldX) && (p.y >= 0) && (p.y < fieldY);
}

bool isPointNotBlocked(int **grid, int x, int y){
  return (grid[x][y] == 0);
}

bool isPointDestination(){}

int aStarSearchNextMove(Point **grid, Point destination, std::vector<Coordinates> openList, int fieldX, int fieldY){

  if(openList.size() == 0 ){
    return 1;
  }

  //Get Point from openList with lowest f param.
  Coordinates pointWithLowestF = openList[0];
  int n = 0;
  for(int i=1; i<openList.size(); i++){
    if(grid[openList[i].first][openList[i].second].f < grid[pointWithLowestF.first][pointWithLowestF.second].f){
      pointWithLowestF = openList[i];
      n = i;
    }
  }
  
  //Remove this point from openList
  openList.erase(openList.begin() + n);






  if(!isPointInsideGrid(grid[x][y], fieldX, fieldY)){
    printf("ERR: Point is outside field!");
    return;
  }



}

double getHParam(int x, int y, Point p){
  return ((double)sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)));
}

int countCharQuantity(std::string s, char c){
  char * charstring = new char [s.length()+1];
  strcpy(charstring, s.c_str());

  int quantity = 0;
  for(int i=0;i<s.length();i++){
    if(charstring[i] == c){
      quantity++;
    }
  }
  return quantity;
}

int char2int(char c){
  return(c-'0');
}

void LineToIntArray(std::string s, int* array){
  char * charstring = new char [s.length()+1];
  strcpy(charstring, s.c_str());
  int arrayIterator = 0;
  int tempValu = 0;
  for(int i=0;i<s.length();i++){
    if(charstring[i]>='0' && charstring[i]<='9'){
      tempValu=tempValu*10+char2int(charstring[i]);
    }
    if(charstring[i]==','){
      array[arrayIterator++]=tempValu;
      tempValu=0;
    }
  }
  array[arrayIterator]=tempValu;
}

int CSVErrorFormat(){
  printf("Wrong format of file!\n"
    "X,Y size of board\n"
    "X,Y coordinates of start\n"
    "X,Y coordinates of end\n"
    "X rows x Y lines coma separated numbers:\n"
    "0: Free space\n"
    "1: Wall\n");
  return 1;
}

int CSVErrorGridSize(){
  printf("Grid size should be {2,2}<={x,y}<={400,400}.\n");
  return 1;
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    printf("Usage: %s filename.csv\n",argv[0]);
    return 1;
  }

  std::string line;
  std::ifstream file (argv[1]);

  if (! file.is_open()){
    printf("File is not exist!\nUsage: %s filename.csv\n",argv[0]);
    return 1;
  }

  //Get X,Y board size
  if (! file.good()){
    printf("File is empty!\nUsage: %s filename.csv\n",argv[0]);
    return 1;
  }
  getline (file,line);
  int comas = countCharQuantity(line,',');
  //For first line we should get x,y pair
  if(comas != 1){
    return CSVErrorFormat();
  }
  int *table = new int[comas+1];
  LineToIntArray(line,table);
  if(table[0] < 2 || table[0] > 400 || table[1]<2 || table[1]>400){
    return CSVErrorGridSize();
  }
  int fieldX = table[0];
  int fieldY = table[1];

  //Get X,Y start point
  if (! file.good()){
    return CSVErrorFormat();
  }
  getline (file,line);
  comas = countCharQuantity(line,',');
  //For second line we should get x,y pair
  if(comas != 1){
    return CSVErrorFormat();
  }
  LineToIntArray(line,table);
  Point startPoint;
  startPoint.x = table[0];
  startPoint.y = table[1];

  //Get X,Y end point
  if (! file.good()){
    return CSVErrorFormat();
  }
  getline (file,line);
  comas = countCharQuantity(line,',');
  //For first line we should get x,y pair
  if(comas != 1){
    return CSVErrorFormat();
  }
  LineToIntArray(line,table);
  Point endPoint;
  endPoint.x = table[0];
  endPoint.y = table[1];

  Point grid[fieldX][fieldY];

  // delete[] table;
  // int table[fieldY];
  table = new int[fieldY];
  for(int x = 0; x < fieldX; x++){
    if (! file.good()){
      return CSVErrorFormat();
    }
    getline (file,line);
    comas = countCharQuantity(line,',');
    //For first line we should get x,y pair
    if(comas != fieldY - 1){
      return CSVErrorFormat();
    }
    LineToIntArray(line,table);
    for(int y = 0; y < fieldY; y++){
      if(table[y] == 1 || table[y] == 0){
        grid[x][y].status = table[y];
      }
      else{
        return CSVErrorFormat();
      }
    }
  }

  //Start point to grid
  grid[startPoint.x][startPoint.y].status = 3;
  //End point to grid
  grid[endPoint.x][endPoint.y].status = 4;

  //Raport
  printf("B: %d x %d\n",fieldX,fieldY);
  printf("S: %d x %d\n",startPoint.x,startPoint.y);
  printf("E: %d x %d\n",endPoint.x,endPoint.y);
  for(int x = 0; x < fieldX; x++){
    for(int y = 0; y < fieldY; y++){
      printf("%d ",grid[x][y].status);
    }
    printf("\n");
  }

  file.close();

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
    int distanceBetweenCells = windowSizeX / (fieldX * 10);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect Rect[fieldX][fieldY];
    const int fieldWidth = (windowSizeX-(distanceBetweenCells*(fieldX+1)))/fieldX;
    const int fieldHeight = (windowSizeY-(distanceBetweenCells*(fieldY+1)))/fieldY;
    int marginX = (windowSizeX - ((distanceBetweenCells*(fieldX+1))+(fieldX*fieldWidth)))/2;
    int marginY = (windowSizeY - ((distanceBetweenCells*(fieldY+1))+(fieldY*fieldHeight)))/2;

    // printf("marginX: %d\n",marginX);
    // printf("marginY: %d\n",marginY);

    // printf("fieldWidth: %d, fieldHeight: %d\n",fieldWidth,fieldHeight);
    int sx,sy;
    for(int x = 0; x < fieldX; x++){
      for(int y = 0; y < fieldY; y++){
        sx = marginX + (distanceBetweenCells*(x+1))+(x*fieldWidth);
        sy = marginY + (distanceBetweenCells*(y+1))+(y*fieldHeight);
        // printf("%d x %d {%d, %d, %d, %d}\n",x,y,sx,sy,fieldWidth,fieldHeight);
        Rect[x][y] = {sx, sy, fieldWidth, fieldHeight};
      }
    }

    std::vector<Coordinates> openList; 

    do{
      printf("DO %d!\n",++iteration);
      SDL_SetRenderDrawColor(renderer,20,30,55,255);
      SDL_RenderClear(renderer);

      for(int x = 0; x < fieldX; x++){
        for(int y = 0; y < fieldY; y++){
          switch(grid[x][y].status){
            case 0: SDL_SetRenderDrawColor(renderer,255,255,255,255); break;
            case 1: SDL_SetRenderDrawColor(renderer,0,0,0,255); break;
            case 2: SDL_SetRenderDrawColor(renderer,255,255,0,255); break;
            case 3: SDL_SetRenderDrawColor(renderer,0,255,0,255); break;
            case 4: SDL_SetRenderDrawColor(renderer,0,0,255,255); break;
          }
          SDL_RenderFillRect(renderer,&Rect[x][y]);
        }
      }

      SDL_RenderPresent(renderer);

      aStarSearchNextMove();

      SDL_Delay(1000);
      if(iteration >= 1)
        end = true;
    }while(!end); 

    SDL_DestroyRenderer(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
