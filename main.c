#include "sudoku_solver.h"
#include "sudoku_reader.h"
#include "sudoku_gui.h"
#include<stdio.h>

int main(int argc, char* argv[])
{
	int **sudoku=NULL;
	if (argc==2)
	{
		sudoku=read_matrix(argv[1]);
	}
	else
	{
		sudoku=allocate_empty_matrix(9,9);
	}
	int res = sudoku_gui(sudoku);
   /*int res=sudoku_solver(sudoku);
   if (res ==0)
   {
	   display_matrix(sudoku);
   }
   else
   {
	   printf("No solution found :(\n");
   }*/
   return res;
}   

