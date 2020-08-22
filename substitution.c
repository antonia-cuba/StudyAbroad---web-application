#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int m = 0; m < strlen(argv[1]) - 1; m++)
            for( int n = 1; n < strlen(argv[1]); n++)
        {
            if (argv[1][m] == argv[1][n])
            {
                printf("duplicate\n");
                return 1;
            }
        }
        
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (strlen(argv[1]) != 26)
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            else if (! (isupper(argv[1][i]) || islower(argv[1][i])))
            {
                printf("./substitution key\n");
                return 1;
            }
        }
    }
    else if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    char letter[26];
    for (int j = 0; j < 26; j++)
    {
        letter[j] = tolower(argv[1][j]);
    }
    
    for (int k = 0; k < strlen(text); k++)
    {   int nr = text[k]; // we transform the letter in ascii nr
        if (islower(text[k]))
        {
            printf("%c", letter[nr - 97]);
        }
        else if (isupper(text[k]))
        {
            printf("%c", toupper(letter[nr - 65]));
        }
        else
        {
            printf("%C", text[k]);
        }
    }
    printf("\n");
}