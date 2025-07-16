#include <stdio.h>
#include <limits.h>

typedef long long ll;
int isPrime(int x){
  if(x <= 1) return 0;
  if(x == 2 || x == 3) return 1;
  if(x %2 == 0 || x %3 == 0) return 0;

  for(int i = 5; (ll) i * i <= x; i+=6) {
    if(x%i == 0 || x%(i+2) ==0)
    return 0;
  }
  return 1;
}


int reverseDigits(int x){
  ll rev = 0;
  while(x){
    rev = rev * 10 + x%10;
    x/=10;

    if(rev > INT_MAX || rev < INT_MIN) return 0;
  }
  return rev;
}

int CountDigits(int x){
  int c = 0;
  while(x) {
    x/=10;
    c++;
  }
  return c;
}

int main(int argc, char const *argv[]) {
  printf("%s\n", "=> ");
  int inp;
  scanf("%d",&inp);
  int isp = isPrime(inp);
  printf("%s\n",isp == 0 ? "Not Prime":"Prime");

  printf("%s%d\n","Reversed  Integer ..",reverseDigits(inp));
  printf("%s%d\n","DigitCount ..",CountDigits(inp));

}