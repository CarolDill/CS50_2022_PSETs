#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    //Get text frim user
    string text = get_string("Text: ");
    float letters = 0;
    //Words starts at 1 to consider that the last word doesn't have a space after it
    float words = 1;
    float sentences = 0;

    // Iterate the text
    for (int i = 0; i < strlen(text); i++)
    {
        // for each space, add a word count
        if (text[i] == 32)
        {
            words++;
        }
        // for each . ? ! and add a sentence count
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
        //Check if it's a letter, and add a letter count
        else if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
    }

    float L = letters / words * 100;
    float S = sentences / words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    printf("index: %i\n", index);

    if (index < 1)
    {
        printf("Before Grade 1.\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+.\n");
    }
    else
    {
        printf("Grade %i.\n", index);
    }
}