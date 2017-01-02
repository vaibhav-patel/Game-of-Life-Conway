#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
int **curr_serial;
int **next_serial;
int **prefix_sum;



void prefix(int r,int c)
{
	int i,j;
	
	for(i=1;i<r-1;i++)
	{
		for(j=1;j<c-1;j++)
		{
			prefix_sum[i][j]=curr_serial[i][j]-prefix_sum[i-1][j-1]+prefix_sum[i-1][j]+prefix_sum[i][j-1];
	//		printf("%d ",prefix_sum[i][j] );
		}
	//	printf("\n");

	}
	//		printf("\n");



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
	printf("\n");

}
void update(int r, int c, int **curr_serial, int **next_serial)
{
	prefix(r,c);
	int i, j;
	#pragma omp parallel for private(i, j)
	for(i = 3; i < r-3; i++)
	{
		//
		for(j = 3; j < c-3; j++)
		{
			//printf("%d ", curr_serial[i][j]);
			int alive_neighbours = 0;
			alive_neighbours = prefix_sum[i][j]-prefix_sum[i-3][j]-prefix_sum[i][j-3]+prefix_sum[i-3][j-3];
			int is_alive = curr_serial[i][j];
			next_serial[i][j] = is_alive;
			if(is_alive && (alive_neighbours < 2 || alive_neighbours > 3))
			{
				next_serial[i][j] = 0;
			}
			if(!is_alive && alive_neighbours == 3)
			{
				next_serial[i][j] = 1;
			}
		}
		//printf("\n");
	}
	//print_state(curr_serial,r,c);

	//print_state( next_serial,r,c);

	#pragma omp parallel for private(i, j)
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			curr_serial[i][j]=next_serial[i][j];
		}

	}
}

int main(int argc , char** argv)
{
	int i, j, r, c, total_steps, steps,thr;
	//scanf("%d%d", &r, &c);
	r=atoi(argv[1]);
	c=atoi(argv[2]);
	total_steps=atoi(argv[3]);
	thr=atoi(argv[4]);	

	curr_serial = (int **)(malloc(r * sizeof(int *)));
	next_serial = (int **)(malloc(r * sizeof(int *)));
	prefix_sum = (int **)(malloc(r * sizeof(int *)));
	
	for(i = 0; i < r; i++)
	{
		curr_serial[i] = (int *)(malloc(c * sizeof(int)));
		next_serial[i] = (int *)(malloc(c * sizeof(int)));
		prefix_sum[i] = (int *)(malloc(c * sizeof(int)));

		for(j = 0; j < c; j++)
		{
			curr_serial[i][j]=rand()%2;
			prefix_sum[i][j]=0;

			//scanf("%d",&curr_serial [i][j]);
			//curr_serial[i][j]=0;
		}
	}
	
	double start=omp_get_wtime();
	omp_set_num_threads(thr);
	if(total_steps>=10)
	{
		#pragma omp parallel
		for(steps = 0; steps < total_steps; steps++)
		{
			//if(steps%100==0)
			//	printf("steps finished %d\n",steps);
			//#pragma omp parallel for private(i, j)
			//show(curr_serial,r,c);
			
			update(r, c,curr_serial,next_serial);
			// /usleep(200000);
		}
	}
	else
	{
		for(steps = 0; steps < total_steps; steps++)
		{
			//if(steps%100==0)
			//	printf("steps finished %d\n",steps);
			//#pragma omp parallel for private(i, j)
			//show(curr_serial,r,c);
			
			update(r, c,curr_serial,next_serial);
			// /usleep(200000);
		}

	}
	double stop=omp_get_wtime();
	printf("%0.10lf\n", (stop-start));
}