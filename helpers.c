#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float s = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;

            s = (red + green + blue) / 3;

            image[i][j].rgbtRed = round(s);
            image[i][j].rgbtGreen = round(s);
            image[i][j].rgbtBlue = round(s);
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = aux;
        }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int m = 0;
    float averageRed = 0;
    float averageBlue = 0;
    float averageGreen = 0;
    
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                for (int k = -1; k < 2; k++)
                {
                    if (j + k < 0 || j + k > height - 1)
                        continue;

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                        continue;
                        
                            m++;
                            averageRed += image[i + h][j + k].rgbtRed;
                            averageBlue += image[i + h][j + k].rgbtBlue;
                            averageGreen += image[i + h][j + k].rgbtGreen;
                }     
            }
                image[i][j].rgbtRed = round(averageRed / m);
                image[i][j].rgbtGreen = round(averageGreen / m);
                image[i][j].rgbtBlue = round(averageBlue / m);
            }

    return;
}
