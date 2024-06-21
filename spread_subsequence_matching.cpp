#include <iostream>
#include <string>
using namespace std;

#define MAX_CHAR 256

int statearr[MAX_CHAR];
// Function to build the finite automaton for pattern
void buildFiniteAutomaton(string pattern, int m, int TF[][MAX_CHAR])
{
    int state, x;

    // Initialize the initial state
    state = 0;
    TF[0][pattern[0]] = 1;

    // Fill the transition function table
    for (int i = 1; i <= m; ++i)
    {
        // Copy values from the previous state
        for (x = 0; x < MAX_CHAR; ++x)
        {
            TF[i][x] = TF[state][x];
        }

        // Update the entry for the current character
        if (i < m)
        {
            TF[i][pattern[i]] = i + 1;
            state = TF[state][pattern[i]];
        }
    }
}

void searchPattern(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    int found = 0;

    // Initialize the finite automaton transition function table
    int TF[m + 1][MAX_CHAR];
    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j < MAX_CHAR; ++j)
        {
            TF[i][j] = 0;
        }
    }

    // Build the finite automaton
    buildFiniteAutomaton(pattern, m, TF);

    // Perform pattern matching using the finite automaton
    int state = 0;
    int indices[MAX_CHAR]; // Array to store indices of pattern matches
    int indexCount = 0;

    for (int i = 0; i < n; ++i)
    {
        state = TF[state][text[i]];

        statearr[i] = state;

        if (state < statearr[i - 1] && i != 0)
        {
            state = statearr[i - 1];
            statearr[i] = state;
        }

        // cout << statearr[i] << " " << state << endl;

        if (state == statearr[i - 1] + 1)
        {
            indices[indexCount] = i;
            indexCount++;
        }

        if (state == m)
        {
            found = 1;
            state = 0;
            cout << "Found " << pattern << " at indices : ";
            for (int j = 0; j < indexCount; j++)
            {
                cout << indices[j] << " ";
            }
            indexCount = 0;
            cout << endl;
            statearr[i] = 0;
        }
    }

    if (found == 0)
    {
        cout << "Pattern is not found in text" << endl;
    }
}

int main()
{
    string text = "abcdaabcdaacdaabacddeacdbedaa";
    string pattern = "abaa";
    searchPattern(text, pattern);

    return 0;
}