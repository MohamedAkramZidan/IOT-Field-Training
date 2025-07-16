#include <stdio.h>

int main() {
  int num1, num2;
  char op;
  char choice;

  do{
    printf("Enter first number");
    scanf("%d", &num1);
    printf("Enter second number");
    scanf("%d", &num2);
    printf("Enter operation (+, -, *, /,%%): ");
    scanf(" %c", &op);

    switch(op){
      case '+':            
        printf("result: %d" , num1 + num2);
        break;

      case '-':            
        printf("result: %d" , num1 - num2);
        break;

      case'*':
        printf("result:%d",num1*num2);
        break;

      case '/':
        if (num2 != 0) 
          printf("result:%d",num1 / num2);
        else 
          printf("Error: Division by zero is not allowed.\n"); 
        break;
                  
      case '%':
        if (num2 != 0)
          printf("Remainder = %d\n", num1% num2);
        else
          printf("Error: Modulo by zero is not allowed.\n");
        break;

      default:
        printf("Invalid operator. Please use +, -, *, or /.\n");
        break;
  }
  printf("Do you want to perform another calculation? (y/n): ");
  scanf(" %c", &choice);

  }while (choice == 'y' || choice == 'Y');
  
  return 0;
}