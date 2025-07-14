// Q7: median of two sorted arrays 
#include <stdio.h>
#include <limits.h>

int max(int a, int b) { 
  return (a > b) ? a : b; 
}

int min(int a, int b) { 
  return (a < b) ? a : b; 
}

double findMedianSortedArrays(int* nums1, int* nums2, int size1, int size2) {
  
  // make nums2 the smallest array
  if(size1 > size2) {
    return findMedianSortedArrays(nums2, nums1, size2, size1);
  }
  
  int totalSize = size1+size2;
  int half = (totalSize+1)/2;

  int l = 0, r = size1;
  while(l <= r) {
    int m1 = (l+r)/2;
    int m2 = half - m1;

    int a1 = m1 > 0 ? nums1[m1-1] : INT_MIN;
    int a2 = m2 > 0 ? nums2[m2-1] : INT_MIN;
    int a3 = m1 < size1 ? nums1[m1] : INT_MAX;
    int a4 = m2 < size2 ? nums2[m2] : INT_MAX;

    if(a1 <= a4 && a2 <= a3) {
      if(totalSize%2 == 0) return (max(a1, a2) + min(a3, a4))/2.0;
      return max(a1, a2);
    }else if(a1 > a4) {
      r = m1-1;
    }else {
      l = m1+1;
    }
  }
  return 0.0;
}

int main() {
  int nums1[] = {-5, -3, 0}, nums2[] = {-4, -2, 1};
  
  int size1 = (sizeof(nums1)/sizeof(nums1[0]));
  int size2 = (sizeof(nums2)/sizeof(nums2[0]));

  printf("%f", findMedianSortedArrays(nums1, nums2, size1, size2));
}