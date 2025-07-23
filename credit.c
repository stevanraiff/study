#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    long original = number;
    int sum = 0;
    int count = 0;
    int first = 0;
    int second = 0;

    while (number > 0)
    {
        int digit = number % 10;

        if (count % 2 == 1)
        {
            int prod = digit * 2;
            sum += (prod / 10) + (prod % 10);
        }
        else
        {
            sum += digit;
        }

        if (number < 100 && number >= 10)
        {
            second = number % 10;
            first = number / 10;
        }

        number /= 10;
        count++;
    }

    if (sum % 10 == 0)
    {
        if (count == 15 && first == 3 && (second == 4 || second == 7))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && first == 5 && (second >= 1 && second <= 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && first == 4)
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
        printf("INVALID\n");
    }
}
