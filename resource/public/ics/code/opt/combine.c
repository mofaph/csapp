#include "combine.h"

/* Combining functions */

char combine1_descr[] = "combine1: Maximum use of data abstraction";
/* $begin combine1 */
/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest)
{
    int i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
	data_t val;
	get_vec_element(v, i, &val);
	/* $begin combineline */
	*dest = *dest OPER val;
	/* $end combineline */
    }
}
/* $end combine1 */

char combine2_descr[] = "combine2: Take vec_length() out of loop";
/* $begin combine2 */
/* Move call to vec_length out of loop */
void combine2(vec_ptr v, data_t *dest)
{
    int i;
    int length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
	data_t val;
	get_vec_element(v, i, &val);
	*dest = *dest OPER val;
    }
}
/* $end combine2 */

char combine3_descr[] = "combine3: Array reference to vector data";
/* $begin combine3 */
/* Direct access to vector data */
void combine3(vec_ptr v, data_t *dest)
{
    int i;
    int length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
	*dest = *dest OPER data[i];
    }
}
/* $end combine3 */

char combine4_descr[] = "combine4: Array reference, accumulate in temporary";
/* $begin combine4 */
/* Accumulate result in local variable */
void combine4(vec_ptr v, data_t *dest)
{
    int i;
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t x = IDENT;

    for (i = 0; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}
/* $end combine4 */

char combine4p_descr[] = "combine4p: Pointer reference, accumulate in temporary";
/* $begin combine4p */
/* Accumulate in local variable, pointer version */
void combine4p(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length;
    data_t x = IDENT;

    for (; data < dend; data++)
	x = x OPER *data;
    *dest = x;
}
/* $end combine4p */


char unroll2a_descr[] = "Array code, unrolled by 2";
void unroll2a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;

    int i;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
	x = x OPER data[i] OPER data[i+1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char combine5_descr[] = "combine5: Array code, unrolled by 3";
/* $begin combine5 */
/* Unroll loop by 3 */
void combine5(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-2;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 3 elements at a time */
    for (i = 0; i < limit; i+=3) {
	x = x OPER data[i] OPER data[i+1] OPER data[i+2];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}
/* $end combine5 */

char combine5p_descr[] = "combine5p: Pointer code, unrolled by 3, for loop";
/* $begin combine5p */
/* Unroll loop by 3, pointer version */
void combine5p(vec_ptr v, data_t *dest)
{
    data_t *data = get_vec_start(v);
    data_t *dend = data+vec_length(v);
    data_t *dlimit = dend-2;
    data_t x = IDENT;

    /* Combine 3 elements at a time */
    for (; data < dlimit; data += 3) {
	x = x OPER data[0] OPER data[1] OPER data[2];
    }

    /* Finish any remaining elements */
    for (; data < dend; data++) {
	x = x OPER data[0];
    }
    *dest = x;
}
/* $end combine5p */

char unroll3aw_descr[] = "Array code, unrolled by 3, while loop";
void unroll3aw_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i = 0;

    /* Combine 3 elements at a time */
    while (i < limit) {
	x = x OPER data[i];
	i+= 3;
	x = x OPER data[i-2] OPER data[i-1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}


char unroll4a_descr[] = "Array code, unrolled by 4";
void unroll4a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-3;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 4 elements at a time */
    for (i = 0; i < limit; i+=4) {
	x = x OPER data[i] OPER data[i+1];
	x = x OPER data[i+2] OPER data[i+3];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll8a_descr[] = "Array code, unrolled by 8";
void unroll8a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-7;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 8 elements at a time */
    for (i = 0; i < limit; i+=8) {
	x = x OPER data[i] OPER data[i+1];
	x = x OPER data[i+2] OPER data[i+3];
	x = x OPER data[i+4] OPER data[i+5];
	x = x OPER data[i+6] OPER data[i+7];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll16a_descr[] = "Array code, unrolled by 16";
void unroll16a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-15;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 16 elements at a time */
    for (i = 0; i < limit; i+=16) {
	x = x OPER data[i] OPER data[i+1];
	x = x OPER data[i+2] OPER data[i+3];
	x = x OPER data[i+4] OPER data[i+5];
	x = x OPER data[i+6] OPER data[i+7];
	x = x OPER data[i+8] OPER data[i+9];
	x = x OPER data[i+10] OPER data[i+11];
	x = x OPER data[i+12] OPER data[i+13];
	x = x OPER data[i+14] OPER data[i+15];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll2_descr[] = "Pointer code, unrolled by 2";
void unroll2_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    int over = length%2;
    data_t *dend = data+length-over;
    data_t x = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	x = x OPER data[1];
	data += 2;
    }
    dend += over;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x;
}


char unroll3_descr[] = "Pointer code, unrolled by 3";
void unroll3_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-2;
    data_t x = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	x = x OPER data[1];
	x = x OPER data[2];
	data += 3;
    }
    dend += 2;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x;
}


char unroll4_descr[] = "Pointer code, unrolled by 4";
void unroll4_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-3;
    data_t x = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	x = x OPER data[1];
	x = x OPER data[2];
	x = x OPER data[3];
	data += 4;
    }
    dend += 3;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x;
}

char unroll8_descr[] = "Pointer code, unrolled by 8";
void unroll8_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    int over = length%8;
    data_t *dend = data+length-over;
    data_t x = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	x = x OPER data[1];
	x = x OPER data[2];
	x = x OPER data[3];
	x = x OPER data[4];
	x = x OPER data[5];
	x = x OPER data[6];
	x = x OPER data[7];
	data += 8;
    }
    dend += over;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x;
}

