#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_LEN 50001
typedef long long ll;

int solve(const char* s){
	int seen[128] = {0};

	int l = 0 , r = 0;
	int maxLen = 0;
	int len = strlen(s);

	while(r < len){
		if(!seen[(unsigned char)s[r]]){
			seen[(unsigned char)s[r]]=1;
			int wind = r -l +1;
			if(wind > maxLen) maxLen = wind;

			r++;
		}
		else{
			seen[(unsigned char)s[l]] = 0;
			l++;
		}
	}
	return maxLen-1;
}
int main(int argc, char const *argv[])
{
	char input[MAX_LEN];
	fgets(input , sizeof(input),stdin);
	int re = solve(input);
	printf("%d\n",re);

}