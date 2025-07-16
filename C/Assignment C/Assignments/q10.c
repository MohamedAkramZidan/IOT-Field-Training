#include <stdio.h>
#include <string.h>

int max(int a, int b) { 
  return (a > b) ? a : b; 
}

int main() {
  char a[] = "11";
  char b[] = "1";
  
  
  // -1 for null charater \0
  int s1 = sizeof(a)/sizeof(a[0]) -1;
  int s2 = sizeof(b)/sizeof(b[0]) -1;
  int end = max(s1, s2); 

  // handle case of different string size
  char aa[end + 1], bb[end + 1], c[end + 1];
  int carry[end + 1];

  memset(aa, '0', end);
  memset(bb, '0', end);
  memset(c, '0', end);
  memset(carry, 0, sizeof(carry));

  aa[end] = '\0';
  bb[end] = '\0';
  c[end] = '\0';

  for(int j = end-1, x = s1-1, y = s2-1; j >= 0; j--) {
    if(x >= 0) aa[j] = a[x--];
    if(y >= 0) bb[j] = b[y--];
  }

  printf(aa);
  printf("\n");
  printf(bb);
  printf("\n------------------\n");
  

  for(int i = end-1; i >= 0; i--) {
    // 48 for ascii
    int sum = aa[i]- '0' +bb[i] - '0' +carry[i];
    c[i] = sum%2 + '0';

    if(i > 0) carry[i-1] = sum/2;
    else carry[0] = sum/2;
  }

  // merge all in one string with leading or not
  if(carry[0]) {
    char ans[end+2];
    ans[0] = '1';
    for(int i = 0; i < end; i++) ans[i+1] = c[i];
    ans[end+1] = '\0';
    printf(ans);
  }else {
    printf(c);
  }
}