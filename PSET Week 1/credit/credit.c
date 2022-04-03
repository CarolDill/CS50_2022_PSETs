#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string cc;
string ccNumber1;
int ccDigits;
long ccNumberToCheckSum;
int ccOddPosition;
int ccEvenPosition;
int sumOddPositionNumbers = 0;
int sumEvenPositionNumbers = 0;
int totalSum;

int main(void)
{
    do
    {
        //Input user for CC NUmber
        cc = get_string("CC Number: ");
        ccNumber1 = cc;

        //Count the number of digits inserted by user
        ccDigits = strlen(cc);
        if (ccDigits < 13)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    while (ccDigits != 13 && ccDigits != 15 && ccDigits != 16);


    long ccNumber = atol(ccNumber1);
    ccNumberToCheckSum = ccNumber;

    //Validation of number of digits complete, starting check of sum
    do
    {
        //Remove last digit and add it to sumOddPositionNumbers
        ccOddPosition = ccNumberToCheckSum % 10;
        ccNumberToCheckSum = ccNumberToCheckSum / 10;
        sumOddPositionNumbers = sumOddPositionNumbers + ccOddPosition;

        //Remove second to last digit
        ccEvenPosition = ccNumberToCheckSum % 10;
        ccNumberToCheckSum = ccNumberToCheckSum / 10;

        //Double even position numbers and add digits to sum
        ccEvenPosition = ccEvenPosition * 2;
        //To split the numbers in case is higher than 10
        if (ccEvenPosition >= 10)
        {
            int d1 = ccEvenPosition % 10;
            int d2 = ccEvenPosition / 10;
            sumEvenPositionNumbers = sumEvenPositionNumbers + d1 + d2;

            //To consider the number itself is it's lower than 10
        }
        else
        {
            sumEvenPositionNumbers = sumEvenPositionNumbers + ccEvenPosition;
        }

    }
    while (ccNumberToCheckSum > 0);

    //Total sum of digits
    totalSum = sumOddPositionNumbers + sumEvenPositionNumbers;

    //To check if total divides by 10
    if (totalSum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        //Check the first digits of the CC. First, get the first 2 digits
        long checkStartNumbers = ccNumber;
        do
        {
            checkStartNumbers = checkStartNumbers / 10;
        }
        while (checkStartNumbers > 100);

        if ((checkStartNumbers <= 55) && (checkStartNumbers >= 51))
        {
            printf("MASTERCARD\n");
        }
        else if (checkStartNumbers == 34 || checkStartNumbers == 37)
        {
            printf("AMEX\n");
        }
        else if (checkStartNumbers / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}