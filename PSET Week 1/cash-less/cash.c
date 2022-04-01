#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int userInput;

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Get cents from user
    do
    {
        userInput = get_int("Change owed: ");
    } while (userInput < 0);

    return userInput;
}

int calculate_quarters(int cents)
{
    int quarterNumber = 0;

    // Calculate the quantity of Quarters
    do
    {
        int quarterValue = cents/25;
        if (quarterValue >= 1)
        {
            quarterNumber ++;
            cents = cents -25;
        }
    } while (cents >= 25);

    return quarterNumber;
}

int calculate_dimes(int cents)
{
    int dimesNumber = 0;

    // Calculate the quantity of Dimes
    do
    {
        int dimesValue = cents/10;
        if (dimesValue >= 1)
        {
            dimesNumber ++;
            cents = cents -10;
        }
    } while (cents > 10);

    return dimesNumber;
}

int calculate_nickels(int cents)
{
    int nickelsNumber = 0;

    // Calculate the quantity of Nickels
    do
    {
        int nickelValue = cents/5;
        if (nickelValue >= 1)
        {
            nickelsNumber ++;
            cents = cents -5;
        }
    } while (cents >= 5);

    return nickelsNumber;
}

int calculate_pennies(int cents)
{
    int penniesNumber = 0;

    // Calculate the number of pennies
    do
    {
        if (cents > 0)
        {
            penniesNumber ++;
            cents = cents -1;
        }
    } while (cents > 0);

    return penniesNumber;
}
