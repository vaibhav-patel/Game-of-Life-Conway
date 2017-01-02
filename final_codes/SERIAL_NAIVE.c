/* serial code without any optimization */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
int **current_state;
int **next_state;
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int get_neighbours(int i, int j, int r,int c)
{
	int ret = 0, k;
	for(k = 0; k < 8; k++)
	{
		int ni = i + dx[k];
		int nj = j + dy[k];
		if(ni < 0) ni += r;          // Handling border cells (toroidal structure)
		if(nj < 0) nj += c;
		if(ni >= r) ni -= r;
		if(nj >= c) nj -= c;
		ret += current_state[ni][nj];
	}
	return ret;     // ret = number of alive neigbours
}
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
	int i, j;
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			int alive_neighbours = get_neighbours(i, j, r, c);
			int is_alive = current_state[i][j];
			next_state[i][j] = is_alive;  // next_state[i][j] is temporary grid to store next state of each cell
			if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))  // update status as per over-population
													// and under-population rule
			{
				next_state[i][j] = 0;
			}
			if(!is_alive && alive_neighbours == 3) // update status as per reproduction rule
			{
				next_state[i][j] = 1;
			}
		}
	}
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			current_state[i][j] = next_state[i][j];  // make current_state = next_state.
		}

	}
}
int main(int argc , char** argv)
{
	int i, j, r, c, total_steps, steps;   // r = rows, c = columns, total_steps = number of generations
	r = atoi(argv[1]);
	c = atoi(argv[2]);
	total_steps = atoi(argv[3]);
	current_state = (int **)(malloc(r * sizeof(int *)));
	next_state = (int **)(malloc(r * sizeof(int *)));
	for(i = 0; i < r; i++)
	{
		current_state[i] = (int *)(malloc(c * sizeof(int)));
		next_state[i] = (int *)(malloc(c * sizeof(int)));
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