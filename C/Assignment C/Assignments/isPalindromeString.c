#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main(){
    char str1[] = "racecar";
    char str2[] = "oooopoooo";
    printf("Is \"%s\" a palindrome? %s\n", str1, isPalindrome(str1) ? "Yes" : "No");
    printf("Is \"%s\" a palindrome? %s\n", str2, isPalindrome(str2) ? "Yes" : "No");


    return 0;
}