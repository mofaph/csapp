/* $begin simple-if-c */
/* $begin simple-if-gotoc */
void cond(int a, int *p)
/* $end simple-if-gotoc */
{
  if (p && a > 0)
    *p += a;
}
/* $end simple-if-c */


void goto_cond(int a, int *p)
/* $begin simple-if-gotoc */
{
  if (p == 0)
    goto done;
  if (a <= 0)
    goto done;
  *p += a;
 done:
}
/* $end simple-if-gotoc */