char unroll16_descr[] = "Pointer code, unrolled by 16";
void unroll16_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    int over = length%16;
    data_t *dend = data+length-over;
    data_t x = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	x = x OPER data[1];
	x = x OPER data[2];
	x = x OPER data[3];
	x = x OPER data[4];
	x = x OPER data[5];
	x = x OPER data[6];
	x = x OPER data[7];
	x = x OPER data[8];
	x = x OPER data[9];
	x = x OPER data[10];
	x = x OPER data[11];
	x = x OPER data[12];
	x = x OPER data[13];
	x = x OPER data[14];
	x = x OPER data[15];
	data += 16;
    }
    dend += over;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x;
}


char combine6_descr[] = "combine6: Array code, unrolled by 2, Superscalar x2";
/* $begin combine6 */
/* Unroll loop by 2, 2-way parallelism */
void combine6(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    int i;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
	x0 = x0 OPER data[i]; 
	x1 = x1 OPER data[i+1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x0 = x0 OPER data[i];
    }
    *dest = x0 OPER x1;
}
/* $end combine6 */

char unroll4x2a_descr[] = "Array code, unrolled by 4, Superscalar x2";
void unroll4x2a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-3;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    data_t y = IDENT;
    int i;

    /* Combine 4 elements at a time */
    for (i = 0; i < limit; i+=4) {
	x = x OPER data[i]; y = y OPER data[i+1];
	x = x OPER data[i+2]; y = y OPER data[i+3];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x OPER y;
}


char unroll8x2a_descr[] = "Array code, unrolled by 8, Superscalar x2";
void unroll8x2a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-7;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    data_t y = IDENT;
    int i;

    /* Combine 8 elements at a time */
    for (i = 0; i < limit; i+=8) {
	x = x OPER data[i]; y = y OPER data[i+1];
	x = x OPER data[i+2]; y = y OPER data[i+3];
	x = x OPER data[i+4]; y = y OPER data[i+5];
	x = x OPER data[i+6]; y = y OPER data[i+7];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x OPER y;
}

char unroll8x4a_descr[] = "Array code, unrolled by 8, Superscalar x4";
void unroll8x4a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-7;
    data_t *data = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    data_t x2 = IDENT;
    data_t x3 = IDENT;
    int i;

    /* Combine 8 elements at a time */
    for (i = 0; i < limit; i+=8) {
	x0 = x0 OPER data[i];   x1 = x1 OPER data[i+1];
	x2 = x2 OPER data[i+2]; x3 = x3 OPER data[i+3];
	x0 = x0 OPER data[i+4]; x1 = x1 OPER data[i+5];
	x2 = x2 OPER data[i+6]; x3 = x3 OPER data[i+7];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x0 = x0 OPER data[i];
    }
    *dest = x0 OPER x1 OPER x2 OPER x3;
}

char unroll12x6a_descr[] = "Array code, unrolled by 12, Superscalar x6";
void unroll12x6a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-11;
    data_t *data = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    data_t x2 = IDENT;
    data_t x3 = IDENT;
    data_t x4 = IDENT;
    data_t x5 = IDENT;
    int i;

    /* Combine 12 elements at a time */
    for (i = 0; i < limit; i+=12) {
	x0 = x0 OPER data[i];
	x0 = x0 OPER data[i+6]; 
	x1 = x1 OPER data[i+1];
	x1 = x1 OPER data[i+7];
	x2 = x2 OPER data[i+2];
	x2 = x2 OPER data[i+8]; 
	x3 = x3 OPER data[i+3];
	x3 = x3 OPER data[i+9];
	x4 = x4 OPER data[i+4]; 
	x4 = x4 OPER data[i+10]; 
	x5 = x5 OPER data[i+5];
	x5 = x5 OPER data[i+11];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x0 = x0 OPER data[i];
    }
    *dest = (x0 OPER x1) OPER (x2 OPER x3) OPER (x4 OPER x5);
}

