#include <stdio.h>    /* for printf */
#include <stdint.h>   /* for uint64 definition - from documentation */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include <time.h>     /* for clock_getime */

//example from clock_gettime documentation
#define BILLION 1000000000L
int localpid(void){
	static int a[9] = { 0 };
	return a[0];
}

int main(int argc, char** argv)
{ 	
	uint64_t diff;
	struct timespec start, end;
	int i;

	/* measure monotonic time */ 
	clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
	//access data here
	clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

	// end program
	return 0;
}
