/* $begin adt */
/* Create abstract data type for vector */
typedef struct {
    int len;
    data_t *data;
/* $end adt */
    int allocated_len; /* NOTE: we don't use this field in the book */
/* $begin adt */ 
} vec_rec, *vec_ptr;
/* $end adt */

/* Create vector */
vec_ptr new_vec(int len);

/*
 * Retrieve vector element and store in dest.
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, int index, data_t *dest);

data_t *get_vec_start(vec_ptr v);

/*
 * Set vector element.
 * Return 0 (out of bounds) or 1 (successful)
 */

int set_vec_element(vec_ptr v, int index, data_t val);

/* Get vector length */
int vec_length(vec_ptr v);

/* Set length of vector.  If > allocated length, will reallocate */
void set_vec_length(vec_ptr v, int newlen);