char unroll8x8a_descr[] = "Array code, unrolled by 8, Superscalar x8";
void unroll8x8a_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-7;
    data_t *data = get_vec_start(v);
    data_t x0 = IDENT;
    data_t x1 = IDENT;
    data_t x2 = IDENT;
    data_t x3 = IDENT;
    data_t x4 = IDENT;
    data_t x5 = IDENT;
    data_t x6 = IDENT;
    data_t x7 = IDENT;
    int i;

    /* Combine 8 elements at a time */
    for (i = 0; i < limit; i+=8) {
	x0 = x0 OPER data[i];   x1 = x1 OPER data[i+1];
	x2 = x2 OPER data[i+2]; x3 = x3 OPER data[i+3];
	x4 = x4 OPER data[i+4]; x5 = x5 OPER data[i+5];
	x6 = x6 OPER data[i+6]; x7 = x7 OPER data[i+7];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x0 = x0 OPER data[i];
    }
    *dest = x0 OPER x1 OPER x2 OPER x3 OPER x4 OPER x5 OPER x6 OPER x7;
}

char unrollx2as_descr[] = "Array code, Unroll x2, Superscalar x2, noninterleaved";
void unrollx2as_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length/2;
    data_t *data = get_vec_start(v);
    data_t *data2 = data+limit;
    data_t x = IDENT;
    data_t y = IDENT;
    int i;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i++) {
	x = x OPER data[i]; y = y OPER data2[i];
    }

    /* Finish any remaining elements */
    for (i = limit*2; i < length; i++) {
	y = y OPER data[i];
    }
    *dest = x OPER y;
}

char unroll4x2as_descr[] = "Array code, Unroll x4, Superscalar x2, noninterleaved";
void unroll4x2as_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length/2;
    data_t *data = get_vec_start(v);
    data_t *data2 = data+limit;
    data_t x = IDENT;
    data_t y = IDENT;
    int i;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i++) {
	x = x OPER data[i]; y = y OPER data2[i];
    }

    /* Finish any remaining elements */
    for (i = limit*2; i < length; i++) {
	y = y OPER data[i];
    }
    *dest = x OPER y;
}



char unroll8x2_descr[] = "Pointer code, unrolled by 8, Superscalar x2";
void unroll8x2_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-7;
    data_t x = IDENT;
    data_t y = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	y = y OPER data[1];
	x = x OPER data[2];
	y = y OPER data[3];
	x = x OPER data[4];
	y = y OPER data[5];
	x = x OPER data[6];
	y = y OPER data[7];
	data += 8;
    }
    dend += 7;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x OPER y;
}

char unroll9x3_descr[] = "Pointer code, unrolled by 9, Superscalar x3";
void unroll9x3_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-8;
    data_t x = IDENT;
    data_t y = IDENT;
    data_t z = IDENT;

    while (data < dend) {
	x = x OPER data[0];
	y = y OPER data[1];
	z = z OPER data[2];
	x = x OPER data[3];
	y = y OPER data[4];
	z = z OPER data[5];
	x = x OPER data[6];
	y = y OPER data[7];
	z = z OPER data[8];
	data += 9;
    }
    dend += 8;
    while (data < dend) {
	x = x OPER *data;
	data ++;
    }
    *dest = x OPER y OPER z; 
}


char unroll8x4_descr[] = "Pointer code, unrolled by 8, Superscalar x4";
void unroll8x4_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-7;
    data_t w = IDENT;
    data_t x = IDENT;
    data_t y = IDENT;
    data_t z = IDENT;

    while (data < dend) {
	w = w OPER data[0];
	x = x OPER data[1];
	y = y OPER data[2];
	z = z OPER data[3];
	w = w OPER data[4];
	x = x OPER data[5];
	y = y OPER data[6];
	z = z OPER data[7];
	data += 8;
    }
    dend += 7;
    while (data < dend) {
	w = w OPER *data;
	data ++;
    }
    *dest = w OPER x OPER y OPER z;
}

char unroll8x8_descr[] = "Pointer code, unrolled by 8, Superscalar x8";
void unroll8x8_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t *dend = data+length-7;
    data_t a = IDENT;
    data_t b = IDENT;
    data_t c = IDENT;
    data_t d = IDENT;
    data_t w = IDENT;
    data_t x = IDENT;
    data_t y = IDENT;
    data_t z = IDENT;

    while (data < dend) {
	a = a OPER data[0];
	b = b OPER data[1];
	c = c OPER data[2];
	d = d OPER data[3];
	w = w OPER data[4];
	x = x OPER data[5];
	y = y OPER data[6];
	z = z OPER data[7];
	data += 8;
    }
    dend += 7;
    while (data < dend) {
	a = a OPER *data;
	data ++;
    }
    *dest = a OPER b OPER c OPER d OPER w OPER x OPER y OPER z;
}

