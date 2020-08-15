#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    int k=0;
    
    do
    {
        dollars = get_float("Change owed: ");
    } while(dollars < 0);
    
    int cents = round(dollars * 100);
    
   // if(cents >= 25)
    {
         while(cents >= 25)
        {
            cents = cents - 25;
           k++;
        }
    }
   // else
   //    if(cents >= 10)
    {
         while(cents >= 10)
        {
            cents -= 10;
            k++;
        }
    }
   // else if(cents >= 5)
    {
        while(cents >= 5)
        {
        cents -= 5;
        k++;
        }
    }
   // else
    {
        while(cents >= 1)
        {
            cents -= 1;
            k++;
        }
    }
    
    printf("%i\n", k);
}