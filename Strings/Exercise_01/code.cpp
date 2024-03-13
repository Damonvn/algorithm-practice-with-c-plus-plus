/* =============

Exercise - Counting Substrings that have exactly k distinct characters:

Given a string S and an integer k, your task is to count the number of
substrings of S that have exactly k distinct characters. Substrings are
not necessarily distinct from each other. For example, if S="abc" and k=2,
the result is 2, including the substrings: "ab", "bc".

Input:

The first line contains the number of test cases, T.
The next lines correspond to T test cases. Each test case consists of a string S and an integer k written on a single line.
Given that T and S satisfy the constraints: 1≤ T ≤100; 1≤ k ≤26; 1≤ Length(S)≤10^3.

Output:

Output the result for each test case on a separate line

Example T =  2:
Input
2
abc 2
2
aba 2
3

============= */

#include <iostream>
#include <string>
// #include <sstream>

using namespace std;

void solve(int (&a)[256], string s, int l, int r, int n, int &res)
{
    bool dfsRun = true;
    int l1;
    int r1;
    bool r1Set = false;
    int r1SetValue = 0;
    int countL = 0;
    int countR = 0;
    if (r == n - 1)
    {
        dfsRun = false;
        r1 = r;
    }
    for (int i = l; i <= r; i++)
    {
        l1 = i;
        if (a[s[i]] < 2)
        {
            break;
        }
        else
        {
            ++countL;
            --a[s[i]];
        }
    }
    for (int j = r + 1; j < n; j++)
    {
        r1 = j;
        if (a[s[j]] > 0)
        {
            ++countR;
            if (r1Set == false)
            {
                ++a[s[j]];
            }
            if (s[j] == s[l1] && r1Set == false)
            {
                r1Set = true;
                r1SetValue = j;
            }
            if (j == n - 1 && r1Set == false)
            {
                dfsRun = false;
            }
        }
        else
        {
            if (r1Set == false)
            {
                ++a[s[r1]];
            }
            break;
        };
    }
    res += (1 + countL + countR + countL * countR);
    ++l1;
    --a[s[l1 - 1]];
    if (r1Set == true)
    {
        r1 = r1SetValue;
    }

    if (dfsRun == true)
    {
        solve(a, s, l1, r1, n, res);
    }
}

int main()
{
    int t;
    cout << "Enter T: ";
    cin >> t;
    cin.ignore();
    while (t--)
    {
        int a[256] = {0};
        string inputS;
        string s;
        int k;
        cout << "Input: " << endl;
        getline(cin, inputS);
        for (int i = 0; i < inputS.length(); i++)
        {
            if (inputS[i] == ' ')
            {
                s = inputS.substr(0, i);
                k = (inputS[i + 1]) - '0';
                break;
            }
        }
        int r = 0;
        int cnt = 0;
        for (int i = 0; i < s.length(); i++)
        {
            r = i;
            a[s[i]] += 1;
            if (a[s[i]] == 1)
                ++cnt;
            if (cnt == k)
                break;
        }
        if (cnt < k)
        {
            cout << "Output: " << endl;
            cout << "Res: 0" << endl;
            return 0;
        }
        int res = 0;
        solve(a, s, 0, r, s.length(), res);
        cout << "Output: " << endl;
        cout << "Res: " << res << endl;
        cout << "==============" << endl;
    }
    return 0;
}

/*
Algorithm complexity varies from O(n+n) to O(n^2), depending on the number of occurrences where 'r1Set' is true.
If there are no occurrences where 'r1Set' is true, the algorithm complexity is O(n+n)
*/