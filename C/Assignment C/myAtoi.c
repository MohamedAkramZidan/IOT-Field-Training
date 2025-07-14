#include <stdio.h>
#include <limits.h>
int myAtoi(char* str) {
    int result = 0;
    int sign = 1;

    while (*str == ' ') {
        str++;
    }
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        if (sign == 1 && result > INT_MAX) return INT_MAX;
        if (sign == -1 && -result < INT_MIN) return INT_MIN;
        str++;
    }
    return sign * result;
}


int main() {
    char str1[] = "42";
    int result = myAtoi(str1);
    printf("The converted integer is: %d\n", result);
    char str2[] = "-042";
    result = myAtoi(str2);
    printf("The converted integer is: %d\n", result);
    char str3[] = "1337cod3";
    result = myAtoi(str3);
    printf("The converted integer is: %d\n", result);
    char str4[] = "0-1";
    result = myAtoi(str4);
    printf("The converted integer is: %d\n", result);
    char str5[] = "words and 987";
    result = myAtoi(str5);
    printf("The converted integer is: %d\n", result);
  
    
  return 0;
}