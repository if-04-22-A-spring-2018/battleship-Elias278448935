
#include <stdio.h>
#include "battleship.h"

static CellContent u_p_field[FIELDSIZE][FIELDSIZE];
static CellContent o_p_field[FIELDSIZE][FIELDSIZE];
static CellContent guess[FIELDSIZE][FIELDSIZE];

void load_game(){
  FILE* u_file = fopen("battleship.my","r");
  FILE* o_file = fopen("battleship.op","r");
  for(int i = 0; i < FIELDSIZE; i++)
  {
    for (int j = 0; j < FIELDSIZE; j++)
    {
        fread(&u_p_field[j][i],4,1,u_file);
        fread(&o_p_field[j][i],4,1,o_file);
        guess[j][i] = Unknown;
    }
  }
  fclose(u_file);
  fclose(o_file);
}

CellContent get_shot(int row, int col){
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)return OutOfRange;

  else   return u_p_field[col][row];

}


bool shoot(int row, int col)
{
 CellContent check = get_my_guess(row,col);
 if(check == OutOfRange)
 {
   return false;
 }
 if(o_p_field[col][row] == Boat || o_p_field[col][row] == Water)
 {
   guess[col][row] = o_p_field[col][row];

   if(guess[col][row] == Boat)
   {
     for (int i = -1; i < 2; i++)
     {
       for (int j = -1; j < 2; j++)
        {
         check = get_my_guess(row+j,col+i);
         if (check == Unknown) guess[col+i][row+j] = Water;
       }
     }
   }
 }
 return true;
}

CellContent get_my_guess(int row, int col)
{
  if(row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)   return OutOfRange;

  else   return guess[col][row];
}
