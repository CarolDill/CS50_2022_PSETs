#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            int average = round((blue + green + red) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the blue value
            float blue = image[i][j].rgbtBlue;
            // Get the green value
            float green = image[i][j].rgbtGreen;
            // Get the red value
            float red = image[i][j].rgbtRed;
            // Calculate the sepia value
            int newBlue = round((red * .272) + (green * .534) + (blue * .131));
            // If higher than 255, set it to 255
            if (newBlue > 255)
            {
                newBlue = 255;
            }
            int newGreen = round((red * .349) + (green * .686) + (blue * .168));
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            int newRed = round((red * .393) + (green * .769) + (blue * .189));
            if (newRed > 255)
            {
                newRed = 255;
            }
            // Set the new values for green, red and blue
            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Get the original pixel and let in a temp variable
            RGBTRIPLE temp = image[i][j];
            // Set the first pixel of the line with the last pixel
            image[i][j] = image[i][width - (j + 1)];
            // Set the last pixel with the first
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredimage [height][width];
    int sumRed;
    int sumGreen;
    int sumBlue;
    int count;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            blurredimage[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            count = 0;

            //starts the sum of each color and the counter
            sumRed += image[h][w].rgbtRed;
            sumGreen += image[h][w].rgbtGreen;
            sumBlue += image[h][w].rgbtBlue;
            count ++;

            //second line untill last, second column until last, adds top left pixel
            if ((h - 1) >= 0 && (w - 1) >= 0)
            {
                sumRed += image[h - 1][w - 1].rgbtRed;
                sumGreen += image[h - 1][w - 1].rgbtGreen;
                sumBlue += image[h - 1][w - 1].rgbtBlue;
                count ++;
            }

            //second pixel of each line until the last, adds left pixel
            if ((w - 1) >= 0)
            {
                sumRed += image[h][w - 1].rgbtRed;
                sumGreen += image[h][w - 1].rgbtGreen;
                sumBlue += image[h][w - 1].rgbtBlue;
                count ++;
            }

            //every column except last of the right, adds left pixel
            if ((w + 1) <= (width - 1))
            {
                sumRed += image[h][w + 1].rgbtRed;
                sumGreen += image[h][w + 1].rgbtGreen;
                sumBlue += image[h][w + 1].rgbtBlue;
                count ++;
            }

            //from second column until the last, adds top pixel
            if ((h - 1) >= 0)
            {
                sumRed += image[h - 1][w].rgbtRed;
                sumGreen += image[h - 1][w].rgbtGreen;
                sumBlue += image[h - 1][w].rgbtBlue;
                count ++;
            }

            //second line until last, every column except last of the right, adds top right pixel
            if ((h - 1) >= 0 && (w + 1) <= (width - 1))
            {
                sumRed += image[h - 1][w + 1].rgbtRed;
                sumGreen += image[h - 1][w + 1].rgbtGreen;
                sumBlue += image[h - 1][w + 1].rgbtBlue;
                count ++;
            }

            //every line except last, every column execpt first, adds bottom left pixel
            if ((h + 1) <= (height - 1) && (w - 1) >= 0)
            {
                sumRed += image[h + 1][w - 1].rgbtRed;
                sumGreen += image[h + 1][w - 1].rgbtGreen;
                sumBlue += image[h + 1][w - 1].rgbtBlue;
                count ++;
            }

            //every line except the last, adds bottom pixel
            if ((h + 1) <= (height - 1))
            {
                sumRed += image[h + 1][w].rgbtRed;
                sumGreen += image[h + 1][w].rgbtGreen;
                sumBlue += image[h + 1][w].rgbtBlue;
                count ++;
            }

            //every line except last, every column except last of the right, adds bottom right pixel
            if ((h + 1) <= (height - 1) && (w + 1) <= (width - 1))
            {
                sumRed += image[h + 1][w + 1].rgbtRed;
                sumGreen += image[h + 1][w + 1].rgbtGreen;
                sumBlue += image[h + 1][w + 1].rgbtBlue;
                count ++;
            }

            //gets the average for each color
            blurredimage[h][w].rgbtRed = round((float)sumRed / count);
            blurredimage[h][w].rgbtGreen = round((float)sumGreen / count);
            blurredimage[h][w].rgbtBlue = round((float)sumBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurredimage[i][j];
        }
    }

    return;
}