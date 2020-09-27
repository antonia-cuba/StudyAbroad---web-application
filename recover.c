#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if ( input == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }
    
    int counter = 0;
    int found = 0;
    FILE *final_img = NULL;
    byte buffer[512];
    
    while (fread(buffer, 512, 1, input)) //reads the first block of memory
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found == 1)
            {
                fclose(final_img);
            }
            else
            {
                found = 1;
            }
            
            char filename[8]; // for ex 000.jpg\0; there are 8 characters
            sprintf(filename, "%03i.jpg", counter);
            final_img = fopen(filename, "w");
            counter++;
        }
        
        if (found == 1)
        {
            fwrite(buffer, 512, 1, final_img);
        }
    }
    
    fclose(final_img);
    fclose(input);
    return 0;
}
