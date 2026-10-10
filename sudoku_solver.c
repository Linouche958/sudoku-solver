#include<stddef.h>

static int valid_number(int **mat,size_t row,size_t col,int num)
{
	for (size_t i=0;i<9;i++)
	{
		if (mat[row][i]==num)
		{
			return 0;
		}
	} 
	for (size_t i=0;i<9;i++)
	{
		if (mat[i][col]==num)
		{
			return 0;
		}
	} 
	size_t startRow = row - (row % 3);
	size_t startCol = col - (col % 3);
	for (size_t i=0;i<3;i++)
	{
		for (size_t j=0;j<3;j++)
		{
			if (mat[i+startRow][j+startCol]==num)
			{
				return 0;
			}
		}
	}
	return 1;
}

static int sudoku_rec(int **mat,size_t row,size_t col)
{
	if (row==8 && col== 9)
	{
		return 0;
	}
	if (col==9)
	{
		row+=1;
		col=0;
	}
	if (mat[row][col]!=0)
	{
		return sudoku_rec(mat, row, col+1);
	}
	for (int i=1;i<10;i++)
	{
		if (valid_number(mat,row,col,i)==1)
		{
			mat[row][col]=i;
			if (sudoku_rec(mat,row,col+1)==0)
			{
				return 0;
			}
			mat[row][col]=0;
		}
	}
	return 1;
}

int sudoku_solver(int **mat)
{
	return sudoku_rec(mat,0,0);
}



