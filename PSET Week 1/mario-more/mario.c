#include <cs50.h>
#include <stdio.h>

int height;

int main(void)
{
    do
    {
        //get input from user
        height = get_int("Height: ");
    }
    //continue asking for inputs until you get a positive number between 1 and 8
    while (height <= 0 || height > 8);

    //to align blocks to the right
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        //to print blocks
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = i + 1; l > i; l--)
        {
            for (int m = 0; m < i + 1; m++)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}