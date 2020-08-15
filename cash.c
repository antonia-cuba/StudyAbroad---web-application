#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    int k = 0; //k means nr of coins used
    
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    
    int cents = round(dollars * 100); //transforms $ in cents
    
    while (cents >= 25)
    {
        cents = cents - 25;
        k++;
    }
        
    while (cents >= 10)
    {
        cents -= 10;
        k++;
    }
        
    while (cents >= 5)
    {
        cents -= 5;
        k++;
    }
    
    while (cents >= 1)
    {
        cents -= 1;
        k++;
    }
    
    printf("%i\n", k);
}