#include <stdio.h>
#include <limits.h>
#include "wgrib2.h"

#ifdef USE_OPENMP
#include <omp.h>
#endif


/* openmp compatible routines, does not require OpenMP 3.1
 *   now requires OpenMP 3.1
 *
 * Public Domain 8/2015 Wesley Ebisuzaki  
 *               6/2016 Wesley Ebisuzaki
 *
 * 4/2022: now requires OpenMP 3.1 like rest of wgrib2.
 */

/*
 * min_max_array()  returns min/max of the array
 *
 * return 0:  if min max found
 * return 1:  if min max not found, min = max = 0
 */

int min_max_array(float *data, unsigned int n, float *min, float *max) {

    unsigned int first, i;
    float mn, mx;

    if (n == 0) {
	*min = *max = 0.0;
	return 1;
    }

    for (first = 0; first < n; first++) {
        if (DEFINED_VAL(data[first])) break;
    }
    if (first >= n) {
	*min = *max = 0.0;
	return 1;
    }

    mn = mx = data[first];
#pragma omp parallel for private(i) reduction(min:mn) reduction(max:mx)
    for (i = first+1; i < n; i++) {
	if (DEFINED_VAL(data[i])) {
	    mn = (mn > data[i]) ? data[i] : mn;
            mx = (mx < data[i]) ? data[i] : mx;
        }
    }

    *min = mn;
    *max = mx;
    return 0;
}

/*
 * min_max_array_all_defined()  returns min/max of the array which has all values defined
 *
 * return 0:  if min max found
 * return 1:  if min max not found, min = max = 0
 */

int min_max_array_all_defined(float *data, unsigned int n, float *min, float *max) {

    float mx, mn;
    unsigned int i;

    if (n == 0) {
	*min = *max = 0.0;
	return 1;
    }

    mn = mx = data[0];
#pragma omp parallel for private(i) reduction(min:mn) reduction(max:mx)
    for (i = 1; i < n; i++) {
	mx = data[i] > mx ? data[i] : mx;
	mn = data[i] < mn ? data[i] : mn;
    }
    *min = mn;
    *max = mx;
    return 0;
} 

/*
 * find min/max of an integer array
 * return 0:  if min max found
 * return 1:  if min max not found, min = max = 0
 */
int int_min_max_array(int *data, unsigned int n, int *min, int *max) {

    unsigned int first, i;
    int  mn, mx;

    *min = *max = 0;
    if (n == 0) return 1;

    for (first = 0; first < n; first++) {
        if (data[first] != INT_MAX) break;
    }
    if (first >= n) return 1;

    mn = mx = data[first];

#pragma omp parallel for private(i) reduction(min:mn) reduction(max:mx)
    for (i = first + 1; i < n; i++) {
        if (data[i] != INT_MAX) {
	    mx = data[i] > mx ? data[i] : mx;
	    mn = data[i] < mn ? data[i] : mn;
	}
    }

    *min = mn;
    *max = mx;
    return 0;
}
