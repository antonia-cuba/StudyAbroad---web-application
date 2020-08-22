#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    
    char letter[26];
    
    if (argc == 2)
    {
        if (strlen(argv[1]) != 26)
            {
                printf("Key must contain 26 characters.\n"); // nr of letters WORKS
                return 1;
            }
            
            
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (! (isupper(argv[1][i]) || islower(argv[1][i]))) // if it's just letters WORKS
            {
                printf("./substitution key\n");
                return 1;
            }
        }
        
        
        if (strlen(argv[1]) == 26)
        {
            for (int j = 0; j < 26; j++)
            {
                letter[j] = tolower(argv[1][j]); // makes all the letters lower WORKS
            }
        }
        
        for (int m = 0; m <  24; m++)
        {
           for( int n = m + 1; n < 25; n++)
        {
            if (letter[m] == letter[n]) // verifies if there are no duplicate letters
            {
                printf("duplicate\n");
                return 1;
            }
        }
        }
    }
    else if (argc != 2)
    {
        printf("./substitution key\n"); // if there are more commands or no command
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
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
