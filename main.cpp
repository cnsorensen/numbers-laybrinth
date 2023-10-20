#include <stdio.h>
#include <stdlib.h>
#include <cmath>

signed int maze[5][5] = {
{2, -2, 4, -1, 3},
{-3, 3, -1, 3, -2},
{1, -2, 0, -2, 3},
{-3, 2, -3, 2, -4},
{4, -2, 1, -3, 2}
};

int touched[5][5] = {
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}
};

int startx = 4;
int starty = 2;
int endx = 2;
int endy = 2;

const int NUMROWS = 5;
const int NUMCOLS = 5;

int count;
int sum;

void PrintGrid(int maze[NUMROWS][NUMCOLS])
{
  printf("\n");
  for(int i = 0; i < NUMROWS; i++)
  {
    for(int j = 0; j < NUMCOLS; j++)
    {
      if(maze[i][j] < 0)
      {
        printf("%d ", maze[i][j]);
      }
      else if(maze[i][j] < 10)
      {
        printf(" %d  ", maze[i][j]);
      }
      else
      {
        printf(" %d ", maze[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

int FindPath(int x, int y)
{
  int steps;

  // Return if we're looking at a tile that's already been stepped on.
  if(touched[x][y] == 1)
  {
    return 2;
  }

  count++;
  touched[x][y] = count;
  sum += maze[x][y];

  // We've hit where the maze starts, we're done! 
  if((x == startx) && (y == starty))
  {
    printf("YOU FOUND THE PATH!!\n");
    printf("Number of steps = %d\n", count);
    printf("Sum of tiles = %d\n", sum);

    PrintGrid(touched);

    exit(0);
  }

  // Right
  steps = 1;
  for(int i = x + 1; i < NUMCOLS; i++)
  {
    if(touched[i][y] == 0)
    {
      if(std::abs(maze[i][y]) == steps)
      {
        FindPath(i, y);
      }
    }
    steps++;
  }

  // Up
  steps = 1;
  for(int i = y - 1; i >= 0; i--)
  {
    if(touched[x][i] == 0)
    {
      if(std::abs(maze[x][i]) == steps)
      {
        FindPath(x, i);
      }    
    }
    steps++;
  }

  // Down
  steps = 1;
  for(int i = y + 1; i < NUMROWS; i++)
  {
    if(touched[x][i] == 0)
    {
      if(std::abs(maze[x][i]) == steps)
      {
        FindPath(x, i);
      }
    }
    steps++;
  }

  // Left
  steps = 1;
  for(int i = x - 1; i >= 0; i--)
  {
    if(touched[i][y] == 0)
    {
      if(std::abs(maze[i][y]) == steps)
      {
        FindPath(i, y);
      }
    }
    steps++;
  }

  // If this tile didn't have any other options, reset the tile properties.
  touched[x][y] = 0;
  count--;
  sum -= maze[x][y];

  return 0;
}

int main(int argc, char* argv[])
{
  count = 0; 
  sum = 0;

  PrintGrid(maze);

  (void)FindPath(endx, endy);

  return 0;
}

