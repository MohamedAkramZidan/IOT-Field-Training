#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
            return mid;
        else if (target < nums[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }

    return left;  
}

int main() {
    int nums[] = {1, 3, 5, 6};
    int target = 5;
    int result = searchInsert(nums, sizeof(nums) / sizeof(nums[0]), target);
    printf("Insert position for %d is: %d\n", target, result);

    target = 2;
    result = searchInsert(nums, sizeof(nums) / sizeof(nums[0]), target);
    printf("Insert position for %d is: %d\n", target, result);

    target = 7;
    result = searchInsert(nums, sizeof(nums) / sizeof(nums[0]), target);
    printf("Insert position for %d is: %d\n", target, result);

    return 0;
}