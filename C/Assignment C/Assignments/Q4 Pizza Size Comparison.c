// Q4: Pizza Size Comparison
#include <stdio.h>
#include <limits.h>

int max(int a, int b) { 
  return (a > b) ? a : b; 
}

int min(int a, int b) { 
  return (a < b) ? a : b; 
}

const double PI = 3.14;

int main() {
  int diam1, diam2, price1, price2;
  printf("Enter price for first pizza");
  scanf("%d", &price1);
  printf("Enter diameter for first pizza");
  scanf("%d", &diam1);
  printf("Enter price for second pizza");
  scanf("%d", &price2);
  printf("Enter diameter for second pizza");
  scanf("%d", &diam2);
 
  double a1 = PI*(diam1/2.0)*(diam1/2.0);
  double a2 = PI*(diam2/2.0)*(diam2/2.0);
  double cost1 = price1/a1; 
  double cost2 = price2/a2;

  printf("Price per square inch for first pizza is %f\n", cost1);
  printf("Price per square inch for second pizza is %f\n", cost2);

  if(cost1 > cost2) {
    printf("First pizza wins");
  }else if(cost2 > cost1) {
    printf("Second pizza wins");
  }else {
    if(a1 > a2) {
      printf("First pizza wins");
    }else if(a2 > a1) {
      printf("Second pizza wins");
    }else {
      printf("Equal price and size");
    }
  }
}