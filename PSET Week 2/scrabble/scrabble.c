#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Compute and return score for string
    int score = 0;
    // Get the lenght of the string entered by user
    int n = strlen(word);
    // Store the upper string
    int upperWord[n];

    //Conver the string to upper case if necessary
    for (int i = 0; i < n; i++)
    {
        upperWord[i] = toupper(word[i]);
    }

    //Calculate the score
    for (int i = 0; i < n; i++)
    {
        // If it's a non letter character, don't add any points
        if (upperWord[i] < 65 || upperWord[i] > 90)
        {
            score = score + 0;
        }
        else
        {
            // If it's a character, get the correspondent number of points
            int pointsNumber = upperWord[i];
            int pointsEarned = POINTS[pointsNumber - 65];
            score = score + pointsEarned;
        }
    }
    return score;
}
