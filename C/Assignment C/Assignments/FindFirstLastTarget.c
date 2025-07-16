#include <stdio.h>

void FindFLTarget(int* nums, int numsSize, int target, int* output) {
    int left, right, mid;
    output[0] = -1;
    output[1] = -1;
    left = 0;
    right = numsSize - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        if (nums[mid] == target) {
            output[0] = mid;
        }
    }
    if (output[0] == -1) {
        return; 
    }
    left = 0;
    right = numsSize - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
        if (nums[mid] == target) {
            output[1] = mid;
        }
    }
}


int main(){
    int nums[] = {5, 7, 7, 8, 8, 10};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 8;
    int output[2];
    FindFLTarget(nums, numsSize, target, output);
    printf("First and Last positions of target %d are: [%d, %d]\n", target, output[0], output[1]);
    target = 6;
    FindFLTarget(nums, numsSize, target, output);
    printf("First and Last positions of target %d are: [%d, %d]\n", target, output[0], output[1]);
    target = 5;
    FindFLTarget(nums, numsSize, target, output);
    printf("First and Last positions of target %d are: [%d, %d]\n", target, output[0], output[1]);

    return 0;
}