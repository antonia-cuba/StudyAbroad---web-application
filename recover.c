#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }
    
    //filename
    char *card = argv[1];
    
    FILE *input = fopen(card, "r");
    if ( input == NULL)
    {
        fprintf(stderr, "Could not open %s\n", card);
        return 2;
    }
    
    
    
    
    
    
}
