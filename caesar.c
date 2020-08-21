#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for ( int j = 0, n = strlen(argv[1]); j < n; j++)
        {
            if (! isdigit(argv[1][j]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isupper(plain[i]))
        {
            printf("%c", (plain[i] - 65 + key) % 26 + 65);
        }
        else if (islower(plain[i]))
        {
            printf("%c", (plain[i] - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}