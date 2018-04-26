#include <stdio.h>    /* for printf */
#include <stdint.h>   /* for uint64 definition - from documentation */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include <time.h>     /* for clock_getime */
#include "cachewizard.h"


int main()
{ 	
	mem_init();
	cache_size();
	find_speeds();
	line_size();
	mem_free();
	// end program
	return 0;
}