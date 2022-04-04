#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_letters();
string rotate(string a, string key);

int main(int argc, string argv[])
{
    // Check if the number of arguments is correct
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) < 26 || !only_letters(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int n = strlen(argv[1]);
        for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if ( key[i] == key[j])
                    {
                        printf("Each letter on the key must apper only once\n");
                        return 1;
                    }
                }
            }

        // Ask input text from user
        string plaintext = get_string("plaintext: ");

        // Encrypt the text with the key
        string cypher_text = rotate(plaintext, key);
        printf("ciphertext: %s\n", cypher_text);
    }
    return 0;
}

bool only_letters(string key)
{
    // Iterate over the key and check if there is any non-alpha character
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}

string rotate(string a, string key)
{
    // Iterate over the text from user and encrypt it using the key
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        // Check if the character is lower case
        if (isalpha(a[i]))
        {
            // If it is, get the correspondent encryption key and turn it into lower case
            if (islower(a[i]))
            {
                int x = a[i];
                a[i] = tolower(key[x - 97]);
            }
            else
            {
                int x = a[i];
                a[i] = toupper(key[x - 65]);
            }
        }
        // If it's not character, just repeat
        else
        {
            a[i] = a[i];
        }
    }
    return a;
}