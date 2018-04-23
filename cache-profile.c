#include <stdio.h>
#include <stdint.h>   /* for uint64 defini
//example from clock_gettime documentation
#define BILLION 1000000000Ltion - from documentation */
#include <stdlib.h>
#include <time.h>

#define KB 1024
#define MB 1024 * 1024

//example from clock_gettime documentation
#define BILLION 1000000000L

long long wall_clock_time() {
	#ifdef __linux__
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		return (long long)(tp.tv_nsec + (long long)tp.tv_sec * 1000000000ll);
	#else
		#warning "Your timer resoultion might be too low. Compile on Linux and link with librt"
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
	#endif
}

int main() {
    int steps = 1024 * 1024 * 1024;
    //static int arr[16 * 1024 * 1024];
		int *arr = calloc(16 * 1024 * 1024,  sizeof(int));
    int lengthMod;
    int sizes[] = {
        1 * KB, 2 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB,
				512 * KB, 1 * MB, 2 * MB, 4 * MB, 8 * MB, 16 * MB
    };
    int results[sizeof(sizes)/sizeof(int)];

    uint64_t diff;
    struct timespec start, end;

    // for each size to test for ...
    for (int s = 0; s < sizeof(sizes)/sizeof(int); s++) {
	    lengthMod = sizes[s] - 1;
	    clock_gettime(CLOCK_MONOTONIC, &start);
	    for (int i = 0; i < steps; i++) {
	        ++arr[i & lengthMod];
	    }
	    clock_gettime(CLOCK_MONOTONIC, &end); /* mark the end time */
      diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
      printf("%d, %lf \n", sizes[s] / 1024, (double) ((long long unsigned int) diff) / steps);
    }

    return 0;
}
