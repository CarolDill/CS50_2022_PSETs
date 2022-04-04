#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool only_digits();
string rotate(string a, int key);

int main(int argc, string argv[])
{
    // Check if the number of arguments is correct or if key has any letters
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Ask input text from user
        string plaintext = get_string("plaintext: ");

        // Turn key into number
        int key = atoi(argv[1]);

        // If key is higher than 26, get the remainder to start the alphabet again
        if (key > 26)
        {
            key = key % 26;
        }

        // Encrypt the text with the key
        string cypher_text = rotate(plaintext, key);
        printf("ciphertext: %s\n", cypher_text);
    }
    return 0;
}

bool only_digits(string key)
{
    // Iterate over the key and check if there is any letter
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

string rotate(string a, int key)
{
    // Iterate over the text from user and encrypt it using the key
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isalpha(a[i]))
        {
            if (a[i] >= 65 && a[i] <= 90)
            {
                if (a[i] + key > 90)
                {
                    a[i] = a[i] + key - 26;
                }
                else
                {
                    a[i] += key;
                }
            }
            else if (a[i] >= 97 && a[i] <= 122)
            {
                if ((a[i] + key > 122))
                {
                    a[i] = a[i] + key - 26;
                }
                else
                {
                    a[i] += key;
                }
            }
            else
            {
                a[i] += key;
            }
        }
        else
        {
            a[i] = a[i];
        }
    }
    return a;
}