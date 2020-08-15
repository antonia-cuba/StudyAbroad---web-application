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
   long cnr1 = nr;
   
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
   { //calculam primul pas
      nr2 = nr2 + (cnr % 100 / 10 * 2) * p;
      cnr /= 100;
      p *= 10;
   }
   
   while (nr2)
   {
      sum1 = sum1 + nr2 %10;
      nr2 /=10;
   }
   int sum2 = sum1;
   
   while (cnr1)
   {
      sum2 = sum2 + cnr1 % 10;
      cnr1 /= 100;
   }
   
   if (sum2 % 10 != 0)
       printf("INVALID\n");
   else if (nrc == 15 && (prim == 34 || prim == 37))
        printf("AMEX\n");
   else if ( nrc ==16 && (prim == 51 || prim == 52 || prim == 53 || prim == 54 || prim == 55))
      printf("MASTERCARD\n");
   else if ((nrc == 13 || nrc == 16) && prim / 10 == 4)
      printf("VISA\n");
   
   
   
  // printf("%i, %i, %i\n", nrc, nr2, sum2 );
}