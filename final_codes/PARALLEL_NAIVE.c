/* parallel code without any optimizations */


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
int **current_state;
int **next_state;
int **debug_state;

int debug =0;
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

void print_state(int **state,int r,int c)
{
	int i,j;
	for ( i = 0; i < r; ++i)
	{
		for (j = 0; j < c; ++j)
		{
			printf("%d ",state[i][j] );
		}
		printf("\n");
	}

}
int check_correctness(int r,int c)
{	
	int i,j;
	for ( i = 0; i < r; ++i)
	{
		for ( j = 0; j < c; ++j)
		{
			debug_state[i][j]=0;
		}
	}
	for(i = 0; i < r; i++)
	{
		//
		for(j = 0; j < c; j++)
		{
			//printf("%d ", current_state[i][j]);
			int alive_neighbours = 0;
			alive_neighbours = get_neighbours(i, j,r,c);
			int is_alive = current_state[i][j];
			debug_state[i][j] = is_alive;
			if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
			{
				debug_state[i][j] = 0;
			}
			if(!is_alive && alive_neighbours == 3)
			{
				debug_state[i][j] = 1;
			}
		}
		//printf("\n");
	}

	for ( i = 0; i < r; ++i)
	{
		for ( j = 0; j < c; ++j)
		{
			if(next_state[i][j] != debug_state[i][j])
			{
				printf("%d   %d\n",i,j );
				printf("%d   %d\n",next_state[i][j],debug_state[i][j] );
				
				return 1;
			}
		}
	}
return 0;

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
	#pragma omp parallel for private(i, j)
		// dividing rows among threads
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
	if(debug)
		if(check_correctness(r,c))
			printf("error\n");

	#pragma omp parallel for private(i, j)
		// dividing rows among threads
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
	omp_set_num_threads(atoi(argv[4]));

	current_state = (int **)(malloc(r * sizeof(int *)));
	next_state = (int **)(malloc(r * sizeof(int *)));
	if(debug)
		debug_state = (int **)(malloc(r * sizeof(int *)));
	
	for(i = 0; i < r; i++)
	{
		current_state[i] = (int *)(malloc(c * sizeof(int)));
		next_state[i] = (int *)(malloc(c * sizeof(int)));
		if(debug)
			debug_state[i] = (int *)(malloc(c * sizeof(int)));		
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