#define CNT 9

/* $begin structprob-astruct-c */
typedef struct {
    int idx;
    int x[4];
} a_struct;
/* $end structprob-astruct-c */

/* $begin structprob-ans-c */
typedef struct {
    int left;
    a_struct a[CNT];
    int right;
} b_struct;

void test(int i, b_struct *bp)
{
    int n = bp->left + bp->right;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}
/* $end structprob-ans-c */

