#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    int space;
    do
    {
        n = get_int("Size: ");
    }
    while (n<1 || n>8);
    // gets input from user
    
    for(int i=1; i<=n; i++)
    {
          space=n-i;
          //if(space>0)
          {
              for(int k=1; k<=space; k++)
              {
                  printf(" "); //print the spaces
              }
              
              for(int kk=1; kk<=i; kk++)
              {
                  printf("#"); //print the #
              }
              
              printf("  ");
              
              for(int kkk=1; kkk<=i; kkk++)
              {
                  printf("#"); //print the # in the right
              }
              printf("\n");
           }
    }
    
}