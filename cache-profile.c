#include <stdio.h>
#include <stdint.h>   /* for uint64 defini
//example from clock_gettime documentation
#define BILLION 1000000000Ltion - from documentation */
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define KB 1024
#define MB 1024 * 1024

//example from clock_gettime documentation
#define BILLION 1000000000L

int main() {
    int steps = 1024 * 1024 * 1024 / 10;
    //static int arr[16 * 1024 * 1024];
		char* arr = malloc(16 * 1024 * 1024 * sizeof(char));
    int lengthMod;
    int sizes[] = {
        1 * KB, 2 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB,
				512 * KB, 1 * MB, 2 * MB, 4 * MB, 8 * MB, 16 * MB
    };
		double results[sizeof(sizes)];
		int stride = 256;

    uint64_t diff;
    struct timespec start, end;

		printf("Size(KB), Average time(ns)\n");

    // for each size to test for ...
    for(int s = 0; s < sizeof(sizes)/sizeof(int); s++) {
	    lengthMod = sizes[s] - 1;
	    clock_gettime(CLOCK_REALTIME, &start);
	    for (int i = 0; i < steps; i++) {
	        ++arr[(i * stride) & lengthMod];
					//printf("%d\n", (i * stride) % lengthMod);
					//++*arr;
	    }
	    clock_gettime(CLOCK_REALTIME, &end); /* mark the end time */
      diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
			results[s] = (double) ((long long unsigned int) diff) / steps;
      printf("%d, %lf \n", sizes[s] / 1024, (double) ((long long unsigned int) diff) / steps);
    }

		int max_diff = 0;
		int jump_loc = -1;
		for(int i = 0; i < sizeof(sizes)/sizeof(int) - 1; ++i) {
			if(results[i+1] - results[i] > max_diff) {
				jump_loc = i;
				max_diff = results[i+1] - results[i];
			}
		}
		printf("Cache size is between %dK and %dK.\n", sizes[jump_loc] / KB, sizes[jump_loc + 1] / KB);
		double cache_avg = 0;
		double ram_avg = 0;
		for(int i = 0; i < sizeof(sizes)/sizeof(int); ++i) {
			if(i <= jump_loc) {
				cache_avg += results[i];
			} else {
				ram_avg += results[i];
			}
		}
		cache_avg /= (double) (jump_loc + 1);
		ram_avg /= (double)((sizeof(sizes)/sizeof(int)) - jump_loc - 1);
		printf("Average speed of cache: %lf\n", cache_avg);
		printf("Average speed of main memory: %lf\n", ram_avg);

		printf("Stride(B), Average time(ns)\n");

		int strides[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
										 150};
		double stride_results[sizeof(strides)/sizeof(int)];
		// for each size to test for ...
		for(int s = 0; s < sizeof(strides)/sizeof(int); s++) {
			lengthMod = sizes[jump_loc + 1] - 1;
			stride = strides[s];
			clock_gettime(CLOCK_REALTIME, &start);
			for (int i = 0; i < steps; i++) {
					++arr[(i * stride) & lengthMod];
					//printf("%d\n", (i * stride) % lengthMod);
					//++*arr;
			}
			clock_gettime(CLOCK_REALTIME, &end); /* mark the end time */
			diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
			stride_results[s] = (double) ((long long unsigned int) diff) / steps;
			printf("%d, %lf \n", strides[s], (double) ((long long unsigned int) diff) / steps);
		}
		printf("Line size: %d Bytes\n", 64);

		free(arr);
    return 0;
}
