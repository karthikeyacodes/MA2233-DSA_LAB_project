#include <iostream>
#include <string>

using namespace std;

// Returns length of LCS for X[0..m-1], Y[0..n-1]
int lcs(const string& X, const string& Y, int m, int n, string& lcsResult)
{
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // Reconstructing the LCS
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcsResult = X[i - 1] + lcsResult;
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return L[m][n];
}

int main()
{
     string S1 = "abcdaabaacdaabaabaa";
    string S2 = "abcdaabcdaacdaabacddeacdbedaa";
    int m = S1.size();
    int n = S2.size();

    string lcsResult;
    int length = lcs(S1, S2, m, n, lcsResult);

    // Print the length of LCS
    cout << "Length of LCS is " << length << endl;

    // Print the LCS
    cout << "Longest Common Subsequence: " << lcsResult << endl;

    return 0;
}
