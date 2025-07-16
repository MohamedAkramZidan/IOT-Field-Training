#include <stdio.h>

int main() {
  int num1, num2;

  printf("Enter the first number\n");
  scanf("%d", &num1);
  printf("Enter the second number\n");
  scanf("%d", &num2);

  if(num1%2 == 0 && num2%2 == 0) {
    printf("Sum: %d", num1+num2);
  }else if(num1%2 == 1 && num2%2 == 1) {
    printf("Product: %d", num1*num2);
  }else {

    // detect odd from even
    int odd = num1%2 == 0 ? num2 : num1; 
    int even = num1%2 == 0 ? num1 : num2; 

    printf("Even - odd: %d", even - odd);
  }
  
  return 0;
}