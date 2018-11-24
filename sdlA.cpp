#include<SDL2/SDL.h>
#include<stdio.h>
#include<bits/stdc++.h> 
// using namespace std; 

#define windowSizeX 800
#define windowSizeY 800

// #define distanceBetweenCells 2

// <x, y>
typedef std::pair<int, int> Coordinates;

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
  // 5 = closed
  int status;
};

bool isPointInsideGrid(int x, int y, int fieldX, int fieldY){
  return (x >= 0) && (x < fieldX) && (y >= 0) && (y < fieldY);
}

bool isPointNotBlocked(std::vector<std::vector<Point>> &grid, int x, int y){
  return (grid[x][y].status == 0 || grid[x][y].status == 4);
}

void findFinalWayBack(std::vector<std::vector<Point>> &grid, Point parentPoint){
  printf("PP: %d,%d\n",parentPoint.parentX,parentPoint.parentY);
}

int aStarSearchNextMove(int fieldX, int fieldY, std::vector<std::vector<Point>> &grid, Point destination, std::vector<Coordinates> &openList, float hFactor){

  if(openList.size() == 0 ){
      printf("Way not found!\n");
    return -1;
  }

// //D
//   printf("openList: ");
//   for(int i=0; i<openList.size(); i++){
//     printf("%d,%d, ", openList[i].first, openList[i].second);
//   }  
//   printf("\n");
// //D

  //Get Point from openList with lowest f param.
  Coordinates pointCoordinatesWithLowestF = openList[0];
  int n = 0;
  for(int i=1; i<openList.size(); i++){
    if(grid[openList[i].first][openList[i].second].f < grid[pointCoordinatesWithLowestF.first][pointCoordinatesWithLowestF.second].f){
      pointCoordinatesWithLowestF = openList[i];
      n = i;
    }
  }  

  //Remove this point from openList
  openList.erase(openList.begin() + n);
  Point &pointWithLowestF = grid[pointCoordinatesWithLowestF.first][pointCoordinatesWithLowestF.second];
  pointWithLowestF.status = 5;

  printf("Trying: %d %d\n",pointWithLowestF.x, pointWithLowestF.y);
  for(int x = -1; x <= 1; x++){
    for(int y = -1; y <= 1; y++){
      if(x==0 && y==0){
        continue;
      }
      if(!isPointInsideGrid(pointWithLowestF.x + x, pointWithLowestF.y + y, fieldX, fieldY)){
        continue;
      }
      if(!isPointNotBlocked(grid, pointWithLowestF.x + x, pointWithLowestF.y + y)){
        continue;
      }
      Point &checkingPoint = grid[pointWithLowestF.x + x][pointWithLowestF.y + y];
      checkingPoint.x = pointWithLowestF.x + x;
      checkingPoint.y = pointWithLowestF.y + y;
      checkingPoint.parentX = pointWithLowestF.x;
      checkingPoint.parentY = pointWithLowestF.y;
      checkingPoint.g = pointWithLowestF.g + ((double)sqrt((x*x)+(y*y)));
      checkingPoint.h = ((double)sqrt((checkingPoint.x-destination.x)*(checkingPoint.x-destination.x)+(checkingPoint.y-destination.y)*(checkingPoint.y-destination.y)))*hFactor;
      checkingPoint.f = checkingPoint.g + checkingPoint.h;
      checkingPoint.status = 2;
      Coordinates checkingPointCoordinates;
      checkingPointCoordinates.first = checkingPoint.x;
      checkingPointCoordinates.second = checkingPoint.y;
      openList.push_back(checkingPointCoordinates);
      printf("PKT OK: %d x %d, G: %.1f, H: %.2f, F: %.1f\n",checkingPoint.x, checkingPoint.y, checkingPoint.g, checkingPoint.h, checkingPoint.f);
      if(checkingPoint.x == destination.x && checkingPoint.y == destination.y){
        printf("At destination!\n");
        destination = checkingPoint;
        return 1;
      }
    }
  }
  return 0;
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

int string2int(std::string s){
  char * charstring = new char [s.length()+1];
  strcpy(charstring, s.c_str());
  int tempValu = 0;
  bool negative = false;
  for(int i=0;i<s.length();i++){
    if(charstring[i]>='0' && charstring[i]<='9'){
      tempValu=tempValu*10+char2int(charstring[i]);
    }
    if(charstring[i]=='-'){
      negative = ! negative;
    }

  }
  if(negative){
    return -tempValu;
  }
  else{
    return tempValu;
  }
}

float string2float(std::string s){
  char * charstring = new char [s.length()+1];
  strcpy(charstring, s.c_str());
  float tempValu = 0;
  bool negative = false;
  int afterDot = 0;
  for(int i=0;i<s.length();i++){
    if(charstring[i]>='0' && charstring[i]<='9'){
      if(afterDot == 0){
        tempValu=tempValu*10+char2int(charstring[i]);
      }
      else{
        tempValu=tempValu+(char2int(charstring[i])*(1/pow(10,afterDot)));
        afterDot+=1;
      }
    }
    if(charstring[i]=='-'){
      negative = ! negative;
    }
    if(charstring[i]=='.' && afterDot == 0){
      afterDot = 1;
    }

  }
  if(negative){
    return -tempValu;
  }
  else{
    return tempValu;
  }
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

int ParamError(char *c){
  printf("Usage: %s filename.csv [WaitTime] [h param]\n",c);
  return 1;
}

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 4) {
    return ParamError(argv[0]);
  }

  int SDL_DelayTime;
  if(argc >= 3){
    SDL_DelayTime = string2int(argv[2]);
  }
  else{
    SDL_DelayTime = 50;
  }
  // printf("SDL_DelayTime: %d\n",SDL_DelayTime);

  float hFactor;
  if(argc >= 4){
    hFactor = string2float(argv[3]);
  }
  else{
    hFactor = 1;
  }
  std::string windowNameString = "A* H: " + std::to_string(hFactor);
  char * windowName = new char [windowNameString.length()+1];
  strcpy(windowName, windowNameString.c_str());

  std::string line;
  std::ifstream file (argv[1]);

  if (! file.is_open()){
    printf("File is not exist!\n");
    return ParamError(argv[0]);
  }

  //Get X,Y board size
  if (! file.good()){
    printf("File is empty!\n");
    return ParamError(argv[0]);
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

  // Point grid[fieldX][fieldY];
  std::vector<std::vector<Point>> grid(fieldY);
  for(int y = 0; y < fieldY; y++){
    grid[y] = std::vector<Point>(fieldX);
  }

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
  startPoint.f = 0;
  startPoint.g = 0;
  startPoint.h = 0;
  startPoint.status = 3;
  grid[startPoint.x][startPoint.y] = startPoint;
  //End point to grid
  grid[endPoint.x][endPoint.y] = endPoint;
  grid[endPoint.x][endPoint.y].status = 4;

  //Raport
  printf("H: %.2f\n",hFactor);
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
    window = SDL_CreateWindow(windowName,SDL_WINDOWPOS_UNDEFINED,
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
    Coordinates startPointCordinates;
    startPointCordinates.first = startPoint.x;
    startPointCordinates.second = startPoint.y;
    openList.push_back(startPointCordinates);
    bool atDestination = false;

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
            case 5: SDL_SetRenderDrawColor(renderer,50,120,120,255); break;
          }
          SDL_RenderFillRect(renderer,&Rect[x][y]);
        }
      }

      SDL_RenderPresent(renderer);
      int status = 0; // -1 error, 0 continue, 1 end;
      if(!atDestination){
        status = aStarSearchNextMove(fieldX, fieldY, grid, endPoint, openList, hFactor);
      }
      else{
        
      }

      SDL_Delay(SDL_DelayTime);
      switch(status){
        case -1: end = true; break;
        case 1: atDestination = true; end = true; break;
      }

      printf("STATUS: %d\n",status);

    }while(!end); 

    SDL_DestroyRenderer(renderer);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
