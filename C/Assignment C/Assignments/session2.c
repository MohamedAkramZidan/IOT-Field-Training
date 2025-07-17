#include <stdio.h>

int main()
{
    // Question2
    float balance, interest, Total_amount_due, minPayment;
    char choice;

    do
    {
        printf("Enter your balance please");
        scanf("%f", &balance);

        if (balance <= 1000)
        {
            interest = balance * 0.015;
        }
        else
        {
            interest = 1000 * 0.015 + (balance - 1000) * 0.01;
        }

        Total_amount_due = balance + interest;

        if (Total_amount_due <= 10)

        {
            minPayment = Total_amount_due;
        }

        else
        {
            minPayment = Total_amount_due * 0.1;
            minPayment = (minPayment < 10) ? 10 : minPayment;
        }

        printf("Account Balance: %.5f\n", balance);
        printf("Interest: %.5f\n", interest);
        printf("Total Due: %.5f\n", Total_amount_due);
        printf("Minimum Payment: %.5f\n", minPayment);
        printf("Do you want to enter another balance? (y/n) ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}