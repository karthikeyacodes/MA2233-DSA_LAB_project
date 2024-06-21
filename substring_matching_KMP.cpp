#include <iostream>
#include <string>
using namespace std;

// Function to compute the Longest Proper Prefix which is also a Suffix array
void computeLPS(string pattern, int m, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            ++len;
            lps[i] = len;
            ++i;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }

    // for (int i = 0; i < m; i++)
    // {
    //     cout << lps[i] << " ";
    // }
    // cout << endl;
}

// KMP algorithm for pattern matching
void kmpSearch(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    
    // Compute the Longest Proper Prefix which is also a Suffix array
    int *lps = new int[m];
    computeLPS(pattern, m, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            ++i;
            ++j;
        }

        if (j == m)
        {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                ++i;
            }
        }
    }

    delete[] lps;
}

int main()
{
    string text;
    string pattern;

    cout << "Text: ";
    getline(cin, text);

    cout << "Pattern: ";
    getline(cin, pattern);

    kmpSearch(text, pattern);

    return 0;
}
