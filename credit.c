#include <stdio.h>
#include <cs50.h>
#include <math.h>

int luhn();
int length();
void validation();




int main(void)
{
    long cardNum = get_long("Number: ");
    long j = length(cardNum);
    validation(j, cardNum);
}







//checks the remainder against number length and the pre defined number prefixes for each type of card

void validation(long j, long cardNum)    
{
    int cardcheck = cardNum / pow(10, j - 2); // reduces card numbers to the first 2 digits
    if (j == 15 && luhn(j, cardNum) == 0)
    {
        if (cardcheck == 34 || cardcheck == 37) // amex only starts with 37 of 34
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (j == 13 && luhn(j, cardNum) == 0) 
    {
        if (cardcheck >= 40 && cardcheck <= 49) // visa always starts with a 4
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (j == 16 && luhn(j, cardNum) == 0)
    {
        if (cardcheck >= 51 && cardcheck <= 55) // mastercard starts with a number from 51-55
        {
            printf("MASTERCARD\n");
        }
        else if (cardcheck >= 40 && cardcheck <= 49) // again visa always starts with a 4 
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n"); // returns invalid for any other card number input
    }
}

//determines the length of the number input by user and returns 13, 15, 16 or 1 if not a credit card length specified in the problemset.
int length(long cardNum)
{
    if (cardNum >= 1000000000000000) 
    {
        return 16;
    }
    else if (100000000000000 <= cardNum && cardNum <= 1000000000000000)
    {
        return 15;
    }
    else if (1000000000000 <= cardNum && cardNum < 10000000000000)
    {
        return 13;
    }
    else
    {
        return 0;
    }
}

int luhn(long j, long cardNum) // this will return the sum of the digits required to test luhns algorithm
{
    int k = 0;  // k will be the sum of the first half of the required values
    int c = 0;
    int b = 0;
    for (int i = 1; i <= j; i ++)
    {
        long power = pow(10, i); //creates a number that will be used to determine the remainder
        int l = i - 1;
        long a = cardNum % power; //determines the remainder at spot i
        if (a < pow(10, l))
        { 
            a = 0;  // if there are zeroes in the number this will return 0 instead of an improper value
        }
        else
        {
            a = a / pow(10, l); // this will make "a" the single digit value at location i in the number
        }
        if (i % 2 == 0)    // if i is divisible by 2 multiply the values by 2 and add thier digits
        {
            b = a * 2;
            if (b >= 10)     // if 2x the digit is greater than 10 it will add 1 and the remainder together 
            {
                b = 1 + b % 10;
            }
            k = k + b; //keeps a total of all the doubled values
        }
        else
        {
            c = c + a; // keeps a sum of all non doubled values
        }
    }
    k = k + c; //sum of all values 
    k = k % 10; // modulo of 10 to determine if the last digit of the sum is zero for validation
    return k;
}