char unroll2aa_descr[] = "Array code, unrolled by 2, different associativity";
/* Change associativity of combining operation */
void unroll2aa_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
	x = x OPER (data[i] OPER data[i+1]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll3aa_descr[] = "Array code, unrolled by 3, Different Associativity";
void unroll3aa_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-2;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 3 elements at a time */
    for (i = 0; i < limit; i+=3) {
	x = x OPER (data[i] OPER data[i+1] OPER data[i+2]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll4aa_descr[] = "Array code, unrolled by 4, Different Associativity";
void unroll4aa_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-3;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 4 elements at a time */
    for (i = 0; i < limit; i+=4) {
	data_t t1 = data[i] OPER data[i+1];
	data_t t2 = data[i+2] OPER data[i+3];
	x = x OPER (t1 OPER t2); 
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll6aa_descr[] = "Array code, unrolled by 6, Different Associativity";
void unroll6aa_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-5;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 6 elements at a time */
    for (i = 0; i < limit; i+=6) {
	data_t t1 = data[i] OPER data[i+1];
	data_t t2 = data[i+2] OPER data[i+3];
	data_t t3 = data[i+4] OPER data[i+5];
	x = x OPER (t1 OPER t2 OPER t3); 
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }
    *dest = x;
}

char unroll8aa_descr[] = "Array code, unrolled by 8, Different Associativity";
void unroll8aa_combine(vec_ptr v, data_t *dest)
{
    int length = vec_length(v);
    int limit = length-7;
    data_t *data = get_vec_start(v);
    data_t x = IDENT;
    int i;

    /* Combine 8 elements at a time */
    for (i = 0; i < limit; i+=8) {
	data_t t1 = data[i] OPER data[i+1];
	data_t t2 = data[i+2] OPER data[i+3];
	data_t u1 = t1 OPER t2;
	data_t t3 = data[i+4] OPER data[i+5];
	data_t t4 = data[i+6] OPER data[i+7];
	data_t u2 = t3 OPER t4;
	x = x OPER (u1 OPER u2); 
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
	x = x OPER data[i];
    }

    *dest = x;
}


void register_combiners(void)
{
    add_combiner(combine1, combine1, combine1_descr);
    add_combiner(combine2, combine1, combine2_descr);
    add_combiner(combine3, combine1, combine3_descr);
    add_combiner(combine4, combine1, combine4_descr);
    add_combiner(combine4p, combine1, combine4p_descr);
    add_combiner(unroll2a_combine, combine1, unroll2a_descr);
    add_combiner(combine5p, combine1, combine5p_descr);
    add_combiner(unroll3aw_combine, combine1, unroll3aw_descr);
    add_combiner(unroll4a_combine, combine1, unroll4a_descr);
    add_combiner(unroll8a_combine, combine1, unroll8a_descr);
    add_combiner(unroll16a_combine, combine1, unroll16a_descr);
    add_combiner(unroll2_combine, combine1, unroll2_descr);
    add_combiner(unroll3_combine, combine1, unroll3_descr);
    add_combiner(unroll4_combine, combine1, unroll4_descr);
    add_combiner(unroll8_combine, combine1, unroll8_descr);
    add_combiner(unroll16_combine, combine1, unroll16_descr);
    add_combiner(combine6, combine1, combine6_descr);
    add_combiner(unroll4x2a_combine, combine1, unroll4x2a_descr);
    add_combiner(unroll8x2a_combine, combine1, unroll8x2a_descr);
    add_combiner(unroll8x4a_combine, combine1, unroll8x4a_descr);
    add_combiner(unroll8x8a_combine, combine1, unroll8x8a_descr);
    add_combiner(unroll12x6a_combine, combine1, unroll12x6a_descr);
    add_combiner(unroll8x2_combine, combine1, unroll8x2_descr);
    add_combiner(unroll8x4_combine, combine1, unroll8x4_descr);
    add_combiner(unroll8x8_combine, combine1, unroll8x8_descr);
    add_combiner(unroll9x3_combine, combine1, unroll9x3_descr);
    add_combiner(unrollx2as_combine, combine1, unrollx2as_descr);
    add_combiner(unroll2aa_combine, combine1, unroll2aa_descr);
    add_combiner(unroll3aa_combine, combine1, unroll3aa_descr);
    add_combiner(unroll4aa_combine, combine1, unroll4aa_descr);
    add_combiner(unroll6aa_combine, combine1, unroll6aa_descr);
    add_combiner(unroll8aa_combine, combine1, unroll8aa_descr);
}







