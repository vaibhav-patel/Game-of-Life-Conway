/* serial code with all optimizations as mentioned in report */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
int **current_state;
int **next_state;
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
void show(int r,int c)
{
	int i, j;
	for (i = 0; i < r; ++i)
	{
		for (j = 0; j < c; ++j)
		{
			printf("%d ",current_state[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}
void update(int r, int c)  
{
	int i, j, k;
	for(i = 1; i < r - 1; i++) // loop only through inner cells
	{
		int alive_neigbours, is_alive, v3 = 0, v2 = 0, v1 = 0;
		int k;
		j = 1;
		v1 = current_state[i][j - 1] + current_state[i - 1][j - 1] + current_state[i + 1][j - 1]; 
			// v1 maintains alive neighbours of previous column for current cell. 
		v2 = current_state[i - 1][j] + current_state[i + 1][j] ;
			// v2 maintains alive neighbours of same column as of current cell.
		v3 = current_state[i][j + 1] + current_state[i - 1][j + 1] + current_state[i + 1][j + 1];
			// v3 maintains alive neighbours of next column for current cell.
		for(j = 1; j < c - 1; j++)
		{
			alive_neigbours = v1 + v2 + v3; 
			v2 += current_state[i][j];     // updating v1, v2, v3 for cell of next column 
			v3 -= current_state[i][j + 1]; 
			v1 = v2;      // new_v1 = old_v2 + state(i, j)
			v2 = v3;      // new_v2 = old_v3 - state(i, j + 1);
			v3 = current_state[i - 1][j + 2] + current_state[i][j + 2] + current_state[i + 1][j + 2];	
				// new_v3 is to be calculated be checking neigbours of next to next column 	
			is_alive = current_state[i][j];
			next_state[i][j] = is_alive;   // next_state[i][j] is temporary grid to store next state of each cell
			if(is_alive && (alive_neigbours < 2 || alive_neigbours > 3)) // update status as per over-population
						                                              // and under-population rule
			{
				next_state[i][j] = 0;
			}
			if(!is_alive && alive_neigbours == 3)    // update status as per reproduction rule
			{
				next_state[i][j] = 1;
			}	
		}
	}
	for(i = 0; i < r; i++) // Now loop through left and rightmost cells of each row
	{
		j = 0;           // For leftmost cells
		int alive_neighbours = 0;
		for(k = 0; k < 8; k++) // No loop unrolling , because wont't affect much as complexity of this loop is less.
		{
			int ni = (i + dx[k]);
			int nj = (j + dy[k]);
			if(ni < 0) ni += r;
			if(nj < 0) nj += c;
			if(ni >= r) ni -= r;
			if(nj >= c) nj -= c;	
			alive_neighbours += current_state[ni][nj];
		}
		int is_alive = current_state[i][j];
		next_state[i][j] = is_alive;
		if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
		{
			next_state[i][j] = 0;
		}
		if(!is_alive && alive_neighbours == 3)
		{
			next_state[i][j] = 1;
		}
		j = c - 1;        // For rightmost cells
		alive_neighbours = 0;
		for(k = 0; k < 8; k++)
		{
			int ni = (i + dx[k]);
			int nj = (j + dy[k]);
			if(ni < 0) ni += r;
			if(nj < 0) nj += c;
			if(ni >= r) ni -= r;
			if(nj >= c) nj -= c;	
			alive_neighbours += current_state[ni][nj];
		}
		is_alive = current_state[i][j];
		next_state[i][j] = is_alive;
		if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
		{
			next_state[i][j] = 0;
		}
		if(!is_alive && alive_neighbours == 3)  
		{
			next_state[i][j] = 1;
		}
	}
	for(j = 0; j < c; j++)  // Loop through first and last cells of each column
	{
		i = 0; 				// For first cell of each column
		int alive_neighbours = 0;
		for(k = 0; k < 8; k++)
		{
			int ni = (i + dx[k]);
			int nj = (j + dy[k]);
			if(ni < 0) ni += r;
			if(nj < 0) nj += c;
			if(ni >= r) ni -= r;
			if(nj >= c) nj -= c;	
			alive_neighbours += current_state[ni][nj];
		}
		int is_alive = current_state[i][j];
		next_state[i][j] = is_alive;
		if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
		{
			next_state[i][j] = 0;
		}
		if(!is_alive && alive_neighbours == 3)
		{
			next_state[i][j] = 1;
		}
		i = r - 1;			// For last cell of each column
		alive_neighbours = 0;
		for(k = 0; k < 8; k++)
		{
			int ni = (i + dx[k]);
			int nj = (j + dy[k]);
			if(ni < 0) ni += r;
			if(nj < 0) nj += c;
			if(ni >= r) ni -= r;
			if(nj >= c) nj -= c;	
			alive_neighbours += current_state[ni][nj];
		}
		is_alive = current_state[i][j];
		next_state[i][j] = is_alive;
		if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
		{
			next_state[i][j] = 0;
		}
		if(!is_alive && alive_neighbours == 3)
		{
			next_state[i][j] = 1;
		}
	}

	int **temp = current_state; // just swap pointers of current_state and next_state instead of 
								// using r * c loop.
	current_state = next_state;
	next_state = temp;
}
int main(int argc , char** argv)
{
	int i, j, r, c, total_steps, steps;   // r = rows, c = columns, total_steps = number of generations
	r = atoi(argv[1]);
	c = atoi(argv[2]);
	total_steps = atoi(argv[3]);
	current_state = (int **)(malloc((r + 1) * sizeof(int *)));
	next_state = (int **)(malloc((r + 1) * sizeof(int *)));
	for(i = 0; i < r; i++)
	{
		current_state[i] = (int *)(malloc((c + 1) * sizeof(int)));
		next_state[i] = (int *)(malloc((c + 1) * sizeof(int)));
		for(j = 0; j < c; j++)
		{
			current_state[i][j] = rand() % 2;   // current_state[i][j] = 1  ==>  (i, j) is alive 
												// current_state[i][j] = 0  ==>  (i, j) is dead
		}
	}
	double start = omp_get_wtime();
	for(steps = 0; steps < total_steps; steps++)
	{		
		update(r, c);                           // finds next_state of each cell from current_state as per rules of Game of Life
	}
	double stop = omp_get_wtime();
	printf("%0.10lf\n", (stop - start));
}