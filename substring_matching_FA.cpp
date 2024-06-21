#include <iostream>
#include <string>
using namespace std;

#define MAX_CHAR 256

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

// Function to perform pattern matching using finite automaton
void searchPattern(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();
    int found = 0;

    // Initialize the finite automaton transition function table
    int TF[m + 1][MAX_CHAR] = {0};

    // Build the finite automaton
    buildFiniteAutomaton(pattern, m, TF);

    // Perform pattern matching using the finite automaton
    int state = 0;
    for (int i = 0; i < n; ++i)
    {
        state = TF[state][text[i]];

        if (state == m)
        {
            found = 1;
            cout << "Pattern found at index " << (i - m + 1) << endl;
        }
    }

    if (found == 0)
    {
        cout << "Pattern is not found in text" << endl;
    }
}

int main()
{
    string text;
    string pattern;

    cout << "Text: ";
    getline(cin, text);

    cout << "Pattern: ";
    getline(cin, pattern);

    // Search for the pattern in the text
    searchPattern(text, pattern);

    return 0;
}
