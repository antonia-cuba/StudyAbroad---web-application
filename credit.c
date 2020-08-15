#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int nrc = 0; //nr cifre
   int sum1 = 0;
   int p = 1;
   int nr2 = 0;
   
   long nr = get_long("Number: ");
   long cnr = nr;
   
   while(nr >= 100)
   {
      nr = nr / 10; //nr becomes only 2 decimals, the first two
      nrc++; //the nr of decimals in the card nr, but without the first two
   }
   nrc += 2; //the nr of total decimals
   int prim = nr; //the first 2 decimals
   
   if (nrc != 15 && nrc != 16 && nrc != 13)
      printf("INVALID\n");
      
   while (cnr)
   {
      nr2 = nr2 + (cnr % 100 / 10 * 2) * p;
      cnr /= 100;
      p *= 10;
   }
   
   
   
   
   printf("%i, %i, %i\n", nrc, prim, nr2 );
}