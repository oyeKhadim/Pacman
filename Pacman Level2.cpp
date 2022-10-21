#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;

// Global Variable
char maze[24][71];
int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 31; // Y Coordinate of Pacman
int score = 0;

int ghostX = 19;  // X Coordinate of Ghost
int ghostY = 25;  // Y Coordinate of Ghost
char previousItem = ' ';
int px=19,py=25;
int movecount=0;
//ProtoTypes
void loadMaze();
void printMaze();
void printScore();
void calculateScore();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
void gameOver();
int ghostDirection();
bool ghostMovement();
bool finished();
bool position();
// Main Function
main()
{
    loadMaze();
    bool gameRunning = true;
    while (gameRunning)
    {
        system("CLS");
        printMaze();
        Sleep(200);
       gameRunning = ghostMovement();
        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft(); // Function call to move Pacman towards left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight(); // Function call to move Pacman towards right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp(); // Function call to move Pacman towards up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown(); // Function call to move Pacman towards down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
       
     }
     gameOver();
     
}
void loadMaze(){
    fstream file;
    string line;
   
    file.open("maze.txt",ios::in);
       for (int row = 0; row < 24; row = row + 1)

    {
    getline(file,line);
    
        for (int col = 0; col < 71; col = col + 1)
        {
             maze[row][col]=line[col];
        }
        
    }
    file.close();
}
void printMaze(){
    
    for (int row = 0; row < 24; row = row + 1)
    {
        for (int col = 0; col < 71; col = col + 1)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}
void printScore()
{
    cout << endl << "Score: " << score << endl;
    if(finished()){

        cout<<"Level Completed."<<endl;
        exit(0);
    }
}
void calculateScore()
{
    score = score + 1;
}
void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] == '.')
    {
                if (maze[pacmanX][pacmanY - 1] == 'G')
    {
        gameOver();
       
    }   
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
   
}

void movePacmanRight()
{ if (maze[pacmanX][pacmanY - 1] == 'G')
    {
        gameOver();
       
    }
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
     if (maze[pacmanX][pacmanY + 1] == 'G')
    {
        gameOver();
       
    }
}

void movePacmanUp()
{ if (maze[pacmanX][pacmanY - 1] == 'G')
    {
        gameOver();
       
    }
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
     if (maze[pacmanX-1][pacmanY ] == 'G')
    {
        gameOver();
       
    }
}

void movePacmanDown()
{ if (maze[pacmanX][pacmanY - 1] == 'G')
    {
        gameOver();
       
    }
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
        calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
    }
      if (maze[pacmanX+1][pacmanY ] == 'G')
    {
        gameOver();
       
    }
}
void gameOver(){
      system("cls");
    printMaze();
    printScore();
        cout<<"Game Over."<<endl;
       
        exit(0);
}
int ghostDirection()
{
 int result;
   if(position()){
      srand(time(0));
    int result = 1 + (rand() % 4);
    return result;}
    int x,y;
    int nx,ny;
    x=pacmanX-ghostX;
    y=pacmanY-ghostY;
    nx=x;
    ny=y;
    if(x<0){
        nx=-x;
    }
    if(y<0){
        ny=-y;
    }
  
    if(nx>=ny){
        if(x>=0){
            return 4;
        }
        else{
            return 3;
        }
    }
    if(nx<ny){
        
        if(y>=0){
            return 2;
        }
        else{
            return 1;
        }
    }
  
    
      srand(time(0));
     result = 1 + (rand() % 4);
    return result;
}
bool ghostMovement()
{
    px=ghostX;
    py=ghostY;
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == '.' ||maze[ghostX][ghostY - 1] == '%' ||maze[ghostX][ghostY - 1] == '|' || maze[ghostX][ghostY - 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            ghostY = ghostY - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
        }
    }
    if (value == 2)
    {
        if (maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == 'P'||maze[ghostX][ghostY + 1] == '%' ||maze[ghostX][ghostY + 1] == '|' )
        {
            maze[ghostX][ghostY] = previousItem;
            ghostY = ghostY + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
        }
    }
    if (value == 3)
    {
        if (maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == 'P'||maze[ghostX - 1][ghostY] == '%' ||maze[ghostX - 1][ghostY] == '|' )
        {
            maze[ghostX][ghostY] = previousItem;
            ghostX = ghostX - 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
        }
    }
    if (value == 4)
    {
        if (maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == '.'||maze[ghostX + 1][ghostY] == '%' ||maze[ghostX + 1][ghostY] == '|' )
        {
            maze[ghostX][ghostY] = previousItem;
            ghostX = ghostX + 1;
            previousItem = maze[ghostX][ghostY];
            if (previousItem == 'P')
            {
                return 0;
            }
            maze[ghostX][ghostY] = 'G';
        }
    }
    return 1;
}

bool finished(){
      for (int row = 0; row < 24; row = row + 1)
    {
        for (int col = 0; col < 71; col = col + 1)
        {
            if(maze[row][col]=='.'){
                return 0;
            }
        }
      
    }
    return 1;
}
bool position(){
    if(px==ghostX && py==ghostY && movecount==4){
        movecount=0;
     //  return 1;
    }
    movecount++;
    return 0;
}