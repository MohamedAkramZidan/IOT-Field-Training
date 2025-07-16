#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 50001
#define MAX_M 6
#define MAX_N 6
#define MAX_WORD_LEN 16

typedef long long ll;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool dfs(char board[MAX_M][MAX_N], int m, int n, int i, int j, const char* word, int idx, bool visited[MAX_M][MAX_N]) {
    if (word[idx] == '\0') return true; 


    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] != word[idx])
        return false;

    visited[i][j] = true;

    for (int d = 0; d < 4; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (dfs(board, m, n, ni, nj, word, idx + 1, visited))
            return true;
    }

    visited[i][j] = false; 
    return false;
}

bool exist(char board[MAX_M][MAX_N], int m, int n, const char* word) {
    bool visited[MAX_M][MAX_N] = { false };

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfs(board, m, n, i, j, word, 0, visited))
                return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
	int m, n;
    char board[MAX_M][MAX_N];
    char word[MAX_WORD_LEN];

    scanf("%d %d", &m, &n);
   	for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c", &board[i][j]);
    scanf("%s", word);

    bool found = exist(board, m, n, word);

    printf("%s", found ? "yes":"no");

}