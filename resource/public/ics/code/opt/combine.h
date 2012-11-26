#ifdef FLOAT
typedef float data_t;
#define DATA_NAME "Float"
#else
#ifdef DOUBLE
typedef double data_t;
#define DATA_NAME "Double"
#else
#ifdef EXTEND
typedef long double data_t;
#define DATA_NAME "Extended"
#else
/* $begin typedefint */
typedef int data_t;
/* $end typedefint */ 
#define DATA_NAME "Integer"
#endif /* EXTEND */
#endif /* DOUBLE */
#endif /* FLOAT */

#ifdef PROD
/* $begin operprod */
#define IDENT 1
#define OPER  *
/* $end operprod */
#define OPER_NAME "Product"
#else
#ifdef DIV
#define OPER /
#define IDENT 1
#define OPER_NAME "Divide"
#else
/* $begin operplus */
#define IDENT 0
#define OPER  +
/* $end operplus */
#define OPER_NAME "Sum"
#endif /* DIV */
#endif /* PROD */

#include "vec.h"

/* Declaration of a combining routine */
/* Source vector, destination location */ 
typedef void (*combiner)(vec_ptr, data_t *);

/* Add combining routine to list of programs to measure */
void add_combiner(combiner f, combiner fc, char *description);

/* Called by main to register the set of transposition routines to benchmark */
void register_combiners(void);


