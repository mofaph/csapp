#include <stdlib.h>
#include "combine.h"

/* $begin vec */
/* Create vector of specified length */
vec_ptr new_vec(int len)
{
    /* allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    if (!result)
        return NULL;  /* Couldn't allocate storage */
    result->len = len;
/* $end vec */
    /* We don't show this in the book */
    result->allocated_len = len;
/* $begin vec */
    /* Allocate array */
    if (len > 0) {
        data_t *data = (data_t *)calloc(len, sizeof(data_t));
	if (!data) {
	    free((void *) result);
 	    return NULL; /* Couldn't allocate storage */
	}
	result->data = data;
    }
    else
	result->data = NULL;
    return result;
}

/*
 * Retrieve vector element and store at dest.
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, int index, data_t *dest)
{
    if (index < 0 || index >= v->len)
	return 0;
    *dest = v->data[index];
    return 1;
}

/* Return length of vector */
int vec_length(vec_ptr v)
{
    return v->len;
}
/* $end vec */


/* $begin get_vec_start */
data_t *get_vec_start(vec_ptr v)
{
    return v->data;
}
/* $end get_vec_start */


/*
 * Set vector element.
 * Return 0 (out of bounds) or 1 (successful)
 */
int set_vec_element(vec_ptr v, int index, data_t val)
{
    if (index < 0 || index >= v->len)
	return 0;
    v->data[index] = val;
    return 1;
}


/* Set vector length.  If >= allocated length, will reallocate */
void set_vec_length(vec_ptr v, int newlen)
{
    if (newlen > v->allocated_len) {
	free(v->data);
	v->data = calloc(newlen, sizeof(data_t));
	v->allocated_len = newlen;
    }
    v->len = newlen;
}
