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
    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE aux[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            int counter = 0;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[i + k][j + h].rgbtBlue;
                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumRed += image[i + k][j + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            aux[i][j].rgbtBlue = round(sumBlue / counter);
            aux[i][j].rgbtGreen = round(sumGreen / counter);
            aux[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = aux[i][j].rgbtBlue;
            image[i][j].rgbtGreen = aux[i][j].rgbtGreen;
            image[i][j].rgbtRed = aux[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE aux[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            aux[i][j] = image[i][j];
            
    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxBlue = 0;
            float GxGreen = 0;
            float GxRed = 0;
            float GyBlue = 0;
            float GyGreen = 0;
            float GyRed = 0;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k > height - 1)
                {
                    continue;
                }
                    if (j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }
                
                GxRed += aux[i + k][j + h].rgbtRed * Gx[k + 1][h + 1];
                GxBlue += aux[i + k][j + h].rgbtBlue * Gx[k + 1][h + 1];
                GxGreen += aux[i + k][j + h].rgbtGreen * Gx[k + 1][h + 1];
                GyRed += aux[i + k][j + h].rgbtRed * Gy[k + 1][h + 1];
                GyBlue += aux[i + k][j + h].rgbtBlue * Gy[k + 1][h + 1];
                GyGreen += aux[i + k][j + h].rgbtGreen * Gy[k + 1][h + 1];
                }
            }
            
            int red = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            int green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            
            // Stop at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
