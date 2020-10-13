
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SEED 35791246

int   main(int argc, char* argv)
{
   int      niter,
            i,
            count;
   double   x,
            y,
            z,
            pi;

            /* # of points in the 1st quadrant of unit circle */



   niter = 0;
   count = 0;
   printf("Enter the number of iterations used to estimate pi: ");
   scanf("%d",&niter);

   /* initialize random numbers */
   srand(SEED);
   count=0;
   for ( i = 0; i < niter; i++)
   {
      x = (double)rand() / RAND_MAX;
      y = (double)rand() / RAND_MAX;
      z = x * x + y * y;
      if (z <= 1)
         count++;
      }
   pi = (double)count / niter * 4;
   printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
}
