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
        do
        {
            cents = cents - 25;
           k++;
        } while(cents >= 25);
    }
   // else
   //    if(cents >= 10)
    {
        do
        {
            cents -= 10;
            k++;
        } while(cents >= 10);
    }
   // else if(cents >= 5)
    {
        do
        {
        cents -= 5;
        k++;
        }while(cents >= 5);
    }
   // else
    {
        do
        {
            cents -= 1;
            k++;
        }while(cents >= 1);
    }
    
    printf("%i\n", k);
}