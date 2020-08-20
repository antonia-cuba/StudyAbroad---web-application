#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string x);
int count_words(string x);
int count_sentences(string x);

int main(void)
{
    string text = get_string("Text: ");
    
    int L = count_letters(text);
    int W = count_words(text);
    int S = count_sentences(text);
    float index = 0.0588 * ((float)L / (float)W * 100) - 0.296 * ((float)S / (float)W * 100) - 15.8;
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
   
}   

    int count_letters(string x)
    // function that calc nr of letters
    {
        int L = 0;
        // nr of letters
        int c = 0;
        // contor  for letter position
        while(x[c] != '\0')
        // if letter is \0, that means we finished the string
        {
            if(isalpha(x[c]))
            // verifys if the character is a letter
            {
                L++;
            }
        c++;
        }
        return L;
    }    
    
    int count_words(string x)
    {
        int W = 1;
        int c = 0;
        while (x[c] != '\0')
        {
            if (isspace(x[c]))
            {
                W++;
            }
            c++;
        }
        return W;
    }
    
    int count_sentences(string x)
    {
        int S = 0;
        int c = 0;
        while (x[c] != '\0')
        {
            if (x[c] == '.' || x[c] == '!' || x[c] == '?')
            {
                S++;
            }
            c++;
        }
        return S;
    }