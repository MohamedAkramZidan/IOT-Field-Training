#include <stdio.h>
#include <math.h>
// fn Prototype
int isPerfectSquare(int num);
int reverseDigits(int num);
int calculateSum(int num);
int main()
{
    int number;
    do
    {
        printf("Please enter a positive number: ");
        scanf("%d", &number);

        if (number <= 0)
        {
            printf("Invalid input. Number must be positive.\n");
        }

    } while (number <= 0);

    printf("Is perfect square? %s\n", isPerfectSquare(number) ? "Yes" : "No");
    printf("Reversed number: %d\n", reverseDigits(number));
    printf("Sum of digits: %d\n", calculateSum(number));

    return 0;
}
// Fn Declration
int isPerfectSquare(int num)
{
    int root = sqrt(num);
    return num == root * root;
}
int reverseDigits(int num)
{
    int rev = 0;
    while (num > 0)
    {
        rev = rev * 10 + num % 10;
        num = num / 10;
    }
    return rev;
}
int calculateSum(int num)
{
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}